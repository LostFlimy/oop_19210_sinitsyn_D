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
    stream >> str;
    if(str != "desc"){
        throw "Bad format";
    }
    std::regex rx("([0-9]) = (grep|sort|replace|readfile|writefile) *((\\w+(.| )\\w*)|)");
}
