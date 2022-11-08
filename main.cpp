#include <iostream>
#include "hpp/rest_server.hpp"

const std::string query1 = "{\"action\" : \"info\",\"type\" : \"cpu\",\"filter\": [{\"name\" : \"=;I9 12900k\",\"cores\" : \"=;12\"},{\"socket\" : {\"type\" : \"motherboard\",\"filter\" : {\"name\" : \"=;MSI H170a\"}}}]}";

int main(int, char**) {
    RestServer rs({"market1", "market2", "market3"});

    rs.listen();

    return 0;
}