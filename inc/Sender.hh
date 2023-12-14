#ifndef SENDER_HH
#define SENDER_HH

#include <unistd.h>
#include <cstring>
#include <ostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Scene.hh"
#include "Port.hh"


class Sender
{
   
    volatile bool _ContinueLooping = true;
  
    int _Socket = 0;

    Scene *_pScn = nullptr;

public:
  
    Sender(Scene *pScn) : _pScn(pScn) {}

    ~Sender();

    bool OpenConnection();

    int Send(const char *sMesg);
   
    bool ShouldCountinueLooping() const { return _ContinueLooping; }
  
    void CancelCountinueLooping() { _ContinueLooping = false; }

    void Watching_and_Sending();
    std::string getUpdateInstruction(MobileObj *obj) const;
    std::string getAddInstruction(MobileObj *obj) const;
};

#endif