#ifndef COOLER_CLASS
#define COOLER_CLASS

#include "sector.hpp"

class Cooler : public Sector {
    public:
        Cooler(int id, 
            std::string manufacturer, 
            std::string model,
            std::string size,
            std::string socketSupport,
            double price,
            int stock
        );
        std::string getModel() const;
        std::string getSize() const;
        std::string getSocketSupport() const;
        static std::vector<Cooler*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class CoolerQueryLambda;
    private:
        std::string model;
        std::string size;
        std::string socketSupport;
};

#endif