#include "Point.h"
#include <cmath>

Point::Point(pair<double, double> position, pair<double, double> velocity, double mass, string color, pair<double, double> acceleration, double timeFrame)
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass), timeFrame(timeFrame), radius(std::log(mass) / std::log(0.09)), isInvisable(false), color(color) {}

pair<double, double> Point::getPosition() const
{
    return position;
}

void Point::setPosition(double newX, double newY)
{
    position = std::make_pair(newX, newY);
}

pair<double, double> Point::getVelocity() const
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

void Point::setAcceleration(pair<double, double> newAccceleration)
{
    acceleration = newAccceleration;
}

double Point::getMass() const
{
    return mass;
}

void Point::setMass(double newMass)
{
    mass = newMass;
}

double Point::getTimeFrame()
{
    return timeFrame;
}

void Point::setTimeFrame(double newTimeFrame)
{
    timeFrame = newTimeFrame;
}

void Point::updatePoint(const vector<Point>& allPoints)
{
     // updating acceleration
    updateAcceleration(allPoints);

    // updating velocity
    updateVelocity();


    if (!isInvisable)
    {
       

        // updating point position
        updatePosition(allPoints);
    }
    
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
    velocity.first += acceleration.first * timeFrame;
    velocity.second += acceleration.second * timeFrame;
    
    // setting the max velocity to 1000 m/s
    if (velocity.first > 1000) { velocity.first = 1000; }
    if (velocity.second > 1000) {velocity.second = 1000; }


    return velocity;
}

void Point::updatePosition(const vector<Point>& allPoints)
{
    // getting direction (angle)
    direction = 1 / std::atan2(velocity.first, velocity.second);

    // moving pos
    position.first += velocity.first * timeFrame;
    position.second += velocity.second * timeFrame;
}

double Point::getDistance(const Point& otherPoint) const
{
    return std::sqrt(std::pow(otherPoint.position.first - position.first, 2) + pow(otherPoint.position.second - position.second, 2));
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

int Point::getDirection() const
{
    return direction;
}

int Point::getRadius() const
{
    return radius;
}

void Point::setRadius(int newRadius)
{
    radius = newRadius;
}

double Point::checkAngle(const Point& other)
{
    double dx = other.position.first - this->position.first;
    double dy = other.position.second - this->position.second;

    double angle = atan2(dy, dx) * 180.0 / M_PI;

    return angle;
}

void Point::moveByAngle(double distance, double angle)
{
    this->position.first += distance * cos(angle * (M_PI / 180));
    this->position.second += distance * sin(angle * (M_PI / 180));
}

void Point::setInvisable()
{
    isInvisable = true;
}

bool Point::isPointInvisable() const
{
    return isInvisable;
}

void Point::downgradeVelocity()
{
    velocity.first *= 0.999;
    velocity.second *= 0.999;
}

void Point::setColor(const string& color)
{
    this->color = color;
}

string Point::getColor() const
{
    return color;
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
            double forceX = currForce * std::round(std::cos(angle));
            double forceY = currForce * std::round(std::sin(angle));

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
    if (distance < 100)
    {
        distance = 100;
    }
    double force = (G * mass * otherPoint.mass) / (distance * distance);

    return force;
}

