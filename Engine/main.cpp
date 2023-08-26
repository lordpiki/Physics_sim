#include <iostream>
#include <WinSock2.h>
#include "Communicator.h"
#include "Enviroment.h"
#include <cmath>
#include <iostream>
#include <random>



using std::cout;
using std::endl;

int main() 
{
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(300, 600); // Range 1-90

    const int PORT = 8876;
    int frame = 1000000;
    Enviroment env;

    Communicator communicator(PORT);
    double mass = std::pow(10, 6);

    cout << communicator.getEnviromentJson(env);
    env.addPoint(Point({ 550, 100 }, { -0.0, 0 }, std::pow(10, 6)));
    env.addPoint(Point({ 350, 200 }, { 0.005, 0.0 }, std::pow(10, 8)));
    env.addPoint(Point({ 450, 350 }, { 0, -0.00 }, std::pow(10, 7)));
    env.addPoint(Point({ 650, 75 }, { 0, -0.00 }, std::pow(10, 6)));

    while (true)
    {

        env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        string msg = communicator.recieveMsg();
        if (msg == "+")
        {
            env.updateTimeFrame(true);
        }
        if (msg == "-")
        {
            env.updateTimeFrame(false);
        }
        if (msg == "exit")
        {
            exit(1);
        }
        frame++;
    }

    return 0;
}
