#ifndef RAM_QUERY_CLASS
#define RAM_QUERY_CLASS

#include "iquery.hpp"
#include "../ram.hpp"

struct RamQueryLambdas {
    void filterByID(int criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByManufacturer(std::string criteria, Operation operation, std::vector<RAM*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->manufacturer == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void filterByModel(std::string criteria, Operation operation, std::vector<RAM*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->model == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->model != criteria; }),filtered.end());
    }

    void filterByRAMVersion(std::string criteria, Operation operation, std::vector<RAM*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->version == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const RAM* m) { return m->version != criteria; }),filtered.end());
    }

    void filterByCapacity(int criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->capacity != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->capacity >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->capacity <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->capacity != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->capacity < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->capacity > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->capacity == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByCapacity(int criteria, int criteria2, Operation operation, std::vector<RAM*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const RAM* m) { return m->capacity < criteria && m->capacity > criteria2; }),filtered.end());
    }

    void filterByMhz(int criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->mhz != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->mhz >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->mhz <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->mhz != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->mhz < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->mhz > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->mhz == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByMhz(int criteria, int criteria2, Operation operation, std::vector<RAM*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const RAM* m) { return m->mhz < criteria && m->mhz > criteria2; }),filtered.end());
    }

    void filterByCl(int criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->cl != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->cl >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->cl <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->cl != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->cl < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->cl > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->cl == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByCl(int criteria, int criteria2, Operation operation, std::vector<RAM*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const RAM* m) { return m->cl < criteria && m->cl > criteria2; }),filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end()); 
    }

    void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<RAM*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const RAM* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

    void filterByStock(double criteria, Operation operation, std::vector<RAM*>& filtered){
        std::function<bool(const RAM*)> p = [&criteria](const RAM* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const RAM* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const RAM* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const RAM* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const RAM* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const RAM* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const RAM* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<RAM> {
    public:
        Query<RAM>(std::vector<RAM*> all) : filtered(all) { }
        Query<RAM>& filterBy(std::string _for, std::string _what, Operation _how) {
            RamQueryLambdas rql;
            if (_for == "id") {
                rql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                rql.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "model") {
                rql.filterByModel(_what, _how, filtered);
            } else if (_for == "ram") {
                rql.filterByRAMVersion(_what, _how, filtered);
            } else if (_for == "capacity") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    rql.filterByCapacity(std::stoi(parts[0]),std::stoi(parts[1]), _how, filtered);
                } else {
                    rql.filterByCapacity(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "mhz") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    rql.filterByMhz(std::stoi(parts[0]),std::stoi(parts[1]), _how, filtered);
                } else {
                    rql.filterByMhz(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "cl") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    rql.filterByCl(std::stoi(parts[0]),std::stoi(parts[1]), _how, filtered);
                } else {
                    rql.filterByCl(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    rql.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    rql.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                rql.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }

            return *this;
        }
        std::vector<RAM*> get() { return filtered; }
private:
    std::vector<RAM*> filtered;
};

#endif