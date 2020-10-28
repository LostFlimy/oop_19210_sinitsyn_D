#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<algorithm>
#include <sstream>

using namespace std;

class LineReader{
public:
    LineReader(string nameOfInputFile) {
        input.open(nameOfInputFile);
        if(input.is_open()){
            status = true;
        }
        else{
            status = false;
        }
    }

    bool readline() {
        if(getline(input, value)){
            return true;
        }
        return false;
    }

    string getvalue() const {
        return value;
    }

    bool isOpen() const{
        return status;
    }

private:
    bool status;
    ifstream input;
    string value;
};

class TokenService{
public:
    void fillLine(string curline){
        clearParts();
        line = curline;
    }

    vector<string> getParts() {
        splitLine();
        return partsofline;
    }

private:
    void clearParts() {
        partsofline.clear();
    }

    void splitLine() {
        string newline = "";
        for(int i = 0; i < line.size(); ++i){
            if( (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') ) {
                newline += line[i];
            }
            else{
                if(newline != "")
                    partsofline.push_back(newline);
                newline = "";
            }
        }
    }
    string line;
    vector<string> partsofline;
};

class WordStateService{
public:
    WordStateService(){
        sum = 0.0;
    }

    void createState(vector<string> parts){
        for(const auto& x : parts){
            sum += 1;
            stateOfWords[x].first++;
        }
    }

    map<string, pair<int, double>> getState(){
        for(auto& x : stateOfWords){
            x.second.second = x.second.first / sum;
        }
        return stateOfWords;
    }
private:
    double sum;
    map<string, pair<int, double>> stateOfWords;
};

class ReportService{
public:
    ReportService(string out) {
        output.open(out);
        if(output.is_open()){
            status = true;
        }
        else{
            status = false;
        }
    }

    void fillInfo(map<string, pair<int, double>> state){
        for(auto& x : state){
            infoReport.push_back({x.second, x.first});
        }
        sort(infoReport.begin(), infoReport.end(),
             [](pair<pair<int, double>, string> lsr, pair<pair<int, double>, string> hsr)
             {
                 return lsr.first.first > hsr.first.first;
             });
    }

    void getInfo() {
        for(auto x : infoReport){
            output << x.second << ',' << x.first.first << ',' << x.first.second << endl;
        }
    }

    bool isOpen(){
        return status;
    }

private:
    bool status;
    ofstream output;
    vector<pair<pair<int, double>, string>> infoReport;
};

int main(int argc, char** argv) {

    {// Unit tests of TokenService
        TokenService service1;
        service1.fillLine("Hello,. :' World'., asd!!!");
        vector<string> curvector;
        curvector.push_back("Hello");
        curvector.push_back("World");
        curvector.push_back("asd");
        if(service1.getParts() != curvector){
            cout << "Error in TokenService!!!" << endl;
            return 1;
        }

        TokenService service2;
        service2.fillLine("");
        if(service2.getParts().size() != 0){
            cout << "Error in TokenService!!!" << endl;
            return 1;
        }
    }

    {//Unit tests of WordStateService
        WordStateService service1;
        service1.createState({});
        if(service1.getState().size() != 0){
            cout << "Error in WordStateService!!!" << endl;
            return 2;
        }
        WordStateService service2;
        service2.createState({"a", "a", "b", "b", "a", "c", "d", "f"});
        map<string, pair<int, double>> result = service2.getState();
        if(result["a"] != pair<int,double>{3, 0.375} || result["h"] != pair<int,double>{0, 0.0}){
            cout << "Error in WordStateService!!!" << endl;
            return 2;
        }
    }

    {
        LineReader reader("abc");
        if(reader.readline() == true){
            cout << "Error in LineReader!!!" << endl;
            return 3;
        }
    }

    LineReader reader(argv[1]);
    if(!reader.isOpen()){
        cout << "Incorrect name of input file!" << endl;
        return 0;
    }
    TokenService service;
    WordStateService state_service;
    ReportService rep_service(argv[2]);
    if(!rep_service.isOpen()){
        cout << "Incorrect name of output file!" << endl;
        return 0;
    }
    while(reader.readline()){
        service.fillLine(reader.getvalue());
        state_service.createState(service.getParts());
    }
    rep_service.fillInfo(state_service.getState());
    rep_service.getInfo();
    return 0;
}