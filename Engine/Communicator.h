#pragma once

#include <WinSock2.h>
#include <map>
#include <vector>
#include "Enviroment.h"
#include <Windows.h>
#include "JSON/json.hpp"
#include <string>


using std::string;

class Communicator
{
public:
    Communicator(int port);
    ~Communicator();

    void sendMsg(const string& message);
    string recieveMsg();

    string getEnviromentJson(const Enviroment& enviroment);


private:

    int bindAndListen();
    int acceptClient();

    SOCKET serverSocket;
    SOCKET clientSocket;

};