#ifndef PCC_QUERY_CLASS
#define PCC_QUERY_CLASS

#include "iquery.hpp"
#include "../pc_case.hpp"

struct PcCaseQueryLambdas {
    void filterByID(int criteria, Operation operation, std::vector<PcCase*>& filtered){
        std::function<bool(const PcCase*)> p = [&criteria](const PcCase* m) { return m->id != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PcCase* m) { return m->id >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PcCase* m) { return m->id <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PcCase* m) { return m->id != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PcCase* m) { return m->id < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PcCase* m) { return m->id > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PcCase* m) { return m->id == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByManufacturer(std::string criteria, Operation operation, std::vector<PcCase*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->manufacturer == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->manufacturer != criteria; }),filtered.end());
    }

    void filterByModel(std::string criteria, Operation operation, std::vector<PcCase*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->model == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->model != criteria; }),filtered.end());
    }

    void filterByFrontPanel(std::string criteria, Operation operation, std::vector<PcCase*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->frontPanel == criteria; }),filtered.end());
            return ;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->frontPanel != criteria; }),filtered.end());
    }

    void filterByTopPanel(std::string criteria, Operation operation, std::vector<PcCase*>& filtered){
        if (operation == Operation::NotEqual) {
            filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->topPanel == criteria; }),filtered.end());
            return;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria](const PcCase* m) { return m->topPanel != criteria; }),filtered.end());
    }

    void filterByPrice(double criteria, Operation operation, std::vector<PcCase*>& filtered){
        std::function<bool(const PcCase*)> p = [&criteria](const PcCase* m) { return m->price != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PcCase* m) { return m->price >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PcCase* m) { return m->price <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PcCase* m) { return m->price != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PcCase* m) { return m->price < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PcCase* m) { return m->price > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PcCase* m) { return m->price == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }

    void filterByPrice(double criteria, double criteria2, Operation operation, std::vector<PcCase*>& filtered){
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&criteria, &criteria2](const PcCase* m) { return m->price < criteria && m->price > criteria2; }),filtered.end());
    }

    void filterByStock(int criteria, Operation operation, std::vector<PcCase*>& filtered){
        std::function<bool(const PcCase*)> p = [&criteria](const PcCase* m) { return m->stock != criteria; };
        switch (operation) {
            case Operation::LessThan : p = [&criteria](const PcCase* m) { return m->stock >= criteria; }; break;
            case Operation::BiggerThan : p = [&criteria](const PcCase* m) { return m->stock <= criteria; }; break;
            case Operation::Equal : p = [&criteria](const PcCase* m) { return m->stock != criteria; }; break;
            case Operation::NotLessThan : p = [&criteria](const PcCase* m) { return m->stock < criteria; }; break;
            case Operation::NotBiggerThan : p = [&criteria](const PcCase* m) { return m->stock > criteria; }; break;
            case Operation::NotEqual : p = [&criteria](const PcCase* m) { return m->stock == criteria; }; break;
        }
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), p),filtered.end());
    }
}; 

template<>
class Query<PcCase> {
    public:
        Query<PcCase>(std::vector<PcCase*> all) : filtered(all) { }
        Query<PcCase>& filterBy(std::string _for, std::string _what, Operation _how) {
            PcCaseQueryLambdas pql;
            if (_for == "id") {
                pql.filterByID(std::stoi(_what), _how, filtered);
            } else if (_for == "manufacturer") {
                pql.filterByManufacturer(_what, _how, filtered);
            } else if (_for == "model") {
                pql.filterByModel(_what, _how, filtered);
            } else if (_for == "frontPanel") {
                pql.filterByFrontPanel(_what, _how, filtered);
            } else if (_for == "topPanel") {
                pql.filterByTopPanel(_what, _how, filtered);
            }else if (_for == "price") {
                if (_how == Operation::Between) {
                    std::vector<std::string> parts = split(_what);
                    pql.filterByPrice(std::stod(parts[0]),std::stod(parts[1]), _how, filtered);
                } else {
                    pql.filterByPrice(std::stod(_what), _how, filtered);
                }
            } else if (_for == "stock") {
                pql.filterByStock(std::stoi(_what), _how, filtered);
            } else { return *this; }

            return *this;
        }
        std::vector<PcCase*> get() { return filtered; }
    private:
        std::vector<PcCase*> filtered; 
};

#endif