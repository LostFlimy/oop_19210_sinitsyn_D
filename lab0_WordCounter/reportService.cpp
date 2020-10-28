#include "reportService.h"

ReportService::ReportService(const std::string &out) {
    output.open(out);
    if(output.is_open()){
        status = true;
    }
    else{
        status = false;
    }
}

void ReportService::getInfo(std::vector<std::pair<std::pair<int, double>, std::string>> infoReport) {
    for(auto x : infoReport){
        output << x.second << ',' << x.first.first << ',' << x.first.second << std::endl;
    }
}

bool ReportService::isOpen() const {
    return status;
}