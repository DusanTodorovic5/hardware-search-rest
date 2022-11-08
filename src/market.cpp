#include "../hpp/market.hpp"
#include <algorithm>
#include "../hpp/query/cpu_query.hpp"
#include "../hpp/query/gpu_query.hpp"
#include "../hpp/query/cooler_query.hpp"
#include "../hpp/query/motherboard_query.hpp"
#include "../hpp/query/pc_case_query.hpp"
#include "../hpp/query/psu_query.hpp"
#include "../hpp/query/ram_query.hpp"
#include "../hpp/query/ssd_query.hpp"
#include <string>
#include <sstream>

Market::Market(std::string name) : name(name) {
    this->cpus = CPU::load(name + "/cpus");
    this->motherboards = Motherboard::load(name + "/mobos");
    this->gpus = GPU::load(name + "/gpus");
    this->powerSupplies = PowerSupply::load(name + "/psus");
    this->rams = RAM::load(name + "/ram");
    this->cases = PcCase::load(name + "/cases");
    this->ssds = SSD::load(name + "/ssds");
    this->coolers = Cooler::load(name + "/coolers");

    for (CPU* cpu : cpus) {
        for (Motherboard* mobo : motherboards) {
            if (mobo->getChipSocket() == cpu->getChipSocket() && mobo->getProcessor() == cpu->getManufacturer()) {
                mobo->addCPU(cpu);
                cpu->addMobo(mobo);                
            }
        }

        for (Cooler* cooler : coolers) {
            std::vector<std::string> m_cpus = split(cooler->getSocketSupport(), "-");
            if (std::find(m_cpus.begin(), m_cpus.end(), cpu->getChipSocket()) != m_cpus.end()) {
                cpu->addCooler(cooler);
            }
        }
    }

    for (PcCase* _case : cases) {
        for (Cooler* cooler : coolers) {
            if (cooler->getSize() == _case->getFrontPanel()) {
                _case->addFrontCooler(cooler);
            }

            if (cooler->getSize() == _case->getTopPanel()) {
                _case->addTopCooler(cooler);
            }
        }
    }
}

Market::~Market() {
    for (auto el : cpus) delete el;
    for (auto el : gpus) delete el;
    for (auto el : motherboards) delete el;
    for (auto el : powerSupplies) delete el;
    for (auto el : coolers) delete el;
    for (auto el : cases) delete el;
    for (auto el : ssds) delete el;
    for (auto el : rams) delete el;
}

std::string Market::getName() const {
    return this->name;
}

template<>
Query<CPU> Market::getQuery(){ return Query<CPU>(this->cpus); }
template<>
Query<Motherboard> Market::getQuery(){ return Query<Motherboard>(this->motherboards); }
template<>
Query<GPU> Market::getQuery(){ return Query<GPU>(this->gpus); }
template<>
Query<PcCase> Market::getQuery(){ return Query<PcCase>(this->cases); }
template<>
Query<PowerSupply> Market::getQuery(){ return Query<PowerSupply>(this->powerSupplies); }
template<>
Query<RAM> Market::getQuery(){ return Query<RAM>(this->rams); }
template<>
Query<Cooler> Market::getQuery(){ return Query<Cooler>(this->coolers); }
template<>
Query<SSD> Market::getQuery(){ return Query<SSD>(this->ssds); }

void Market::add(std::vector<std::string> entries) {
    std::string part;
    for (std::string entry : entries) {
        std::vector<std::string> splitted;
        std::stringstream s(entry);

        while (getline(s, part, '|')) {
            splitted.push_back(part);
        }

        if (splitted.size() == 3) {
            if (splitted[0] == "CPU") {
                for (CPU* el : cpus) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "Motherboard") {
                for (Motherboard* el : motherboards) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "GPU") {
                for (GPU* el : gpus) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "RAM") {
                for (RAM* el : rams) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "PowerSupply") {
                for (PowerSupply* el : powerSupplies) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }
            if (splitted[0] == "PcCase") {
                for (PcCase* el : cases) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "Cooler") {
                for (Cooler* el : coolers) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }

            if (splitted[0] == "SSD") {
                for (SSD* el : ssds) {
                    if (el->getId() == std::stoi(splitted[1])) {
                        el->add(std::stoi(splitted[2]));
                        break;
                    }
                }
                continue;
            }
        }
    }
}