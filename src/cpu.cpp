#include "../hpp/cpu.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

CPU::CPU(int id,
         std::string manufacturer,
        std::string chipSocket,
         int generation,
         std::string model,
         std::string chipVersion,
         int coreCount,
         float baseFreq,
         float turboFreq,
         double price,
         int stock) : Sector(id, manufacturer, price, stock), chipSocket(chipSocket), generation(generation), model(model),
                      chipVersion(chipVersion), coreCount(coreCount), baseFreq(baseFreq), turboFreq(turboFreq) {}
                      
int CPU::getGeneration() const {
    return generation;
}

std::string CPU::getModel() const {
    return model;
}

std::string CPU::getChipSocket() const {
    return chipSocket;
}

std::string CPU::getChipVersion() const {
    return chipVersion;
}

int CPU::getCoreCount() const {
    return coreCount;
}

float CPU::getBaseFreq() const {
    return baseFreq;
}

float CPU::getTurboFreq() const {
    return turboFreq;
}

std::vector<CPU*> CPU::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<CPU*> out;

    std::string line;
    std::string part;
    while(getline(file, line)){
        std::vector<std::string> splitted;
        std::stringstream s(line);

        while (getline(s, part, '|')) {
            splitted.push_back(part);
        }

        if (splitted.size() != 11) continue;

        if (!isNumber(splitted[0]) || 
            !isNumber(splitted[3]) || 
            !isNumber(splitted[6]) || 
            !isNumber(splitted[7], true) || 
            !isNumber(splitted[8], true) || 
            !isNumber(splitted[9], true) || 
            !isNumber(splitted[10])) continue;

        out.push_back(new CPU(
            std::stoi(splitted[0]),
            splitted[1],
            splitted[2],
            std::stoi(splitted[3]),
            splitted[4],
            splitted[5],
            std::stoi(splitted[6]),
            std::stod(splitted[7]),
            std::stod(splitted[8]),
            std::stod(splitted[9]),
            std::stoi(splitted[10])
        ));
    }

    file.close();
    return out;
}

void CPU::addMobo(Motherboard* mobo) {
    this->mobos.insert(mobo);
}

void CPU::addCooler(Cooler* cooler) {
    this->coolers.insert(cooler);
}

std::unordered_set<Motherboard*> CPU::getMobos() {
    return this->mobos;
}

std::unordered_set<Cooler*> CPU::getCoolers() {
    return this->coolers;
}

std::string CPU::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
        "\"manufacturer\":\"" + manufacturer + "\"," +
        "\"chipSocket\":\"" + chipSocket +
        "\",\"generation\":" + std::to_string(generation) +
        ",\"model\":\"" + model +
        "\",\"chipVersion\":\"" + chipVersion +
        "\",\"coreCount\":" + std::to_string(coreCount) +
        ",\"baseFreq\":" + std::to_string(baseFreq) +
        ",\"turboFreq\":" + std::to_string(turboFreq) +
        ",\"price\":" + std::to_string(price) +
        ",\"stock\":" + std::to_string(stock) + "}";
}

std::string CPU::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "chipSocket") return chipSocket;
    if (str == "generation") return std::to_string(generation);
    if (str == "model") return model;
    if (str == "chipVersion") return chipVersion;
    if (str == "coreCount") return std::to_string(coreCount);
    if (str == "baseFreq") return std::to_string(baseFreq);
    if (str == "turboFreq") return std::to_string(turboFreq);
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}

std::vector<std::string> CPU::getFields() {
    return {"id", "manufacturer", "chipSocket","generation","model","chipVersion","coreCount"
    ,"baseFreq","turboFreq","price","stock"};
}