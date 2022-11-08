#include "../hpp/util.hpp"

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token != "") res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

Operation stringToOperation(std::string operation) {
    if (operation == "<=") return Operation::NotBiggerThan;
    if (operation == ">") return Operation::BiggerThan;
    if (operation == "<") return Operation::LessThan;
    if (operation == ">=") return Operation::NotLessThan;
    if (operation == "!=") return Operation::NotEqual;
    if (operation == "<>") return Operation::Between;
    return Operation::Equal;
}

Action stringToAction(std::string action) {
    if (action == "buy") return Action::BUY;
    if (action == "buyanyways") return Action::BUY_ANYWAYS;
    if (action == "select") return Action::SELECT;
    if (action == "diff") return Action::DIFF;
    return Action::INFO;
}

Type stringToType(std::string type) {
    if (type == "cpu") return Type::CPU;
    if (type == "gpu") return Type::GPU;
    if (type == "motherboard") return Type::MOTHERBOARD;
    if (type == "psu") return Type::PSU;
    if (type == "case") return Type::PC_CASE;
    if (type == "ssd") return Type::SSD;
    if (type == "ram") return Type::RAM;
    return Type::COOLER;
}

bool isNumber(std::string& str, bool hasFloatingPoint) {
    if (!str.length()) return false;
    for (int i=0;i<str.length();++i) {
        if ((i == 0 && str[i] == '-') || (str[i] >= '0' && str[i] <= '9')) continue;
        if (!hasFloatingPoint) return false;
        if (str[i] != '.') return false;
    }
    return true;
}