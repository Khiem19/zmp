#include "Sender.hh"

Sender::~Sender()
{
    close(_Socket);
}

int Sender::Send(const char *sMesg)
{
    ssize_t bytesSent = 0;
    ssize_t bytesToSend = strlen(sMesg);

    while (bytesSent < bytesToSend)
    {
        ssize_t sent = write(_Socket, sMesg + bytesSent, bytesToSend - bytesSent);
        if (sent < 0)
        {
            std::cerr << "*** Blad przeslania napisu." << std::endl;
            return -1;
        }
        bytesSent += sent;
    }

    return 0;
}

void Sender::Watching_and_Sending()
{
    Send("Clear\n");

    _pScn->LockAccess();
    for (auto &iterator : _pScn->getMobileObjects())
    {
       
        Send(getAddInstruction(&(iterator.second)).c_str());
     
    }
    _pScn->UnlockAccess();

    while (ShouldCountinueLooping())
    {
        if (!_pScn->IsChanged())
        {
            usleep(10000);
            continue;
        }

        _pScn->LockAccess();

        for (auto &iterator : _pScn->getMobileObjects())
        {
   
            Send(getUpdateInstruction(&(iterator.second)).c_str());
         
        }

        _pScn->CancelChange();
        _pScn->UnlockAccess();
    }
}

bool Sender::OpenConnection()
{
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0)
    {
        std::cerr << "*** Blad otwarcia gniazda." << std::endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
        std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
        return false;
    }

    return true;
}

std::string Sender::getUpdateInstruction(MobileObj *obj) const
{
    std::ostringstream tmp;
    tmp << "UpdateObj Name=" << obj->GetName()
        << " Shift=(" << obj->GetPosition_m()[0] << ", " << obj->GetPosition_m()[1] << ", " << obj->GetPosition_m()[2] << ")"
        << " Scale=(" << obj->getScale()[0] << ", " << obj->getScale()[1] << ", " << obj->getScale()[2] << ")"
        << " Trans_m=(" << obj->getTranslation()[0] << ", " << obj->getTranslation()[1] << ", " << obj->getTranslation()[2] << ")"
        << " RGB=(" << static_cast<int>(obj->getRgb()[0]) << ", " << static_cast<int>(obj->getRgb()[1]) << ", " << static_cast<int>(obj->getRgb()[2]) << ")"
        << " RotXYZ_deg=(" << obj->GetAng_Roll_deg() << ", " << obj->GetAng_Pitch_deg() << ", " << obj->GetAng_Yaw_deg() << ")\n";

    return tmp.str();
}

std::string Sender::getAddInstruction(MobileObj *obj) const
{
    std::ostringstream tmp;
    tmp << "AddObj Name=" << obj->GetName()
        << " Shift=(" << obj->GetPosition_m()[0] << ", " << obj->GetPosition_m()[1] << ", " << obj->GetPosition_m()[2] << ")"
        << " Scale=(" << obj->getScale()[0] << ", " << obj->getScale()[1] << ", " << obj->getScale()[2] << ")"
        << " Trans_m=(" << obj->getTranslation()[0] << ", " << obj->getTranslation()[1] << ", " << obj->getTranslation()[2] << ")"
        << " RGB=(" << static_cast<int>(obj->getRgb()[0]) << ", " << static_cast<int>(obj->getRgb()[1]) << ", " << static_cast<int>(obj->getRgb()[2]) << ")"
        << " RotXYZ_deg=(" << obj->GetAng_Roll_deg() << ", " << obj->GetAng_Pitch_deg() << ", " << obj->GetAng_Yaw_deg() << ")\n";

    std::cout << tmp.str();

    return tmp.str();
}

