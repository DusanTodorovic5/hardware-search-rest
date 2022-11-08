#include "../hpp/cooler.hpp"
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../hpp/util.hpp"

Cooler::Cooler(int id,
               std::string manufacturer,
               std::string model,
               std::string size,
               std::string socketSupport,
               double price,
               int stock) : Sector(id, manufacturer, price, stock), model(model), size(size), socketSupport(socketSupport) {}

std::string Cooler::getModel() const {
    return model;
}

std::string Cooler::getSize() const {
    return size;
}

std::string Cooler::getSocketSupport() const {
    return socketSupport;
}

std::vector<Cooler*> Cooler::load(std::string filename) {
        struct stat buffer;
    if (stat (filename.c_str(), &buffer) != 0) return {};

    std::fstream file;
    file.open(filename, std::ios::in);

    std::vector<Cooler*> out;

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

        out.push_back(new Cooler(
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
std::string Cooler::toJson() {
    std::string json = "{\"id\":" + std::to_string(id) + "," +
    "\"manufacturer\":\"" + manufacturer + "\"," +
    "\"model\":\"" + model +
    "\",\"size\":\"" + size +
    "\",\"socketSupport\":\"" + socketSupport +
    "\",\"price\":" + std::to_string(price) +
    ",\"stock\":" + std::to_string(stock) + "}";

    return json;
}

std::string Cooler::getValueFromString(std::string str) {
    if (str == "id") return std::to_string(id);
    if (str == "manufacturer") return manufacturer;
    if (str == "model") return model;
    if (str == "size") return size;
    if (str == "socketSupport") return socketSupport;
    if (str == "price") return std::to_string(price);
    if (str == "stock") return std::to_string(stock);
    return "";
}
std::vector<std::string> Cooler::getFields() {
    return {"id", "manufacturer", "model","size","socketSupport","price","stock"};
}