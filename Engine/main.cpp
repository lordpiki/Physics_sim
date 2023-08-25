#include <iostream>
#include <WinSock2.h>
#include "Communicator.h"
#include "Enviroment.h"
#include <cmath>


using std::cout;
using std::endl;

int main() 
{
    const int PORT = 8876;
    Enviroment env;
    env.addPoint(Point({ 20, 20 }, { 0.003, 0.00 }, { 0, 0 }, std::pow(10, 6)));
    env.addPoint(Point({ 100,150 }, { 0.00, 0.00 }, { 0, 0 }, std::pow(10, 8)));
    env.addPoint(Point({ 200, 350 }, {0.002, -0.001}, { 0, 0 }, std::pow(10, 7)));

    Communicator communicator(PORT);

    cout << communicator.getEnviromentJson(env);
    while (true)
    {
        env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        communicator.recieveMsg();
    }

    return 0;
}
