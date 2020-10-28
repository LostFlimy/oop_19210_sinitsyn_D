#pragma once

#include<fstream>
#include<string>
#include<vector>
#include<iostream>


class ReportService{
public:
    explicit ReportService(const std::string& out);

    void getInfo(std::vector<std::pair<std::pair<int, double>, std::string>> infoReport);

    bool isOpen() const;

private:
    bool status;
    std::ofstream output;
};