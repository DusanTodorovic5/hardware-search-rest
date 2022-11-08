#ifndef SSD_QUERY_CLASS
#define SSD_QUERY_CLASS

#include "iquery.hpp"
#include "../ssd.hpp"

struct SSDQueryLambdas {
   void filterByID(int criteria, Operation operation, std::vector<SSD*>& filtered){
     std::function<bool(const SSD*)> p = [&criteria](const SSD* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const SSD* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const SSD* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const SSD* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const SSD* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const SSD* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const SSD* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

   void filterByManufacturer(std::string criteria, Operation operation, std::vector<SSD*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->manufacturer == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->manufacturer != criteria; }),filtered.end());
    }   

   void filterByModel(std::string criteria, Operation operation, std::vector<SSD*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->model == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->model != criteria; }),filtered.end());
    }

   void filterBySize(std::string criteria, Operation operation, std::vector<SSD*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->size == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->size != criteria; }),filtered.end());

    }

   void filterByPCISupport(std::string criteria, Operation operation, std::vector<SSD*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->PCISupport == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const SSD* m) { return m->PCISupport != criteria; }),filtered.end());
    }

   void filterByPrice(double criteria, Operation operation, std::vector<SSD*>& filtered){
    std::function<bool(const SSD*)> p = [&criteria](const SSD* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const SSD* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const SSD* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const SSD* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const SSD* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const SSD* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const SSD* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

   void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<SSD*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(),[&criteria, &criteria2](const SSD* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

   void filterByStock(int criteria, Operation operation, std::vector<SSD*>& filtered){
        std::function<bool(const SSD*)> p = [&criteria](const SSD* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const SSD* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const SSD* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const SSD* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const SSD* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const SSD* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const SSD* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
};

template<>
class Query<SSD> {
    public:
        Query<SSD>(std::vector<SSD*> all) : filtered(all) { }
        Query<SSD>& filterBy(std::string _for, std::string _what, Operation _how) {
            SSDQueryLambdas sql;
            if (_for == "id") {
                sql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                sql.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "model") {
                sql.filterByModel(_what, _how, filtered);
            } else if (_for == "size") {
                sql.filterBySize(_what, _how, filtered);
            } else if (_for == "pci") {
                sql.filterByPCISupport(_what, _how, filtered);
            } else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    sql.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    sql.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                sql.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }

            return *this;
        }
        std::vector<SSD*> get() { return filtered; }
    private:
        std::vector<SSD*> filtered;
};

#endif