#include "Point.h"
#include <cmath>

pair<double, double> Point::getPosition() const
{
    return position;
}

void Point::setPosition(double newX, double newY)
{
    position = std::make_pair(newX, newY);
}

double Point::getvelocity() const
{
    return velocity;
}

void Point::setvelocity(double newvelocity)
{
    velocity = newvelocity;
}

double Point::getAcceleration() const
{
    return acceleration;
}

void Point::setAcceleration(double newAcceleration)
{
    acceleration = newAcceleration;
}

double Point::getMass() const
{
    return mass;
}

void Point::setMass(double newMass)
{
    mass = newMass;
}

void Point::updatePoint(const vector<Point>& allPoints)
{
    // updating acceleration
    updateAcceleration(allPoints);

    // updating velocity
    updateVelocity();

    // updating point position
    updatePosition(allPoints);
}

double Point::updateAcceleration(const vector<Point>& allPoints)
{
    // calculating acceleration by 
    acceleration = std::sqrt(std::pow(calcNetForce(allPoints).first, 2) + std::pow(calcNetForce(allPoints).second, 2)) / mass;
    return acceleration;
}

double Point::updateVelocity()
{
    // adding acceleration to velocity
    velocity = velocity + acceleration * timeFrame;
    return velocity;
}

void Point::updatePosition(const vector<Point>& allPoints)
{
    // getting direction (angle)
    double direction = std::atan2(calcNetForce(allPoints).second, calcNetForce(allPoints).first);

    // moving pos
    position.first += velocity * timeFrame * std::cos(direction);
    position.second += velocity * timeFrame * std::sin(direction);
}

pair<double, double> Point::calcNetForce(const vector<Point>& allPoints)
{
    // x and y net force directions (can be later merged)
    pair<double, double> netForce; 

    for (const Point& otherPoint : allPoints)
    {
        // checking that the otherPoint isn't the current Point
        if (&otherPoint != this)
        {
            // get the force and calculate angel to the other point
            double currForce = calcGravitationalForce(otherPoint);
            double deltaX = otherPoint.position.first - position.first;
            double deltaY = otherPoint.position.second - position.second;
            double angle = std::atan2(deltaY, deltaX);

            // Calculate components of force along X and Y axes
            double forceX = currForce * std::cos(angle);
            double forceY = currForce * std::sin(angle);

            // adding forces to x and y directions
            netForce.first += forceX;
            netForce.second += forceY;
        }
    }

    return netForce;
}

double Point::calcGravitationalForce(const Point& otherPoint) const
{
    // calculate distance between 2 points
    double distance = std::hypot(otherPoint.position.first - position.first, otherPoint.position.second - position.second);

    // Calculate the gravitational force using the gravity formula
    double force = (G * mass * otherPoint.mass) / (distance * distance);

    return force;
}

