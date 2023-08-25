#include "Point.h"
#include <cmath>

Point::Point(pair<double, double> position, pair<double, double> velocity, pair<double, double> acceleration, double mass, double timeFrame, int radius)
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass), timeFrame(timeFrame), radius(radius) {}

pair<double, double> Point::getPosition() const
{
    return position;
}

void Point::setPosition(double newX, double newY)
{
    position = std::make_pair(newX, newY);
}

pair<double, double> Point::getvelocity() const
{
    return velocity;
}

void Point::setVelocity(pair<double, double> newvelocity)
{
    velocity = newvelocity;
}

pair<double, double> Point::getAcceleration() const
{
    return acceleration;
}

void Point::setAcceleration(pair<double, double> newAcceleration)
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

pair<double, double> Point::updateAcceleration(const vector<Point>& allPoints)
{
    // calculating acceleration by 
    acceleration.first = calcNetForce(allPoints).first / mass;
    acceleration.second = calcNetForce(allPoints).second / mass;
    return acceleration;
}

pair<double, double> Point::updateVelocity()
{
    // adding acceleration to velocity
    velocity.first = velocity.first + acceleration.first * timeFrame;
    velocity.second = velocity.second + acceleration.second * timeFrame;
    
    // setting the max velocity to 1000 m/s
    if (velocity.first > 1000) { velocity.first = 1000; }
    if (velocity.second > 1000) {velocity.second = 1000; }


    return velocity;
}

void Point::updatePosition(const vector<Point>& allPoints)
{
    // getting direction (angle)
    direction = std::atan2(velocity.second, velocity.first);

    // moving pos
    position.first += velocity.first * timeFrame;
    position.second += velocity.second * timeFrame;
}

double Point::getDistance(const Point& otherPoint) const
{
    return std::hypot(otherPoint.position.first - position.first, otherPoint.position.second - position.second);
}

double Point::getMomentum() const
{
    return mass * getTotalVelocity();
}

double Point::getTotalVelocity() const
{
    return std::sqrt(std::pow(velocity.first, 2) + std::pow(velocity.second, 2));

}

double Point::getTotalAcceleration() const
{
    return std::sqrt(std::pow(acceleration.first, 2) + std::pow(acceleration.second, 2));
}

double Point::getDirection() const
{
    return direction;
}

int Point::getRadius() const
{
    return radius;
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

