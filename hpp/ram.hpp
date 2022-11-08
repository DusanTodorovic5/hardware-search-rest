#ifndef RAM_CLASS
#define RAM_CLASS


#include "sector.hpp"

class RAM : public Sector {
    public:
        RAM(int id, 
            std::string manufacturer, 
            std::string model,
            std::string version,
            int capacity,
            int mhz,
            int cl,
            double price,
            int stock
        );
        std::string getModel() const;
        std::string getVersion() const;
        int getCapacity() const;
        int getMhz() const;
        int getCl() const;
        static std::vector<RAM*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class RamQueryLambdas;
    private:
        std::string model;
        std::string version;
        int capacity;
        int mhz;
        int cl;
};

#endif