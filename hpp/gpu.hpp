#ifndef GPU_CLASS
#define GPU_CLASS


#include "sector.hpp"

class GPU : public Sector {
    public:
        GPU(int id, 
            std::string manufacturer, 
            std::string maker, 
            std::string model,
            std::string ram,
            double price,
            int stock
        );
        std::string getMaker() const;
        std::string getModel() const;
        std::string getRam() const;
        static std::vector<GPU*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class GPUQueryLambdas;
    private:
        std::string maker;
        std::string model;
        std::string ram;
};

#endif