#include "Enviroment.h"

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
    }
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
