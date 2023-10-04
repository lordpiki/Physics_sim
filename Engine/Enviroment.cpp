#include "Enviroment.h"
#include <iostream>
#include <cmath> // for M_PI

using std::cout;
using std::endl;

const double MAX_VELOCITY = 1000.0; // Define a named constant for max velocity

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
        point.setRadius(10);
        point.updatePoint(points);
    }

    checkColision();
}

void Enviroment::checkColision()
{
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {

            if (checkAndMovePoints(points[i], points[j]))
            {
                double distance = points[i].getDistance(points[j]);
                double angle = points[i].checkAngle(points[j]);
                cout << "collision" << endl;
                //points[i].moveByAngle(distance / 2, 180 - angle);
                //points[j].moveByAngle(distance / 2, angle);
            }
        }
    }
}

void Enviroment::updateTimeFrame(bool toUp)
{
    for (Point& point : points)
    {
        point.setTimeFrame((toUp ? 1 : 0));
    }
}

bool Enviroment::checkAndMovePoints(Point& point1, Point& point2)
{
    // Define a minimum distance threshold
    double minDistance = point1.getRadius() + point2.getRadius();

    // Calculate the actual distance between the points
    double distance = point1.getDistance(point2);

    if (distance < minDistance)
    {

        // Calculate the relative velocity between the two points.
        double relativeVelocityX = point1.getVelocity().first - point2.getVelocity().first;
        double relativeVelocityY = point1.getVelocity().second - point2.getVelocity().second;

        // Calculate the impact vector.
        double impactVectorX = point1.getPosition().first - point2.getPosition().first;
        double impactVectorY = point1.getPosition().second - point2.getPosition().second;

        // Calculate the dot product of relative velocity and impact vector.
        double dotProduct = relativeVelocityX * impactVectorX + relativeVelocityY * impactVectorY;

        // Calculate the magnitude of the impact vector squared.
        double impactVectorMagnitudeSquared = impactVectorX * impactVectorX + impactVectorY * impactVectorY;

        // Calculate the normal force between the two points.
        double normalForce = dotProduct / impactVectorMagnitudeSquared;

        // Calculate the tangential force between the two points.
        double tangentialForceX = relativeVelocityX - normalForce * impactVectorX;
        double tangentialForceY = relativeVelocityY - normalForce * impactVectorY;

        // Update the velocity of each point using the normal and tangential forces.
        point1.setVelocity({ point1.getVelocity().first - normalForce * impactVectorX, point1.getVelocity().second - normalForce * impactVectorY });
        point2.setVelocity({ point2.getVelocity().first + normalForce * impactVectorX, point2.getVelocity().second + normalForce * impactVectorY });

        // Update the velocity of each point using the tangential force.
        point1.setVelocity({ point1.getVelocity().first - tangentialForceX, point1.getVelocity().second - tangentialForceY });
        point2.setVelocity({ point2.getVelocity().first + tangentialForceX, point2.getVelocity().second + tangentialForceY });

        // Clamp the velocity of each point to the maximum velocity threshold.
        point1.setVelocity({ std::min(point1.getVelocity().first, MAX_VELOCITY), std::min(point1.getVelocity().second, MAX_VELOCITY) });
        point2.setVelocity({ std::min(point2.getVelocity().first, MAX_VELOCITY), std::min(point2.getVelocity().second, MAX_VELOCITY) });

        point1.downgradeVelocity();
        point2.downgradeVelocity();

        return true;
    }
    return false;
}
