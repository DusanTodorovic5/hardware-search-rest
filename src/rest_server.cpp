#include "../hpp/rest_server.hpp"

RestServer::RestServer(std::vector<std::string> markets) : engine(markets) {
    server.Post("/query", [this](const httplib::Request& req, httplib::Response& res){
        
        Parser p(req.body);

        QueryCriterium* qc = p();
        if (!qc) {
            res.set_content("Error durring parsing!", "text/plain");
            return;
        }

        std::string sc;

        switch (qc->action) {
            case Action::INFO: 
                sc = engine.query(qc); 
            break;
            case Action::BUY:
            case Action::BUY_ANYWAYS: 
                sc = engine.buyQuery(qc); 
            case Action::DIFF:
                sc = engine.diffQuery(qc);
            break;
        }
            
        res.set_content(sc, "text/plain");
        delete qc;
    });

    server.Post("/add", [this](const httplib::Request& req, httplib::Response& res){
        if (req.params.size()) {
            if (req.has_param("name")) {
                std::string mark = req.get_param_value("name");
                if (engine.add(mark,req.body)) {
                    res.set_content("Succesfully added", "text/plain");
                    return;
                }
                res.set_content("Market does not exist!", "text/plain");
            }
            else {
                res.set_content("Please specify which market!", "text/plain");
            }
        }
    });
}

void RestServer::listen() {
    server.listen("localhost", 8100);
}