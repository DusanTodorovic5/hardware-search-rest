#ifndef SEARCH_ENGINE_CLASS
#define SEARCH_ENGINE_CLASS

#include "market.hpp"
#include "json/parser.hpp"

class Engine {
    public:
        Engine(std::vector<std::string>);
        ~Engine();
        template <typename T> std::vector<T*> query(Criterium*, Market*);
        std::string query(QueryCriterium*);
        std::string buyQuery(QueryCriterium*);
        std::string diffQuery(QueryCriterium*);
        bool add(std::string, std::string);
    private:
        std::string getStringCriterium(Criterium*);
        std::vector<Market*> markets;
};

#endif