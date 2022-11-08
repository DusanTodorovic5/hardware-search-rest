#ifndef UTIL_FILE_HEADER
#define UTIL_FILE_HEADER

#include <vector>
#include <iostream>

enum class Operation {
    LessThan,
    BiggerThan,
    Equal,
    NotLessThan,
    NotBiggerThan,
    NotEqual,
    Between
};

enum class Type {
    CPU,
    GPU,
    MOTHERBOARD,
    PSU,
    PC_CASE,
    SSD,
    RAM,
    COOLER
};

enum class Action {
    BUY,
    BUY_ANYWAYS,
    SELECT,
    INFO,
    DIFF
};

Action stringToAction(std::string action);

Type stringToType(std::string type);

std::vector<std::string> split(std::string s, std::string delimiter = ";");

Operation stringToOperation(std::string);

bool isNumber(std::string&, bool hasFloatingPoint = false);


#endif