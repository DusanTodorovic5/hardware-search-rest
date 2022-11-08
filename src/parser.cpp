#include "../hpp/json/parser.hpp"
#include <iostream>
Parser::Parser(std::string json) : raw_json(json) { qc = nullptr; }

Parser::~Parser() { if (qc) delete qc; }

Part* parsePart(std::string key, std::string value) {
    std::vector<std::string> splitted = split(value);

    if (splitted.size() < 2) return nullptr;

    Operation op = stringToOperation(splitted[0]);

    if (op == Operation::Between && splitted.size() != 3) return nullptr;

    Part* p = new Part();
    p->_for = key;
    p->operation = op;
    p->_what = splitted[1];
    if (op == Operation::Between) {
        p->_what += ";" + splitted[2];
    }

    return p;
}

Criterium* parseCriterium( simdjson::ondemand::object object) {
    Criterium* crit = new Criterium();
    crit->_for = "base";
    bool dirty = false;
    bool typeSet = false;
     for (auto field : object) {
        std::string_view keyv = field.unescaped_key();
        if (keyv == "type") {
            crit->type = stringToType(std::string(field.value().get_string().value()));
            typeSet = true;
            continue;
        }

        if (keyv == "operation") {
            crit->operation = stringToOperation(std::string(field.value().get_string().value()));
            continue;
        }

        if (keyv == "amount") {
            crit->amount = field.value().get_int64().value();
            Part* p = parsePart("stock", ">=;" + std::to_string(crit->amount));
            if (p) {
                crit->parts.push_back(p);
                dirty = true;
            }
            continue;
        }

        if (field.value().type() ==  simdjson::ondemand::json_type::object) {
            Criterium* c = parseCriterium(field.value().get_object());
            if (c) {
                c->_for = std::string(keyv);
                crit->parts.push_back(c);
                dirty = true;
            }
            continue;
        }

        Part* p = parsePart(std::string(keyv), std::string(field.value().get_string().value()));
        if (p) {
            crit->parts.push_back(p);
            dirty = true;
        }
    }
    if (!dirty || !typeSet) {
        delete crit;
        crit = nullptr;
    }
    return crit;
}

QueryCriterium* Parser::operator()() {
    simdjson::ondemand::parser parser;
    simdjson::padded_string json = simdjson::padded_string(raw_json);

    simdjson::ondemand::document doc = parser.iterate(json);

    simdjson::ondemand::object object = doc.get_object();
    std::string action = "";
    std::string buyAnyways = "";
    std::string filter = "";
    
    for (auto field : object) {
        std::string_view keyv = field.unescaped_key();

        if (keyv == "action" && field.value().type() ==  simdjson::ondemand::json_type::string) {
            action = std::string(field.value().get_string().value());
            continue;
        }

        if (keyv == "buyAnyways" && field.value().type() ==  simdjson::ondemand::json_type::string) {
            buyAnyways = std::string(field.value().get_string().value());
            continue;
        }

        if (keyv == "queries" && field.value().type() ==  simdjson::ondemand::json_type::array) {
            filter = std::string(field.value().get_array().value().raw_json().value());
            continue;
        }
    }

    if (action == "" || filter == "") return nullptr;

    QueryCriterium* qc = new QueryCriterium();
    qc->action = stringToAction(action);
    qc->buyAnyways = buyAnyways == "True";
    json = simdjson::padded_string(filter);
    for (auto value : parser.iterate(json)) {
        if (value.value().type() != simdjson::ondemand::json_type::object) {
            continue;
        }
        Criterium* ct = parseCriterium(value);
        if (ct) {
            if (ct->amount == -1 && (qc->action == Action::BUY || qc->action == Action::BUY_ANYWAYS)) {
                delete ct;
                ct = nullptr;
            }
            qc->wheres.push_back(ct);
        }
    }

    if (qc->wheres.size() == 0) {
        delete qc;
        return nullptr;
    }

    return qc;
}
