#pragma once
#include<regex>
#include<string>
#include<vector>
#include<map>
#include<fstream>

class Parser {
public:
    explicit Parser(std::string filename);
    void parsing ();
    [[nodiscard]] std::vector<int> getOrder() const;
    [[nodiscard]] std::map<int, std::string> getWorkers() const;
    std::map<int, std::vector<std::string>> getArgs() const;
private:
    int getnumber(std::string value);
    std::string filename;
    std::vector<int> order;
    std::map<int, std::string> workers; // in x.second[0] is name of worker
    std::map<int, std::vector<std::string>> workers_agrs;
};


