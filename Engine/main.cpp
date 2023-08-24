#include <iostream>
#include <WinSock2.h>
#include "Communicator.h"
#include "Enviroment.h"

using std::cout;
using std::endl;

int main() 
{
    const int PORT = 8876;
    Enviroment env;
    env.addPoint(Point(0, 0));
    env.addPoint(Point(0,100));
    env.addPoint(Point(100,0));
    env.addPoint(Point(100,100));

    Communicator communicator(PORT);

    cout << communicator.getEnviromentJson(env);
    while (true)
    {
        env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        cout << "waiting for msg to continue " << endl;
        communicator.recieveMsg();
    }

    return 0;
}
