#include "Enviroment.h"
#include <iostream>

#define M_PI           3.14159265358979323846  /* pi */



using std::cout;
using std::endl;

Enviroment::Enviroment()
{

}

void Enviroment::addPoint(const Point& point)
{
    points.push_back(point);
}

void Enviroment::reset()
{
    points.clear();
}

vector<Point> Enviroment::getPoints() const
{
    return points;
}

void Enviroment::upatePoints()
{
    for (Point& point : points)
    {
        point.setRadius(3);
        point.updatePoint(points);
        //cout << "pos: [" << point.getPosition().first << ", " << point.getPosition().second << 
          //  "] acc: [" << point.getAcceleration().first << ", " << point.getAcceleration().second << "]"
            //<< "vel: [" << point.getVelocity().first << ", " << point.getVelocity().second << "]" << endl;
    }
    cout << endl;
    
    checkColision();
}

void Enviroment::checkColision()
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (points[i].getDistance(points[i + 1]) < 4 * ( points[i].getRadius() + points[i + 1].getRadius()))
        {
            updateColision(points[i], points[1]);
            cout << "Collision" << endl;
        }
    }
}

void Enviroment::updateColision(Point& point1, Point& point2)
{
    // Calculate the initial total momentum
    double pInitial = point1.getMomentum() + point2.getMomentum();

    // Calculate the final velocities using conservation of momentum
    double velovity1Final = (pInitial - point2.getMomentum()) / point1.getMass();
    double velovity2Final = (pInitial - point1.getMomentum()) / point2.getMass();

    // Calculate angles of velocities
    double alpha = std::atan2(point1.getVelocity().second, point1.getVelocity().first);
    double beta = std::atan2(point2.getVelocity().second, point2.getVelocity().first);

    // Calculate the new direction angles for both points
    double theta1 = std::atan((velovity1Final  * std::sin(alpha) - point1.getVelocity().second * std::sin(beta)) /
        (velovity1Final * std::cos(alpha) - point1.getVelocity().first * std::cos(beta)));

    double theta2 = std::atan((velovity2Final * std::sin(beta) - point2.getVelocity().second * std::sin(alpha)) /
        (velovity2Final * std::cos(beta) - point2.getVelocity().first * std::cos(alpha)));

    // Convert angles to degrees
    double degreesTheta1 = theta1 * 180.0 / M_PI;
    double degreesTheta2 = theta2 * 180.0 / M_PI;

    // Multipler for sensitivity of pushed particle
    double multiplier = 2;

    // Update the directions of the velocities
    point1.setVelocity(std::make_pair(multiplier * velovity1Final * std::cos(theta1), multiplier * velovity1Final * std::sin(theta1)));
    point2.setVelocity(std::make_pair(multiplier * velovity2Final * std::cos(theta2), multiplier * velovity2Final * std::sin(theta2)));
}

