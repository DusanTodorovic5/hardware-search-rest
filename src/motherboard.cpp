#include "../hpp/motherboard.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

Motherboard::Motherboard(int id,
                        std::string manufacturer,
                        std::string processor,
                        std::string chipSocket,
                        std::string model,
                        std::string ramVersion,
                        int m2SlotNumber,
                        double price,
                        int stock) : Sector(id, manufacturer, price, stock), processor(processor), chipSocket(chipSocket), 
                        model(model), ramVersion(ramVersion), m2SlotNumber(m2SlotNumber) {}


std::string Motherboard::getProcessor() const {
    return processor;
}

std::string Motherboard::getChipSocket() const {
    return chipSocket;
}

std::string Motherboard::getModel() const {
    return model;
}

std::string Motherboard::getRamVersion() const {
    return ramVersion;
}

int Motherboard::getM2SlotNumber() const {
    return m2SlotNumber;
}

void Motherboard::addCPU(CPU* cpu) {
    processors.insert(cpu);
}
std::unordered_set<CPU*> Motherboard::getRightProcessors() {
    return this->processors;
}

std::vector<Motherboard*> Motherboard::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<Motherboard*> out;

    std::string line;
    std::string part;
    while(getline(file, line)){
        std::vector<std::string> splitted;
        std::stringstream s(line);

        while (getline(s, part, '|')) {
            splitted.push_back(part);
        }

        if (splitted.size() != 9) continue;

        if (!isNumber(splitted[0]) || 
            !isNumber(splitted[6]) || 
            !isNumber(splitted[7], true) || 
            !isNumber(splitted[8])) continue;

        out.push_back(new Motherboard(
            std::stoi(splitted[0]),
            splitted[1],
            splitted[2],
            splitted[3],
            splitted[4],
            splitted[5],
            std::stoi(splitted[6]),
            std::stod(splitted[7]),
            std::stoi(splitted[8])
        ));
    }

    file.close();
    return out;
}

std::string Motherboard::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"processor\":\"" + processor +
            "\",\"chipSocket\":\"" + chipSocket +
            "\",\"model\":\"" + model +
            "\",\"ramVersion\":\"" + ramVersion +
            "\",\"m2SlotNumber\":" + std::to_string(m2SlotNumber) +
            ",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string Motherboard::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "processor") return processor;
    if (str == "chipSocket") return chipSocket;
    if (str == "model") return model;
    if (str == "ramVersion") return ramVersion;
    if (str == "m2SlotNumber") return std::to_string(m2SlotNumber);
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> Motherboard::getFields() {
    return {"id", "manufacturer", "processor","chipSocket","model","ramVersion","m2SlotNumber","price","stock"};
}