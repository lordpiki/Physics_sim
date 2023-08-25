#include "Enviroment.h"
#include <iostream>

using std::cout;
using std::endl;

Enviroment::Enviroment()
{

}

void Enviroment::addPoint(const Point& point)
{
    points.push_back(point);
}

vector<Point> Enviroment::getPoints() const
{
    return points;
}

void Enviroment::upatePoints()
{
    for (Point& point : points)
    {
        point.updatePoint(points);
        cout << "pos: [" << point.getPosition().first << ", " << point.getPosition().second << 
            "] acc: [" << point.getAcceleration().first << ", " << point.getAcceleration().second << "]"
            << "vel: [" << point.getvelocity().first << ", " << point.getvelocity().second << "]" << endl;
    }
    cout << endl;
    
    checkColision();
}

void Enviroment::checkColision()
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].getDistance(points[i + 1]) < 2)
        {
            points[i].setMass(points[i].getMass() + points[i + 1].getMass());
            points.erase(points.begin() + i);
        }
    }
}
