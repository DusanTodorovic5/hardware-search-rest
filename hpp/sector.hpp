#ifndef SECTOR_INTERFACE
#define SECTOR_INTERFACE

#include <string>
#include <vector>
#include <unordered_set>
#include <mutex>

class Sector {
    public:
        Sector(int id, std::string manufacturer, double price, int stock) : 
            id(id), manufacturer(manufacturer), price(price), stock(stock) { }
        inline int getId() const { return id; }
        inline std::string getManufacturer() const { return manufacturer; }
        inline double getPrice() const { return price; }
        inline int getStock() const { return stock; }
        bool buy(int count) {
            std::lock_guard<std::mutex> guard(mutex);
            if (stock >= count) {
                stock -= count;
                return true;
            }
            return false;
        }
        void add(int amount) {
            std::lock_guard<std::mutex> guard(mutex);
            stock += amount;
        }
        inline bool operator() (const Sector& struct1, const Sector& struct2) {
            return (struct1.price < struct2.price);
        }
        virtual std::string getValueFromString(std::string) = 0;
        virtual std::string toJson() = 0;
        virtual std::vector<std::string> getFields() = 0;
        static std::string compare(Sector* s1, Sector* s2) {
            std::vector<std::string> differences;
            std::string json = "{\"sector1\":" + s1->toJson() + ",\"sector2\":" + s2->toJson() + ",\"differences\":[";
            
            for (std::string s : s1->getFields()) {
                if (s1->getValueFromString(s) != s2->getValueFromString(s)) {
                    differences.push_back("{\"1\":\"" + 
                                        s1->getValueFromString(s) + 
                                        "\",\"2\":\"" + 
                                        s2->getValueFromString(s) + "\"}");
                }
            }

            for (int i=0;i<differences.size();i++) {
                json += differences[i];
                json += ((i == differences.size() - 1) ? "]}" : ",");
            }
            if (differences.size() == 0) {
                json += "]}";
            }
            return json;
        }
        template <class T>
        friend class Query;
    protected:
        int id;
        std::string manufacturer;
        double price;
        int stock;
        std::mutex mutex;
};

#endif