#pragma once
#include<string>
#include<vector>
#include<fstream>

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
    virtual WorkerResult& operation(WorkerResult& enter) = 0;
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
    WorkerResult& operation(WorkerResult& enter) override;
};


