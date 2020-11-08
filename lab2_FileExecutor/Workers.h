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

class ReadWorker : public Worker
{
public:
    explicit ReadWorker(std::string filename) : Worker(ReturnType::NONE, ReturnType::TEXT){
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};

class WriteWorker : public Worker
{
public:
    explicit WriteWorker(std::string filename) :
                         Worker(ReturnType::TEXT, ReturnType::NONE) {
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};

class GrepWorker : public Worker
{
public:
    explicit GrepWorker(std::string word) :
                        Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->word = std::move(word);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string word;
};

class SortWorker : public Worker
{
public:
    explicit SortWorker() :
        Worker(ReturnType:: TEXT, ReturnType::TEXT){}
    WorkerResult operation(WorkerResult& enter) override;
};

class ReplaceWorker : public Worker
{
public:
    explicit ReplaceWorker(std::string word1, std::string word2) :
                           Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->word1 = std::move(word1);
        this->word2 = std::move(word2);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string word1;
    std::string word2;
};

class DumpWorker : public Worker
{
public:
    explicit DumpWorker(std::string filename) :
                        Worker(ReturnType::TEXT, ReturnType::TEXT){
        this->filename = std::move(filename);
    }
    WorkerResult operation(WorkerResult& enter) override;
protected:
    std::string filename;
};