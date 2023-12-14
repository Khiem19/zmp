#include "LibInterface.hh"

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);
}

bool LibInterface::init(std::string libraryName) {
    _LibHandler = dlopen(libraryName.c_str(), RTLD_LAZY);
    const char *(*getCmdName)(void);

    if (!_LibHandler) {
        std::cerr << "!!! Brak biblioteki: " << libraryName << std::endl;
        return false;
    }

    void *function = dlsym(_LibHandler, "CreateCmd");

    if (!function) {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd w " << libraryName << std::endl;
        return false;
    }

    _pCreateCmd = *reinterpret_cast<AbstractInterp4Command *(**)(void)>(&function);

    function = dlsym(_LibHandler, "GetCmdName");

    if (!function) {
        std::cerr << "!!! Nie znaleziono funkcji GetCmdName w " << libraryName << std::endl;
        return false;
    }

    getCmdName = reinterpret_cast<const char *(*)(void)>(function);
    _CmdName = getCmdName();

    return true;
}


AbstractInterp4Command *LibInterface::CreateCmd()
{
    return _pCreateCmd();
}