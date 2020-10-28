#pragma once

#include <vector>
#include <string>

class TokenService{
public:
    void fillLine(const std::string& curline);

    std::vector<std::string> getParts();

private:
    void clearParts();

    void splitLine();
    std::string line;
    std::vector<std::string> partsofline;
};