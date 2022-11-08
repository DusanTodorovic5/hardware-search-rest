#ifndef MOTHERBOARD_QUERY_CLASS
#define MOTHERBOARD_QUERY_CLASS

#include "iquery.hpp"
#include "../motherboard.hpp"

struct MotherboardQueryLambdas {
    void  filterByID(int criteria, Operation operation, std::vector<Motherboard*>& filtered){
        std::function<bool(const Motherboard*)> p = [&criteria](const Motherboard* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Motherboard* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Motherboard* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Motherboard* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Motherboard* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Motherboard* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Motherboard* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void  filterByMaker(std::string criteria, Operation operation, std::vector<Motherboard*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->manufacturer == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void  filterProcessor(std::string criteria, Operation operation, std::vector<Motherboard*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->processor == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->processor != criteria; }),filtered.end());
    }

    void  filterChipSocket(std::string criteria, Operation operation, std::vector<Motherboard*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->chipSocket == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->chipSocket != criteria; }),filtered.end());
    }

    void  filterByMBModel(std::string criteria, Operation operation, std::vector<Motherboard*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(),  [&criteria](const Motherboard* m) { return m->model == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const Motherboard* m) { return m->model != criteria; }),filtered.end());
    }

    void  filterByRamVersion(std::string criteria, Operation operation, std::vector<Motherboard*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(),  [&criteria](const Motherboard* m) { return m->ramVersion == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(),[&criteria](const Motherboard* m) { return m->ramVersion != criteria; }),filtered.end());
    }

    void  filterByM2SlotNumber(int criteria, Operation operation, std::vector<Motherboard*>& filtered){
        std::function<bool(const Motherboard*)> p = [&criteria](const Motherboard* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Motherboard* m) { return m->m2SlotNumber == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void  filterByM2SlotNumber(int criteria, int criteria2, Operation operation, std::vector<Motherboard*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const Motherboard* m) { return m->m2SlotNumber < criteria && m->m2SlotNumber > criteria2; }),filtered.end());
    }

    void  filterByPrice(double criteria, Operation operation, std::vector<Motherboard*>& filtered){
        std::function<bool(const Motherboard*)> p = [&criteria](const Motherboard* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Motherboard* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Motherboard* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Motherboard* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Motherboard* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Motherboard* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Motherboard* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void  filterByPrice(double criteria, double criteria2, Operation operation, std::vector<Motherboard*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const Motherboard* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

    void  filterByStock(int criteria, Operation operation, std::vector<Motherboard*>& filtered){
        std::function<bool(const Motherboard*)> p = [&criteria](const Motherboard* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const Motherboard* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const Motherboard* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const Motherboard* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const Motherboard* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const Motherboard* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const Motherboard* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<Motherboard> {
    public:
        Query<Motherboard>(std::vector<Motherboard*> all) : filtered(all) { }
        Query<Motherboard>& filterBy(std::string _for, std::string _what, Operation _how) {
            MotherboardQueryLambdas mql;
            if (_for == "id") {
                mql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                mql.filterByMaker(_what, _how, filtered);
            } else if (_for == "cpu") {
                mql.filterProcessor(_what, _how, filtered);
            } else if (_for == "chipSocket") {
                mql.filterChipSocket(_what, _how, filtered);
            } else if (_for == "model") {
                mql.filterByMBModel(_what, _how, filtered);
            } else if (_for == "ram") {
                mql.filterByRamVersion(_what, _how, filtered);
            } else if (_for == "m2Slots") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    mql.filterByM2SlotNumber(std::stoi(parts[0]),std::stoi(parts[1]), _how, filtered);
                } else {
                    mql.filterByM2SlotNumber(std::stoi(_what), _how, filtered);
                }
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    mql.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    mql.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                mql.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }
            
            return *this;
        }
        std::vector<Motherboard*> get() { return filtered; }
    private:
        std::vector<Motherboard*> filtered;
};

#endif