#include "wordStateService.h"

WordStateService::WordStateService() {
    sum = 0.0;
}

void WordStateService::createState(const std::vector<std::string> &parts) {
    for(const auto& x : parts){
        sum += 1;
        stateOfWords[x].first++;
    }
    for(auto& x : stateOfWords){
        x.second.second = x.second.first / sum;
    }
}

std::vector<std::pair<std::pair<int, double>, std::string>> WordStateService::getState() {
    std::vector<std::pair<std::pair<int, double>, std::string>> resState;
    for(auto& x : stateOfWords){
        resState.push_back({x.second, x.first});
    }
    sort(resState.begin(), resState.end(),
         [](std::pair<std::pair<int, double>, std::string> lsr, std::pair<std::pair<int, double>, std::string> hsr)
         {
             return lsr.first.first > hsr.first.first;
         });
    return resState;
}