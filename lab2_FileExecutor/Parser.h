#pragma once
#include<regex>
#include<string>
#include<vector>
#include<map>
#include<fstream>

class Parser {
    explicit Parser(std::string filename);
    void parsing ();

private:
    std::string filename;
    std::vector<int> order;
    std::map<int, std::vector<std::string>> workers; // in x.second[0] is name of worker
                                                     // in x.second[1-n] is args
};


