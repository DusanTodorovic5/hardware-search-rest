#ifndef REST_SERVER_CLASS
#define REST_SERVER_CLASS

#include "engine.hpp"
#include "../httplib.h"

class RestServer {
    public:
        RestServer(std::vector<std::string>);
        void listen();
    private:
        Engine engine;
        httplib::Server server;
};

#endif