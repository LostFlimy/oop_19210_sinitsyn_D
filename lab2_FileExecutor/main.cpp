#include "Parser.h"
#include "Fabric.h"
#include<iostream>

int main(int argc, char** argv) {
    Fabric<Worker> Factory;
    Factory.Register<ReadWorker> ("readfile" , Fabric<ReadWorker>::CreateFunc);
    Factory.Register<WriteWorker> ("writefile" , Fabric<WriteWorker>::CreateFunc);
    Factory.Register<DumpWorker> ("dump" , Fabric<DumpWorker>::CreateFunc);
    Factory.Register<SortWorker> ("sort" , Fabric<SortWorker>::CreateFunc);
    Factory.Register<ReplaceWorker> ("replace" , Fabric<ReplaceWorker>::CreateFunc);
    Factory.Register<GrepWorker> ("grep" , Fabric<GrepWorker>::CreateFunc);

    Parser pars(argv[1]);
    try{
        pars.parsing();
    } catch(std::string a) {
        std::cout << a << std::endl;
        return -1;
    }

    try{
        std::vector<int> order = pars.getOrder();
        std::map<int, std::string> workers = pars.getWorkers();
        std::map<int, std::vector<std::string>> args = pars.getArgs();
        if(workers[order[0]] != "readfile"){
            std::string exception("Can not start with first worker");
            throw exception;
        }
        Worker::WorkerResult result;
        for(int i = 0; i < order.size(); ++i){
            std::shared_ptr<Worker> worker = Factory.Create(workers[order[i]], args[order[i]]);
            result = worker->operation(result);
        }
        if(workers[order[order.size() - 1]] != "writefile"){
            std::string exception("Can not end with last worker");
            throw exception;
        }
    } catch (std::string a){
        std::cout << a << std::endl;
        return -1;
    }
    return 0;
}
