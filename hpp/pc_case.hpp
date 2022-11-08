#ifndef PC_CASE_CLASS
#define PC_CASE_CLASS


#include "sector.hpp"

class Cooler;

class PcCase : public Sector {
    public:
        PcCase(int id, 
            std::string manufacturer, 
            std::string model,
            std::string frontPanel,
            std::string backPanel,
            double price,
            int stock
        );
        std::string getModel() const;
        std::string getFrontPanel() const;
        std::string getTopPanel() const;
        void addTopCooler(Cooler*);
        void addFrontCooler(Cooler*);
        std::unordered_set<Cooler*> getTopCoolers();
        std::unordered_set<Cooler*> getFrontCoolers();
        static std::vector<PcCase*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class PcCaseQueryLambdas;
    private:
        std::string model;
        std::string frontPanel;
        std::string topPanel;
        std::unordered_set<Cooler*> topCoolers;
        std::unordered_set<Cooler*> frontCoolers;
};

#endif