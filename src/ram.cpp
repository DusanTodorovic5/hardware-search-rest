#include "../hpp/ram.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

RAM::RAM(int id,
         std::string manufacturer,
         std::string model,
         std::string version,
         int capacity,
         int mhz,
         int cl,
         double price,
         int stock) : Sector(id, manufacturer, price, stock), model(model), version(version), capacity(capacity), mhz(mhz), cl(cl) {}

std::string RAM::getModel() const {
    return model;
}

std::string RAM::getVersion() const {
    return version;
}

int RAM::getCapacity() const {
    return capacity;
}

int RAM::getMhz() const {
    return mhz;
}

std::vector<RAM*> RAM::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<RAM*> out;

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
            !isNumber(splitted[4]) || 
            !isNumber(splitted[5]) || 
            !isNumber(splitted[6]) || 
            !isNumber(splitted[7], true) || 
            !isNumber(splitted[8])) continue;

        out.push_back(new RAM(
            std::stoi(splitted[0]),
            splitted[1],
            splitted[2],
            splitted[3],
            std::stoi(splitted[4]),
            std::stoi(splitted[5]),
            std::stoi(splitted[6]),
            std::stod(splitted[7]),
            std::stoi(splitted[8])
        ));
    }

    file.close();
    return out;
}

std::string RAM::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"model\":\"" + model +
            "\"version\":\"" + model +
            "\",\"capacity\":" + std::to_string(capacity) +
            ",\"mhz\":" + std::to_string(mhz) +
            ",\"cl\":" + std::to_string(cl) +
            ",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string RAM::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "model") return model;
    if (str == "version") return version;
    if (str == "capacity") return std::to_string(capacity);
    if (str == "mhz") return std::to_string(mhz);
    if (str == "cl") return std::to_string(cl);
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> RAM::getFields() {
    return {"id", "manufacturer", "model","version","mhz","cl","price","stock"};
}