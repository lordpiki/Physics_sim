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
    Point inv({ 1300, 300}, { -0.0, 0 }, std::pow(2, 3));
    inv.setInvisable();
    env.addPoint(inv);

    for (int i = 0; i < 50; i++)
    {
        env.addPoint(Point({ 500, 100 + i * 8}, { 0.0, 0 }, std::pow(2, -9)));
        env.addPoint(Point({ 450, 100 + i * 8}, { 0.0, 0 }, std::pow(2, -9)));
        env.addPoint(Point({ 350, 100 + i * 8}, { 0.0, 0 }, std::pow(2, -9)));
                                            
        env.addPoint(Point({ 550, 100 + i * 8}, { -0.0, 0 }, std::pow(2, -9)));
        env.addPoint(Point({ 600, 100 + i * 8}, { -0.0, 0 }, std::pow(2, -9)));
        env.addPoint(Point({ 700, 100 + i * 8}, { -0.0, 0 }, std::pow(2, -9)));
    }

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
