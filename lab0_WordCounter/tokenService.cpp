#include "tokenService.h"

void TokenService::fillLine(const std::string &curline) {
    clearParts();
    line = curline;
}

std::vector<std::string> TokenService::getParts() {
    splitLine();
    return partsofline;
}

void TokenService::clearParts() {
    partsofline.clear();
}

void TokenService::splitLine() {
    std::string newline;
    for(char i : line){
        if( (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == '\'') {
            newline += i;
        }
        else{
            if(!newline.empty())
                partsofline.push_back(newline);
            newline = "";
        }
    }
    if(!newline.empty())
        partsofline.push_back(newline);
}
