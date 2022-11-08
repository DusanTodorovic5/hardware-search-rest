#ifndef PSU_QUERY_CLASS
#define PSU_QUERY_CLASS

#include "iquery.hpp"
#include "../power_supply.hpp"

struct PSUQueryLambdas {
    void filterByID(int criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        std::function<bool(const PowerSupply*)> p = [&criteria](const PowerSupply* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PowerSupply* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PowerSupply* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PowerSupply* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PowerSupply* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PowerSupply* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PowerSupply* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByManufacturer(std::string criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PowerSupply* m) { return m->manufacturer == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PowerSupply* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void filterByModel(std::string criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PowerSupply* m) { return m->model == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PowerSupply* m) { return m->model != criteria; }),filtered.end());
    }

    void filterByCapacity(int criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        std::function<bool(const PowerSupply*)> p = [&criteria](const PowerSupply* m) { return m->capacity != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PowerSupply* m) { return m->capacity >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PowerSupply* m) { return m->capacity <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PowerSupply* m) { return m->capacity != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PowerSupply* m) { return m->capacity < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PowerSupply* m) { return m->capacity > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PowerSupply* m) { return m->capacity == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByCapacity(int criteria, int criteria2, Operation operation, std::vector<PowerSupply*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const PowerSupply* m) { return m->capacity < criteria && m->capacity > criteria2; }),filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        std::function<bool(const PowerSupply*)> p = [&criteria](const PowerSupply* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PowerSupply* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PowerSupply* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PowerSupply* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PowerSupply* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PowerSupply* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PowerSupply* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<PowerSupply*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const PowerSupply* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

    void filterByStock(int criteria, Operation operation, std::vector<PowerSupply*>& filtered){
        std::function<bool(const PowerSupply*)> p = [&criteria](const PowerSupply* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PowerSupply* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PowerSupply* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PowerSupply* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PowerSupply* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PowerSupply* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PowerSupply* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<PowerSupply> {
    public:
        Query<PowerSupply>(std::vector<PowerSupply*> all) : filtered(all) { }
        Query<PowerSupply>& filterBy(std::string _for, std::string _what, Operation _how) {
            PSUQueryLambdas pcl;
            if (_for == "id") {
                pcl.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                pcl.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "model") {
                pcl.filterByModel(_what, _how, filtered);
            } else if (_for == "capacity") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    pcl.filterByCapacity(std::stoi(parts[0]),std::stoi(parts[1]), _how, filtered);
                } else {
                    pcl.filterByCapacity(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    pcl.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    pcl.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                pcl.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }
            return *this;
        }
        std::vector<PowerSupply*> get() { return filtered; }
    private:
        std::vector<PowerSupply*> filtered;
};

#endif