#ifndef CRITERIUM_STRUCT
#define CRITERIUM_STRUCT

#include <string>
#include <vector>
#include "../query/iquery.hpp"
#include "query_criterium.hpp"
#include "../util.hpp"

struct Part {
    std::string _what;
    std::string _for;
    Operation operation;
    virtual inline bool isComplex() const { return false; } 
};

struct Criterium : public Part {
    Criterium() { amount = -1; operation = Operation::Equal; }
    inline bool isComplex() const override { return true; } 
    std::vector<Part*> parts;
    Type type;
    int amount;
    ~Criterium() { for (Part* p : parts) delete p; }
};

#endif