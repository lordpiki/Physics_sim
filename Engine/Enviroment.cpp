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
        //point.setRadius(2);
        point.updatePoint(points);
    }
    
    checkColision();
}

void Enviroment::checkColision()
{
    double distance = 0;
    double angle = 0;
    bool isCollision = false;

    do
    {
        int collisionCount = 0;
        isCollision = false;
        for (int i = 0; i < points.size() - 1; i++)
        {
            distance = points[i].getDistance(points[i + 1]);
            angle = points[i].checkAngle(points[i + 1]);

            if (checkAndMovePoints(points[i], points[i + 1]))
            {
                //isCollision = true;
                collisionCount++;
                //updateColision(points[i], points[i + 1]);
                points[i].downgradeVelocity();
                points[i+1].downgradeVelocity();

            }
            
        }
        if (collisionCount > -1)
        {

            //cout << "collision count: " << collisionCount << endl;
        }
    } while (isCollision);
    //cout << "moved frame" << endl;
}

void Enviroment::updateTimeFrame(bool toUp)
{
    for (Point& point : points)
    {
        point.setTimeFrame(point.getTimeFrame() + 2 * (toUp ? 1 : -1));
    }
    cout << "Updated time Frame: " << points[0].getTimeFrame() << endl;
}

bool Enviroment::checkAndMovePoints(Point& point1, Point& point2)
{
    // Define a minimum distance threshold
    double minDistance = point1.getRadius() + point2.getRadius();

    // Calculate the actual distance between the points
    double distance = point1.getDistance(point2);

    if (distance < minDistance) {
        // Calculate the unit vector between the points
        //double dx = point2.getPosition().first - point1.getPosition().first;
        //double dy = point2.getPosition().second - point1.getPosition().second;
        //double length = std::sqrt(dx * dx + dy * dy);

        //// Calculate the movement distance for each point
        //double moveDistance = (minDistance - distance) / 2.0;

        //// Calculate the movement components
        //double moveX1 = (moveDistance / length) * dx;
        //double moveY1 = (moveDistance / length) * dy;
        //double moveX2 = -moveX1; // Move in opposite directions
        //double moveY2 = -moveY1;

        //// Update the positions of the points
        //point1.setPosition(point1.getPosition().first + moveX1, point1.getPosition().second + moveY1);
        //point2.setPosition(point2.getPosition().first + moveX2, point2.getPosition().second + moveY2);
        return true;
    }
    return false;
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

