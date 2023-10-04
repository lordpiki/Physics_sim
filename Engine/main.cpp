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

    cout << communicator.getEnviromentJson(env);
    Point inv({ 1300, 300}, { -0.0, 0 }, std::pow(2, 15));
    inv.setInvisable();
    inv.setColor("red");
    //env.addPoint(inv);

    int distance_to_points = 40;
    double mass = std::pow(2, 6);
    double speedX = 1;
    double speedY = 0;

    for (int i = 0; i < 1; i++)
    {
        env.addPoint(Point({ 150, 100 + i * distance_to_points}, { speedX, speedY }, mass, "green"));

        env.addPoint(Point({ 650, 100 + i * distance_to_points}, { -speedX, -speedY }, mass, "gray"));

    }



    
    bool canUpdate = true;
    
    while (true)
    {
        if (canUpdate)
            env.upatePoints();
        communicator.sendMsg(communicator.getEnviromentJson(env));
        string msg = communicator.recieveMsg();
        if (msg == "+")
        {
            canUpdate = true;
        }
        if (msg == "-")
        {
            canUpdate = false;
        }
        if (msg == "exit")
        {
            exit(1);
        }
        frame++;
    }

    return 0;
}
