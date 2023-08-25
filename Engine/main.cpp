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
    double mass = std::pow(10, 8);

    cout << communicator.getEnviromentJson(env);
    for (double i = 1; i < 50; i++)
    {
        double newMass = mass * i;
        double newAcc = 0;
        double newVel = 0.01;
        env.addPoint(Point({ 0, i * 8 }, { newVel , 0 }, newMass, { newAcc, 0 }));
        env.addPoint(Point({ 50, i * 8}, { newVel, 0 }, newMass, { newAcc, 0 }));
        env.addPoint(Point({ 100, i * 8}, { newVel, 0 }, newMass, { newAcc, 0 }));
        env.addPoint(Point({ 400, i * 8}, { -newVel, 0 }, newMass, { -newAcc, 0 }));
        env.addPoint(Point({ 450, i * 8}, { -newVel, 0 }, newMass, { -newAcc, 0 }));
        env.addPoint(Point({ 500, i * 8}, { -newVel, 0 }, newMass, { -newAcc, 0 }));
    }

    while (true)
    {

        env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        communicator.recieveMsg();
        frame++;
    }

    return 0;
}
