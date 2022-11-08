#ifndef POWER_SUPPLY_CLASS
#define POWER_SUPPLY_CLASS


#include "sector.hpp"

class PowerSupply : public Sector {
    public:
        PowerSupply(int id, 
            std::string manufacturer, 
            std::string model,
            int capacity,
            double price,
            int stock
        );
        std::string getModel() const;
        int getCapacity() const;
        static std::vector<PowerSupply*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class PSUQueryLambdas;
    private:
        std::string model;
        int capacity;
};

#endif