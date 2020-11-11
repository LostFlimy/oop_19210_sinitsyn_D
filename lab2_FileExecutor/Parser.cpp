#include "Parser.h"

Parser::Parser(std::string filename) {
    this->filename = std::move(filename);
}

void Parser::parsing() {
    std::ifstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        throw "Bad name of input file";
    }
    std::string str;
    std::getline(stream, str);
    if(str != "desc"){
        throw "Bad format";
    }
    std::regex rx("([0-9]+) = (grep|sort|replace|readfile|writefile) ?(.*)");
    std::cmatch result;

    while((std::getline(stream, str)) && (std::regex_search(str.c_str(), result, rx))){
        int key = getnumber(result[1]);
        if(workers[key] != ""){
            throw "multiply definition of worker";
        }
        workers[key] = result[2];
        if(result[2] != "replace" && result[2] != "sort")
            workers_agrs[key].push_back(result[3]);
        else {
            if(result[2] == "replace") {
                std::string sstr = result[3];
                std::regex _rx("(\\w+)");
                if(!std::regex_search(sstr.c_str(), result, _rx)){
                    throw "Bad format of replace";
                }
                workers_agrs[key].push_back(result[1]);
                sstr = result.suffix();
                if(!std::regex_search(sstr.c_str(), result, _rx)){
                    throw "Bad format of replace";
                }
                workers_agrs[key].push_back(result[1]);
                sstr = result.suffix();
                if(!sstr.empty()){
                    throw "Bad format";
                }
            }
            if(result[2] == "sort") {
                if(result[3] != ""){
                    throw "Bad format of sort";
                }
            }
        }
    }
    if(str != "csed"){
        throw "Bad format";
    }
    rx = ("([0-9]+) - > ");
    std::getline(stream, str);
    while(std::regex_search(str.c_str(), result, rx)){
        order.push_back(getnumber(result[1]));
        std::string sstr = result[1];
        str = result.suffix();
        if(result.prefix() != ""){
            throw "Bad format";
        }
    }
    rx = ("([0-9]+)");
    if(std::regex_search(str.c_str(), result, rx)){
        order.push_back(getnumber(result[1]));
        std::string sstr = result[1];
        str = result.suffix();
        if(!str.empty()){
            throw "Bad format";
        }
    } else {
            throw "Bad format in last string";
    }

}

int Parser::getnumber(std::string value) {
    if(value.size() == 0){
        throw "On first position of any string not number";
    }
    if(value[0] == '-'){
        throw "Negative number";
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

