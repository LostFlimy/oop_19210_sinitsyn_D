#pragma once
#include <map>
#include "Workers.h"
#include <memory>

template<class T>
class Fabric{
public:
    using TCreateFunc = std::shared_ptr<T>(*)(std::vector<std::string>);

    template<class TDerived>
    void Register(std::string name, TCreateFunc new_CreateFunc){
        static_assert(std::is_base_of<T, TDerived>::value,
                      "Fabric::Register can not accept this type, because it doesn't derive from base class");
        _CreateFunc[name] = new_CreateFunc;
    }

    std::shared_ptr<T> Create(std::string name, std::vector<std::string> args){
        auto it = _CreateFunc.find(name);
        if(it != _CreateFunc.end()){
            return it->second(args);
        }
        return nullptr;
    }

private:
    template<class TDerived>
    static std::shared_ptr<T> CreateFunc(std::vector<std::string> values){
        return std::make_shared<TDerived>(values);
    }
    std::map<std::string, TCreateFunc> _CreateFunc;

};

template<>
class Fabric<ReadWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<ReadWorker>(values[0]);
    }
};

template<>
class Fabric<WriteWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<WriteWorker>(values[0]);
    }
};

template<>
class Fabric<SortWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<SortWorker>();
    }
};

template<>
class Fabric<GrepWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<GrepWorker>(values[0]);
    }
};

template<>
class Fabric<DumpWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<DumpWorker>(values[0]);
    }
};

template<>
class Fabric<ReplaceWorker>{
private:
    static std::shared_ptr<Worker> CreateFunc(std::vector<std::string> values){
        return std::make_shared<ReplaceWorker>(values[0], values[1]);
    }
};

