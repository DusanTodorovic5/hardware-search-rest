#ifndef PARSER_JSON_CLASS
#define PARSER_JSON_CLASS

#include "../../simdjson.h"
#include "query_criterium.hpp"

class Parser {
    public:
        Parser(std::string _json);
        QueryCriterium* operator()();
        ~Parser();
    private:
        QueryCriterium* qc;
        std::string raw_json;
};

#endif