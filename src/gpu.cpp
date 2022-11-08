#include "../hpp/gpu.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

GPU::GPU(int id,
         std::string manufacturer,
         std::string maker,
         std::string model,
         std::string ram,
         double price,
         int stock) : Sector(id, manufacturer, price, stock), maker(maker), model(model), ram(ram) {}

std::string GPU::getMaker() const {
    return maker;
}

std::string GPU::getModel() const {
    return model;
}

std::string GPU::getRam() const {
    return ram;
}

std::vector<GPU*> GPU::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<GPU*> out;

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

        out.push_back(new GPU(
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

std::string GPU::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"maker\":\"" + maker +
            "\",\"model\":\"" + model +
            "\",\"ram\":\"" + ram +
            "\",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string GPU::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "maker") return maker;
    if (str == "model") return model;
    if (str == "ram") return ram;
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> GPU::getFields() {
    return {"id", "manufacturer", "maker","model","ram","price","stock"};
}