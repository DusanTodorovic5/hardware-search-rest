#include "../hpp/engine.hpp"
#include "../hpp/query/cpu_query.hpp"
#include "../hpp/query/cooler_query.hpp"
#include "../hpp/query/gpu_query.hpp"
#include "../hpp/query/motherboard_query.hpp"
#include "../hpp/query/pc_case_query.hpp"
#include "../hpp/query/psu_query.hpp"
#include "../hpp/query/ram_query.hpp"
#include "../hpp/query/ssd_query.hpp"

Engine::Engine(std::vector<std::string> marketNames) {
    for (std::string name : marketNames) this->markets.push_back(new Market(name));
}

Engine::~Engine() {
    for (Market* m : markets) delete m;
}

template<typename T> std::vector<T*> Engine::query(Criterium* qc, Market* m) {
    Query q = m->getQuery<T>();
    for (Part* p : qc->parts) {
        if (p->isComplex()) {
            std::string _what = getStringCriterium(dynamic_cast<Criterium*>(p));
            q.filterBy(p->_for, _what, p->operation);
            continue;
        }
        q.filterBy(p->_for, p->_what, p->operation);
    }
    return q.get();
}

std::string Engine::getStringCriterium(Criterium* c) {
     switch (c->type) {
        case Type::CPU: 
            for (Market* m : markets) {
                std::vector<CPU*> cpus = this->query<CPU>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break; 
        case Type::GPU: 
            for (Market* m : markets) {
                std::vector<GPU*> cpus = this->query<GPU>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break;  
        case Type::MOTHERBOARD: 
            for (Market* m : markets) {
                std::vector<Motherboard*> cpus = this->query<Motherboard>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break; 
        case Type::PSU: 
            for (Market* m : markets) {
                std::vector<PowerSupply*> cpus = this->query<PowerSupply>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break;  
        case Type::PC_CASE: 
            for (Market* m : markets) {
                std::vector<PcCase*> cpus = this->query<PcCase>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break;  
        case Type::SSD: 
            for (Market* m : markets) {
                std::vector<SSD*> cpus = this->query<SSD>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break; 
        case Type::RAM: 
            for (Market* m : markets) {
                std::vector<RAM*> cpus = this->query<RAM>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break;   
        case Type::COOLER: 
            for (Market* m : markets) {
                std::vector<Cooler*> cpus = this->query<Cooler>(c, m);
                if (cpus.size()) {
                    return cpus[0]->getValueFromString(c->_for);
                }
            }
            break;  
    };

    return "";
}

std::string Engine::query(QueryCriterium* qc) {
    if (!qc) return {};
    
    std::vector<std::vector<Sector*>> rets;
    for (Criterium* c : qc->wheres) {
        std::vector<Sector*> ret;
        switch (c->type) {
            case Type::CPU: 
                for (Market* m : markets) {
                    std::vector<CPU*> cpus = this->query<CPU>(c, m);
                    for (CPU* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::GPU: 
                for (Market* m : markets) {
                    std::vector<GPU*> cpus = this->query<GPU>(c, m);
                    for (GPU* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::MOTHERBOARD: 
                for (Market* m : markets) {
                    std::vector<Motherboard*> cpus = this->query<Motherboard>(c, m);
                    for (Motherboard* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::PSU: 
                for (Market* m : markets) {
                    std::vector<PowerSupply*> cpus = this->query<PowerSupply>(c, m);
                    for (PowerSupply* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::PC_CASE: 
                for (Market* m : markets) {
                    std::vector<PcCase*> cpus = this->query<PcCase>(c, m);
                    for (PcCase* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::SSD: 
                for (Market* m : markets) {
                    std::vector<SSD*> cpus = this->query<SSD>(c, m);
                    for (SSD* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::RAM: 
                for (Market* m : markets) {
                    std::vector<RAM*> cpus = this->query<RAM>(c, m);
                    for (RAM* e : cpus) ret.push_back(e);
                }
                break;   
            case Type::COOLER: 
                for (Market* m : markets) {
                    std::vector<Cooler*> fil = this->query<Cooler>(c, m);
                    for (Cooler* e : fil) ret.push_back(e);
                }
                break;  
        };
        rets.push_back(ret);
    }

    std::string json = "{\"queries:\"[";
    int queryNumber = 0;
    for (std::vector<Sector*>& s : rets) {
        json += "{ \"queryNumber:\" " + std::to_string(++queryNumber) + ", \"result\":[";
        for (int i = 0;i < s.size();i++) {
            json += s[i]->toJson() + (i == s.size() - 1 ? "]}" : ",");
        }
        s != rets[rets.size() - 1] ? json += "," : json += "]}";
    }

    return json;
}

std::string Engine::buyQuery(QueryCriterium* qc) { 
    if (!qc) return {};

    std::vector<std::string> rets;
    std::vector<std::pair<std::vector<Sector*>, Criterium*>> forBuy;
    for (Criterium* c : qc->wheres) {
        if (c->amount == -1) { continue; }
        std::vector<Sector*> ret;
        switch (c->type) {
            case Type::CPU: 
                for (Market* m : markets) {
                    std::vector<CPU*> cpus = this->query<CPU>(c, m);
                    for (CPU* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::GPU: 
                for (Market* m : markets) {
                    std::vector<GPU*> cpus = this->query<GPU>(c, m);
                    for (GPU* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::MOTHERBOARD: 
                for (Market* m : markets) {
                    std::vector<Motherboard*> cpus = this->query<Motherboard>(c, m);
                    for (Motherboard* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::PSU: 
                for (Market* m : markets) {
                    std::vector<PowerSupply*> cpus = this->query<PowerSupply>(c, m);
                    for (PowerSupply* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::PC_CASE: 
                for (Market* m : markets) {
                    std::vector<PcCase*> cpus = this->query<PcCase>(c, m);
                    for (PcCase* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::SSD: 
                for (Market* m : markets) {
                    std::vector<SSD*> cpus = this->query<SSD>(c, m);
                    for (SSD* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::RAM: 
                for (Market* m : markets) {
                    std::vector<RAM*> cpus = this->query<RAM>(c, m);
                    for (RAM* e : cpus) ret.push_back(e);
                }
                break;   
            case Type::COOLER: 
                for (Market* m : markets) {
                    std::vector<Cooler*> fil = this->query<Cooler>(c, m);
                    for (Cooler* e : fil) ret.push_back(e);
                }
                break;  
        };

        std::sort(ret.begin(), ret.end());
        forBuy.push_back({ret, c});
    }

    if (forBuy.size() == 0) { return "{\"message\":\"Invalid query\"}"; }

    for (std::pair<std::vector<Sector*>, Criterium*>& b : forBuy) {
        bool bought = false;
        for (int i=0; i < b.first.size(); i++) {
            if ((bought = b.first[i]->buy(b.second->amount))) {
                rets.push_back("{ \"message\":\" " + b.first[i]->toJson() + "}");
                break;
            }
        }
        if (!bought && !qc->buyAnyways) {
            return "{\"message\":\"Didn't find right products\"}";
        }

        if (!bought) {
            rets.push_back("{ \"message\":\"Found no elements for: " + b.second->_what + "}");
        }
    }

    std::string retString = "{ \"queries\":[";
    for (int i=0;i<rets.size();i++) {
        retString += rets[i];
        i == rets.size() - 1 ? retString += "]}" : retString += ",";
    }
    return retString;
}

std::string Engine::diffQuery(QueryCriterium* qc) { 
    if (!qc) return {};
    std::vector<std::string> rets;
    std::vector<Sector*> forDiff;
    for (Criterium* c : qc->wheres) {
        std::vector<Sector*> ret;
        switch (c->type) {
            case Type::CPU: 
                for (Market* m : markets) {
                    std::vector<CPU*> cpus = this->query<CPU>(c, m);
                    for (CPU* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::GPU: 
                for (Market* m : markets) {
                    std::vector<GPU*> cpus = this->query<GPU>(c, m);
                    for (GPU* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::MOTHERBOARD: 
                for (Market* m : markets) {
                    std::vector<Motherboard*> cpus = this->query<Motherboard>(c, m);
                    for (Motherboard* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::PSU: 
                for (Market* m : markets) {
                    std::vector<PowerSupply*> cpus = this->query<PowerSupply>(c, m);
                    for (PowerSupply* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::PC_CASE: 
                for (Market* m : markets) {
                    std::vector<PcCase*> cpus = this->query<PcCase>(c, m);
                    for (PcCase* e : cpus) ret.push_back(e);
                }
                break;  
            case Type::SSD: 
                for (Market* m : markets) {
                    std::vector<SSD*> cpus = this->query<SSD>(c, m);
                    for (SSD* e : cpus) ret.push_back(e);
                }
                break; 
            case Type::RAM: 
                for (Market* m : markets) {
                    std::vector<RAM*> cpus = this->query<RAM>(c, m);
                    for (RAM* e : cpus) ret.push_back(e);
                }
                break;   
            case Type::COOLER: 
                for (Market* m : markets) {
                    std::vector<Cooler*> fil = this->query<Cooler>(c, m);
                    for (Cooler* e : fil) ret.push_back(e);
                }
                break;  
        };
        if (ret.size() > 0) {
            std::sort(ret.begin(), ret.end());
            forDiff.push_back(ret[0]);
        }
        
    }

    if (forDiff.size() == 0) { return "{\"message\":\"Invalid query\"}"; }

    std::string retString = "[";
    int count = forDiff.size() * (forDiff.size() - 1);
    for (int i=0;i<forDiff.size();i++) {
        for (int j = 0;j<forDiff.size();j++) {
            if (i == j) continue;
            retString += Sector::compare(forDiff[i], forDiff[j]) + ",";
        }
    }
    retString[retString.length() - 1] = ']';
    return retString;
}

bool Engine::add(std::string name, std::string text) {
    for (Market* m : markets) {
        if (m->getName() == name) {
            m->add(split(text,"\n"));
            return true;
        }
    }
    return false;
}