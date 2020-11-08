#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

class Worker {
public:
    enum class ReturnType {
        NONE, TEXT
    };
    class WorkerResult {
    private:
        std::vector<std::string> text;
    public:
        WorkerResult();
        explicit WorkerResult(std::vector<std::string>& text) : text(text){}
        std::vector<std::string> getText();
    };
    virtual WorkerResult operation(WorkerResult& enter) = 0;
    ReturnType getInput() const;
    ReturnType getOutput() const;
protected:
    ReturnType inputType;
    ReturnType outputType;

    explicit Worker(ReturnType input, ReturnType output) : inputType(input), outputType(output){}
};

class readWorker : public Worker
{
public:
    explicit readWorker(std::string filename) : Worker(ReturnType::NONE, ReturnType::TEXT){
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};

class writeWorker : public Worker
{
public:
    explicit writeWorker(std::string filename) :
                         Worker(ReturnType::TEXT, ReturnType::NONE) {
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};

class grepWorker : public Worker
{
public:
    explicit grepWorker(std::string word) :
                        Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->word = std::move(word);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string word;
};

class sortWorker : public Worker
{
public:
    explicit sortWorker() :
        Worker(ReturnType:: TEXT, ReturnType::TEXT){}
    WorkerResult operation(WorkerResult& enter) override;
};

class replaceWorker : public Worker
{
public:
    explicit replaceWorker(std::string word1, std::string word2) :
                           Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->word1 = std::move(word1);
        this->word2 = std::move(word2);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string word1;
    std::string word2;
};

class dumpWorker : public Worker
{
public:
    explicit dumpWorker(std::string filename) :
                        Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};