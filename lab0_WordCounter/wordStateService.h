#pragma once
#include <map>
#include <string>
#include <vector>
#include <algorithm>


class WordStateService{
public:
    WordStateService();

    void createState(const std::vector<std::string>& parts);

    std::vector<std::pair<std::pair<int, double>, std::string>> getState();
private:
    double sum;
    std::map<std::string, std::pair<int, double>> stateOfWords;
};
