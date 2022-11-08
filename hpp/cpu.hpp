#ifndef CPU_CLASS
#define CPU_CLASS

#include "sector.hpp"

class Motherboard;
class Cooler;

class CPU : public Sector {
    public:
        CPU(int id, 
            std::string manufacturer, 
            std::string chipSocket, 
            int generation, 
            std::string model, 
            std::string chipVersion,
            int coreCount,
            float baseFreq,
            float turboFreq,
            double price,
            int stock
        );
        int getGeneration() const; 
        std::string getModel() const; 
        std::string getChipVersion() const;
        std::string getChipSocket() const;
        int getCoreCount() const;
        float getBaseFreq() const;
        float getTurboFreq() const;
        void addMobo(Motherboard*);
        void addCooler(Cooler*);
        std::unordered_set<Motherboard*> getMobos();
        std::unordered_set<Cooler*> getCoolers(); 
        static std::vector<CPU*> load(std::string);
        std::string getValueFromString(std::string) override;
        std::vector<std::string> getFields() override;
        std::string toJson() override;
        friend class CPUQueryLambdas;
    private:
        std::string chipSocket;
        int generation; 
        std::string model; 
        std::string chipVersion;
        int coreCount;
        float baseFreq;
        float turboFreq;

        std::unordered_set<Motherboard*> mobos;
        std::unordered_set<Cooler*> coolers; 
};

#endif