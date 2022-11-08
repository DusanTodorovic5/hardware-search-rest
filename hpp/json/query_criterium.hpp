#ifndef QUERY_CRITERIUMS_STRUCT
#define QUERY_CRITERIUMS_STRUCT

#include "criterium.hpp"

struct QueryCriterium {
    QueryCriterium() : buyAnyways(false) { }
    Action action;
    std::vector<Criterium*> wheres;
    bool buyAnyways;
};

#endif