#include <iostream>
#include "Parser.h"
#include "Fabric.h"

int main(int argc, char** argv) {
    Fabric<Worker> Factory;
    Factory.Register<ReadWorker> ("readfile" , Fabric<ReadWorker>::CreateFunc);
    Factory.Register<WriteWorker> ("writefile" , Fabric<WriteWorker>::CreateFunc);
    Factory.Register<DumpWorker> ("dump" , Fabric<DumpWorker>::CreateFunc);
    Factory.Register<SortWorker> ("sort" , Fabric<SortWorker>::CreateFunc);
    Factory.Register<ReplaceWorker> ("replace" , Fabric<ReplaceWorker>::CreateFunc);
    Factory.Register<GrepWorker> ("grep" , Fabric<GrepWorker>::CreateFunc);
    return 0;
}
