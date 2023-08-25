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
    std::uniform_int_distribution<int> dist(300, 800); // Range 1-90

    const int PORT = 8876;
    int frame = 1000000;
    Enviroment env;

    Communicator communicator(PORT);

    cout << communicator.getEnviromentJson(env);
    while (true)
    {
        if (frame > 3500)
        {
            env.reset();
            env.addPoint(Point({ dist(gen), dist(gen) }, {0.003, 0.00}, {0, 0}, std::pow(10, 6)));
            env.addPoint(Point({ dist(gen), dist(gen) }, { 0.00, 0.00 }, { 0, 0 }, std::pow(10, 8)));
            env.addPoint(Point({ dist(gen), dist(gen) }, { 0.002, -0.001 }, { 0, 0 }, std::pow(10, 7)));
            env.addPoint(Point({ dist(gen), dist(gen) }, { 0.002, -0.002 }, { 0, 0 }, std::pow(10, 4)));
            frame = 0;
        }
        env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        communicator.recieveMsg();
        frame++;
    }

    return 0;
}
