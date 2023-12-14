#ifndef KLIENT_HH
#define KLIENT_HH

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <list>
#include "AccessControl.hh"
#include "Port.hh"
#include "Configuration.hh"
#include "Reader.hh"
#include "Sender.hh"
#include "Set4LibInterfaces.hh"
#include "AbstractInterp4Command.hh"


using namespace std;


int klient();


#endif