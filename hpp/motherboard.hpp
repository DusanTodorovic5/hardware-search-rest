#ifndef Motherboard_CLASS
#define Motherboard_CLASS

#include "cpu.hpp"

class Motherboard : public Sector {
    public:
        Motherboard(int id, 
            std::string manufacturer, 
            std::string processor, 
            std::string chipSocket,
            std::string model,
            std::string ramVersion,
            int m2SlotNumber,
            double price,
            int stock
        );
        std::string getProcessor() const;
        std::string getChipSocket() const;
        std::string getModel() const;
        std::string getRamVersion() const;
        int getM2SlotNumber() const;
        void addCPU(CPU*);
        std::unordered_set<CPU*> getRightProcessors();
        static std::vector<Motherboard*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class MotherboardQueryLambdas;
    private:
        std::string processor;
        std::string chipSocket;
        std::string model;
        std::string ramVersion;
        int m2SlotNumber;

        std::unordered_set<CPU*> processors;
};

#endif