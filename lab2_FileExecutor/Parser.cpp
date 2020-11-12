#include "Parser.h"

Parser::Parser(std::string filename) {
    this->filename = std::move(filename);
}

void Parser::parsing() {
    std::ifstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        std::string exception("Bad name");
        throw exception;
    }
    std::string str;
    std::getline(stream, str);
    if(str != "desc"){
        std::string exception("Bad format");
        throw exception;
    }
    std::regex rx("([0-9]+) = (grep|sort|replace|readfile|writefile|dump) ?(.*)");
    std::cmatch result;

    while((std::getline(stream, str)) && (std::regex_search(str.c_str(), result, rx))){
        int key = getnumber(result[1]);
        if(workers[key] != ""){
            std::string exception("Multiply definition");
            throw exception;
        }
        workers[key] = result[2];
        if(result[2] != "replace" && result[2] != "sort")
            workers_agrs[key].push_back(result[3]);
        else {
            if(result[2] == "replace") {
                std::string sstr = result[3];
                std::regex _rx("(\\w+)");
                if(!std::regex_search(sstr.c_str(), result, _rx)){
                    std::string exception("Bad format of replace");
                    throw exception;
                }
                workers_agrs[key].push_back(result[1]);
                sstr = result.suffix();
                if(!std::regex_search(sstr.c_str(), result, _rx)){
                    std::string exception("Bad format of replace");
                    throw exception;
                }
                workers_agrs[key].push_back(result[1]);
                sstr = result.suffix();
                if(!sstr.empty()){
                    std::string exception("Bad format of replace");
                    throw exception;
                }
            }
            if(result[2] == "sort") {
                if(result[3] != ""){
                    std::string exception("Bad format of sort");
                    throw exception;
                }
            }
        }
    }
    if(str != "csed"){
        std::string exception("Bad format");
        throw exception;
    }
    rx = ("([0-9]+) - > ");
    std::getline(stream, str);
    while(std::regex_search(str.c_str(), result, rx)){
        order.push_back(getnumber(result[1]));
        std::string sstr = result[1];
        str = result.suffix();
        if(result.prefix() != ""){
            std::string exception("Bad format");
            throw exception;
        }
    }
    rx = ("([0-9]+)");
    if(std::regex_search(str.c_str(), result, rx)){
        order.push_back(getnumber(result[1]));
        std::string sstr = result[1];
        str = result.suffix();
        if(!str.empty()){
            std::string exception("Bad format");
            throw exception;
        }
    } else {
        std::string exception("Bad format");
        throw exception;
    }

}

int Parser::getnumber(std::string value) {
    if(value.size() == 0){
        std::string exception("On first position of any string not number");
        throw exception;
    }
    if(value[0] == '-'){
        std::string exception("Negative number");
        throw exception;
    }
    int number = 0;
    for(int i = 0; i < value.size(); ++i){
        number *= 10;
        number += value[i] - 48;
    }
    return number;
}

std::map<int, std::string> Parser::getWorkers() const {
    return workers;
}

std::vector<int> Parser::getOrder() const {
    return order;
}

std::map<int, std::vector<std::string>> Parser::getArgs() const {
    return workers_agrs;
}

