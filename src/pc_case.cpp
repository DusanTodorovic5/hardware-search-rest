#include "../hpp/pc_case.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

PcCase::PcCase(int id,
               std::string manufacturer,
               std::string model,
               std::string frontPanel,
               std::string backPanel,
               double price,
               int stock) : Sector(id, manufacturer, price, stock), model(model), frontPanel(frontPanel), topPanel(backPanel) {}

std::string PcCase::getModel() const {
    return model;
}

std::string PcCase::getFrontPanel() const {
    return frontPanel;
}

std::string PcCase::getTopPanel() const {
    return topPanel;
}

std::vector<PcCase*> PcCase::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<PcCase*> out;

    std::string line;
    std::string part;
    while(getline(file, line)){
        std::vector<std::string> splitted;
        std::stringstream s(line);

        while (getline(s, part, '|')) {
            splitted.push_back(part);
        }

        if (splitted.size() != 7) continue;

        if (!isNumber(splitted[0]) || 
            !isNumber(splitted[5], true) || 
            !isNumber(splitted[6])) continue;

        out.push_back(new PcCase(
            std::stoi(splitted[0]),
            splitted[1],
            splitted[2],
            splitted[3],
            splitted[4],
            std::stod(splitted[5]),
            std::stoi(splitted[6])
        ));
    }

    file.close();
    return out;
}

void PcCase::addTopCooler(Cooler* cooler) {
    topCoolers.insert(cooler);
}

void PcCase::addFrontCooler(Cooler* cooler) {
    frontCoolers.insert(cooler);
}

std::unordered_set<Cooler*> PcCase::getTopCoolers() {
    return topCoolers;
}

std::unordered_set<Cooler*> PcCase::getFrontCoolers() {
    return frontCoolers;
}

std::string PcCase::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"model\":\"" + model +
            "\",\"frontPanel\":\"" + frontPanel +
            "\",\"topPanel\":\"" + topPanel +
            "\",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string PcCase::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "model") return model;
    if (str == "frontPanel") return frontPanel;
    if (str == "topPanel") return topPanel;
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> PcCase::getFields() {
    return {"id", "manufacturer", "model","frontPanel","topPanel","price","stock"};
}