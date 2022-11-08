#ifndef GPU_QUERY_CLASS
#define GPU_QUERY_CLASS

#include "iquery.hpp"
#include "../gpu.hpp"

struct GPUQueryLambdas {
    void filterByID(int criteria, Operation operation, std::vector<GPU*>& filtered){
        std::function<bool(const GPU*)>  p = [&criteria](const GPU* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const GPU* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const GPU* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const GPU* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const GPU* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const GPU* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const GPU* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByManufacturer(std::string criteria, Operation operation, std::vector<GPU*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->manufacturer == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void filterByMaker(std::string criteria, Operation operation, std::vector<GPU*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->maker == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->maker != criteria; }),filtered.end());
    }

    void filterByModel(std::string criteria, Operation operation, std::vector<GPU*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->model == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->model != criteria; }),filtered.end());
    }

    void filterByRAM(std::string criteria, Operation operation, std::vector<GPU*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->ram == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const GPU* m) { return m->ram != criteria; }),filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<GPU*>& filtered){
        std::function<bool(const GPU*)> p = [&criteria](const GPU* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const GPU* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const GPU* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const GPU* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const GPU* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const GPU* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const GPU* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<GPU*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const GPU* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

    void filterByStock(int criteria, Operation operation, std::vector<GPU*>& filtered){
        std::function<bool(const GPU*)> p = [&criteria](const GPU* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const GPU* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const GPU* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const GPU* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const GPU* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const GPU* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const GPU* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<GPU> {
    public:
        Query<GPU>(std::vector<GPU*> all) : filtered(all) { }
        Query<GPU>& filterBy(std::string _for, std::string _what, Operation _how) {
            GPUQueryLambdas gcl;
            if (_for == "id") {
                gcl.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                gcl.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "maker") {
                gcl.filterByMaker(_what, _how, filtered);
            } else if (_for == "model") {
                gcl.filterByModel(_what, _how, filtered);
            } else if (_for == "ram") {
                gcl.filterByRAM(_what, _how, filtered);
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    gcl.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    gcl.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                gcl.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }
            return *this;
        }
        std::vector<GPU*> get() { return filtered; }
    private:
        std::vector<GPU*> filtered;
};

#endif