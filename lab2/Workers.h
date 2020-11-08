#pragma once
#include<vector>
#include<string>
#include<fstream>

template<class T1, class T2>
virtual class worker {
public:
    virtual T2& operation();
protected:
    T1 enter_value;
    T2 exit_value;
};

class ReadWorker : public worker<std::string, std::vector<std::string>> {
public:
    ReadWorker(std::string curname);
};
