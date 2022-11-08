#ifndef QUERY_INTERFACE
#define QUERY_INTERFACE

#include <string>
#include <functional>
#include <algorithm>
#include "../util.hpp"

template <class T>
class Query {
    public:
        Query(std::vector<T*> all) : filtered(all) { }
        virtual Query<T>& filterBy(std::string, std::string, Operation) { return *this; }
        std::vector<T*> get() { return filtered; }
    private:
        std::vector<T*> filtered;
};

#endif