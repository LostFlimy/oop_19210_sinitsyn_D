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
        workers[key].push_back(result[2]);
        if(result[2] != "replace")
            workers[key].push_back(result[3]);
        else {
            std::string sstr = result[2];
            int pos = sstr.find(' ');
            std::string str1 = sstr.substr(0, pos);
            sstr.erase(0, pos + 1);
            std::string str2 = sstr;
            workers[key].push_back(result[3]);
            workers[key].push_back(result[4]);
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
        str.erase(0, sstr.size());
    }
    rx = ("([0-9]+)");
    if(std::regex_search(str.c_str(), result, rx)){
        order.push_back(getnumber(result[1]));
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
        number += value[i];
    }
    return number;
}

std::map<int, std::vector<std::string>> Parser::getWorkers() const {
    return workers;
}

std::vector<int> Parser::getOrder() const {
    return order;
}

