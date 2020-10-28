#pragma once

#include<string>
#include<fstream>

class LineReader{
public:
    explicit LineReader(const std::string& nameOfInputFile);

    bool readline();

    std::string getvalue() const;

    bool isOpen() const;

private:
    bool status;
    std::ifstream input;
    std::string value;
};

