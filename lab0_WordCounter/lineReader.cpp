#include "lineReader.h"

LineReader::LineReader(const std::string& nameOfInputFile) {
    input.open(nameOfInputFile);
    if(input.is_open()){
        status = true;
    }
    else{
        status = false;
    }
}

bool LineReader::readline() {
    if(getline(input, value)){
        return true;
    }
    return false;
}

std::string LineReader::getvalue() const {
    return value;
}

bool LineReader::isOpen() const {
    return status;
}

