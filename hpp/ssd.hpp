#ifndef SSD_CLASS
#define SSD_CLASS


#include "sector.hpp"

class SSD : public Sector {
    public:
        SSD(int id, 
            std::string manufacturer, 
            std::string model,
            std::string size,
            std::string PCISupport,
            double price,
            int stock
        );
        std::string getModel() const;
        std::string getSize() const;
        std::string getPCISupport() const;
        static std::vector<SSD*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class SSDQueryLambdas;
    private:
        std::string model;
        std::string size;
        std::string PCISupport;
};

#endif