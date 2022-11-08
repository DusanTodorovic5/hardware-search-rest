#ifndef MARKET_CLASS
#define MARKET_CLASS

#include "cpu.hpp"
#include "motherboard.hpp"
#include "gpu.hpp"
#include "pc_case.hpp"
#include "cooler.hpp"
#include "power_supply.hpp"
#include "ram.hpp"
#include "ssd.hpp"
#include "query/iquery.hpp"
#include "json/query_criterium.hpp"
#include <iostream>
#include <vector>


class Market {
    public:
        Market(std::string);
        std::string getName() const;
        template<typename T> Query<T> getQuery(){ return Query<T>({}); }
        void add(std::vector<std::string>);
        ~Market();
    private:
        std::vector<CPU*> cpus;
        std::vector<Motherboard*> motherboards;
        std::vector<GPU*> gpus;
        std::vector<PcCase*> cases;
        std::vector<PowerSupply*> powerSupplies;
        std::vector<RAM*> rams;
        std::vector<Cooler*> coolers;
        std::vector<SSD*> ssds;
        std::string name;
};

#endif