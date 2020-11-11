#include "Workers.h"

Worker::WorkerResult::WorkerResult() {
    text = std::vector<std::string>(0);
}

std::vector<std::string> Worker::WorkerResult::getText() {
    return text;
}

Worker::ReturnType Worker::getInput() const {
    return inputType;
}

Worker::ReturnType Worker::getOutput() const {
    return outputType;
}

Worker::WorkerResult ReadWorker::operation(Worker::WorkerResult &enter) {
    std::ifstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        throw "Bad name input file";
    }
    std::vector<std::string> exit(0);
    std::string x;
    while(std::getline(stream, x)){
        exit.push_back(x);
    }
    return WorkerResult(exit);
}



Worker::WorkerResult WriteWorker::operation(Worker::WorkerResult &enter) {
    std::ofstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        throw "Bad name of output file in writeWorker";
    }
    std::vector<std::string> exit = enter.getText();
    for(const auto& x : exit){
        stream << x;
    }
    std::vector<std::string> text(0);
    return WorkerResult(text);
}

Worker::WorkerResult GrepWorker::operation(Worker::WorkerResult &enter) {
    std::vector<std::string> enterText = enter.getText();
    std::vector<std::string> exitText(0);
    for(const auto& x : enterText){
        if(x.find(word) != -1){
            exitText.push_back(x);
        }
    }
    return WorkerResult(exitText);
}


Worker::WorkerResult SortWorker::operation(Worker::WorkerResult &enter) {
    std::vector<std::string> enterText = enter.getText();
    std::sort(enterText.begin(), enterText.end());
    return WorkerResult(enterText);
}

Worker::WorkerResult ReplaceWorker::operation(Worker::WorkerResult &enter) {
    std::vector<std::string> enterText = enter.getText();
    for(auto& x : enterText){
        int pos = 0;
        pos = x.find(word1);
        while(pos != -1){
            x.replace(pos, word1.size(), word2);
            pos = x.find(word1);
        }
    }
    return WorkerResult(enterText);
}

Worker::WorkerResult DumpWorker::operation(Worker::WorkerResult &enter) {
    std::ofstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        throw "Bad name of output file in dumpWorker";
    }
    std::vector<std::string> exit = enter.getText();
    for(const auto& x : exit){
        stream << x;
    }
    return enter;
}
