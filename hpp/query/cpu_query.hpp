#ifndef CPU_QUERY_CLASS
#define CPU_QUERY_CLASS

#include "iquery.hpp"
#include "../cpu.hpp"

struct CPUQueryLambdas {
    void filterByID(int criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->getId() != criteria; };
        switch (operation) {
            case Operation::LessThan : p =  [&criteria](const CPU* m) { return m->getId() >= criteria; }; break;
            case Operation::BiggerThan : p =  [&criteria](const CPU* m) { return m->getId() <= criteria; }; break;
            case Operation::Equal : p =  [&criteria](const CPU* m) { return m->getId() != criteria; }; break;
            case Operation::NotLessThan : p =  [&criteria](const CPU* m) { return m->getId() < criteria; }; break;
            case Operation::NotBiggerThan : p =  [&criteria](const CPU* m) { return m->getId() > criteria; }; break;
            case Operation::NotEqual : p =  [&criteria](const CPU* m) { return m->getId() == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByMaker(std::string criteria, Operation operation, std::vector<CPU*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->manufacturer == criteria; }), filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->manufacturer != criteria; }), filtered.end());
    }   

    void filterByChipSocket(std::string criteria, Operation operation, std::vector<CPU*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->chipSocket == criteria; }), filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->chipSocket != criteria; }), filtered.end());
    }

    void filterByGeneration(int criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->generation != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return m->generation >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return m->generation <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return m->generation != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const CPU* m) { return m->generation < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return m->generation > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return m->generation == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByGeneration(int criteria, int criteria2, Operation operation, std::vector<CPU*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const CPU* m) { return m->generation < criteria && m->generation > criteria2; }), filtered.end());
    }

    void filterByChipModel(std::string criteria, Operation operation, std::vector<CPU*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->model == criteria; }), filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->model != criteria; }), filtered.end());
    }

    void filterByChipVersion(std::string criteria, Operation operation, std::vector<CPU*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->chipVersion == criteria; }), filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const CPU* m) { return m->chipVersion != criteria; }), filtered.end());
    }

    void filterByCoresNumber(short criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->getCoreCount() != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return (m->getCoreCount() >= criteria); }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return (m->getCoreCount() <= criteria); }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return (m->getCoreCount() != criteria); }; break;
            case Operation::NotLessThan : p = [&criteria](const CPU* m) { return (m->getCoreCount() < criteria); }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return (m->getCoreCount() > criteria); }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return (m->getCoreCount() == criteria); }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByCoresNumber(short criteria, short criteria2, Operation operation, std::vector<CPU*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const CPU* m) { return m->getCoreCount() < criteria || m->getCoreCount() > criteria2; }), filtered.end());
    }

    void filterByBaseFrequency(float criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->baseFreq != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return m->baseFreq >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return m->baseFreq <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return m->baseFreq != criteria; }; break;
            case Operation::NotLessThan :  p = [&criteria](const CPU* m) { return m->baseFreq < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return m->baseFreq > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return m->baseFreq == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByBaseFrequency(float criteria, float criteria2, Operation operation, std::vector<CPU*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const CPU* m) { return m->baseFreq < criteria && m->baseFreq > criteria2; }), filtered.end());
    }

    void filterByTurboFrequency(float criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->turboFreq != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return m->turboFreq >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return m->turboFreq <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return m->turboFreq != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const CPU* m) { return m->turboFreq < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return m->turboFreq > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return m->turboFreq == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByTurboFrequency(float criteria2, float criteria, Operation operation, std::vector<CPU*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const CPU* m) { return m->turboFreq < criteria && m->turboFreq > criteria2; }), filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const CPU* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }

    void filterByPrice(double criteria, double criteria2, Operation, std::vector<CPU*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const CPU* m) { return m->price < criteria && m->price > criteria2; }), filtered.end());
    }

    void filterByStock(int criteria, Operation operation, std::vector<CPU*>& filtered) {
        std::function<bool(const CPU*)> p = [&criteria](const CPU* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const CPU* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const CPU* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const CPU* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const CPU* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const CPU* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const CPU* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p), filtered.end());
    }
};

template<>
class Query<CPU> {
    public:
        Query<CPU>(std::vector<CPU*> all) : filtered(all) { }
        Query<CPU>& filterBy(std::string _for, std::string _what, Operation _how) {
            CPUQueryLambdas cql;
            if (_for == "id") {
                cql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                cql.filterByMaker(_what, _how, filtered);
            } else if (_for == "chipSocket") {
                cql.filterByChipSocket(_what, _how, filtered);
            } else if (_for == "generation") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    cql.filterByGeneration(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    cql.filterByGeneration(std::stod(_what), _how, filtered);
                }
            } else if (_for == "cores") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    cql.filterByCoresNumber(std::stoi(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    cql.filterByCoresNumber(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "frequency") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    cql.filterByBaseFrequency(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    cql.filterByBaseFrequency(std::stod(_what), _how, filtered);
                }
            } else if (_for == "turbo") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    cql.filterByTurboFrequency(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    cql.filterByTurboFrequency(std::stod(_what), _how, filtered);
                }
            } else if (_for == "chipModel") {
                cql.filterByChipModel(_what, _how, filtered);
            } else if (_for == "chipVersion") {
                cql.filterByChipVersion(_what, _how, filtered);
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    cql.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    cql.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                cql.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }
            return *this;
        }
        std::vector<CPU*> get() { return filtered; }
    private:
        std::vector<CPU*> filtered;
};

#endif