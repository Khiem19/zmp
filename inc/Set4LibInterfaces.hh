#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <memory>
#include "LibInterface.hh"
#include "AbstractInterp4Command.hh"

class Set4LibInterfaces
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> lib;
    bool parallel = false;

public:
    bool init(std::vector<std::string> lib_vector);

    AbstractInterp4Command *execute(std::string key);
    bool isParallel() { return parallel; }
};

#endif