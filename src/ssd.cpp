#include "../hpp/ssd.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

SSD::SSD(int id,
         std::string manufacturer,
         std::string model,
         std::string size,
         std::string PCISupport,
         double price,
         int stock) : Sector(id, manufacturer, price, stock), model(model), size(size), PCISupport(PCISupport) {}


std::string SSD::getModel() const {
    return model;
}
std::string SSD::getSize() const {
    return size;
}
std::string SSD::getPCISupport() const {
    return PCISupport;
}

std::vector<SSD*> SSD::load(std::string filename) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename,std::ios::in);

    std::vector<SSD*> out;

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

        out.push_back(new SSD(
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

std::string SSD::toJson() {
    return "{\"id\":" + std::to_string(id) + "," +
            "\"manufacturer\":\"" + manufacturer + "\"," +
            "\"model\":\"" + model +
            "\"size\":\"" + size +
            "\"PCISupport\":\"" + PCISupport +
            "\",\"price\":" + std::to_string(price) +
            ",\"stock\":" + std::to_string(stock) + "}";
}

std::string SSD::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "model") return model;
    if (str == "size") return size;
    if (str == "PCISupport") return PCISupport;
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> SSD::getFields() {
    return {"id", "manufacturer", "model","size","PCISupport","price","stock"};
}