#include "../hpp/power_supply.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

PowerSupply::PowerSupply(int id,
                         std::string manufacturer,
                         std::string model,
                         int capacity,
                         double price,
                         int stock) : Sector(id, manufacturer, price, stock), model(model), capacity(capacity) {}

std::string PowerSupply::getModel() const {
    return model;
}

int PowerSupply::getCapacity() const {
    return capacity;
}

std::vector<PowerSupply*> PowerSupply::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<PowerSupply*> out;

    std::string line;
    std::string part;
    while(getline(file, line)){
        std::vector<std::string> splitted;
        std::stringstream s(line);

        while (getline(s, part, '|')) {
            splitted.push_back(part);
        }

        if (splitted.size() != 6) continue;

        if (!isNumber(splitted[0]) || 
            !isNumber(splitted[3], true) || 
            !isNumber(splitted[4], true) || 
            !isNumber(splitted[5])) continue;

        out.push_back(new PowerSupply(
            std::stoi(splitted[0]),
            splitted[1],
            splitted[2],
            std::stod(splitted[3]),
            std::stod(splitted[4]),
            std::stoi(splitted[5])
        ));
    }

    file.close();
    return out;
}

std::string PowerSupply::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"model\":\"" + model +
            "\",\"capacity\":" + std::to_string(capacity) +
            ",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string PowerSupply::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "model") return model;
    if (str == "capacity") return std::to_string(capacity);
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> PowerSupply::getFields() {
    return {"id", "manufacturer", "model","capacity","price","stock"};
}