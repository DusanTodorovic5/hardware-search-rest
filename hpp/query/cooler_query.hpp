#ifndef CC_QUERY_CLASS
#define CC_QUERY_CLASS

#include "iquery.hpp"
#include <functional>
#include "../cooler.hpp"

struct CoolerQueryLambda {
    void filterByID(int criteria, Operation operation, std::vector<Cooler*>& filtered) {
        std::function<bool(const Cooler*)> p = [&criteria](const Cooler* m) { return m->getId() != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Cooler* m) { return m->getId() >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Cooler* m) { return m->getId() <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Cooler* m) { return m->getId() != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Cooler* m) { return m->getId() < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Cooler* m) { return m->getId() > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Cooler* m) { return m->getId() == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByManufacturer(std::string criteria, Operation operation, std::vector<Cooler*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->manufacturer == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void filterByModel(std::string criteria, Operation operation, std::vector<Cooler*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->model == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(),  [&criteria](const Cooler* m) { return m->model != criteria; }),filtered.end());
    }

    void filterBySize(std::string criteria, Operation operation, std::vector<Cooler*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->size == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(),  [&criteria](const Cooler* m) { return m->size != criteria; }),filtered.end());
    }

    void filterBySocketSupport(std::string criteria, Operation operation, std::vector<Cooler*>& filtered) {
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->socketSupport == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Cooler* m) { return m->socketSupport != criteria; }),filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<Cooler*>& filtered) {
        std::function<bool(const Cooler*)> p = [&criteria](const Cooler* m) { return m->getPrice() != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Cooler* m) { return m->getPrice() >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Cooler* m) { return m->getPrice() <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Cooler* m) { return m->getPrice() != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Cooler* m) { return m->getPrice() < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Cooler* m) { return m->getPrice() > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Cooler* m) { return m->getPrice() == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<Cooler*>& filtered) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const Cooler* m) { return m->getPrice() < criteria && m->getPrice() > criteria2; }),filtered.end());
    }

    void filterByStock(int criteria, Operation operation, std::vector<Cooler*>& filtered) {
        std::function<bool(const Cooler*)> p = [&criteria](const Cooler* m) { return m->getStock() != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Cooler* m) { return m->getStock() >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Cooler* m) { return m->getStock() <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Cooler* m) { return m->getStock() != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Cooler* m) { return m->getStock() < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Cooler* m) { return m->getStock() > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Cooler* m) { return m->getStock() == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<Cooler> {
    public:
        Query<Cooler>(std::vector<Cooler*> all) : filtered(all) { }
        Query<Cooler>& filterBy(std::string _for, std::string _what, Operation _how) {
            CoolerQueryLambda cql;
            if (_for == "id") {
                cql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                cql.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "model") {
                cql.filterByModel(_what, _how, filtered);
            } else if (_for == "size") {
                cql.filterBySize(_what, _how, filtered);
            } else if (_for == "socket") {
                cql.filterBySocketSupport(_what, _how, filtered);
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
        std::vector<Cooler*> get() { return filtered; }
    private:
        std::vector<Cooler*> filtered;
};

#endif