#pragma once
#include <utility> // Include for std::pair
#include <cmath> // Include for mathematical functions
#include <vector>
#include <math.h>
#include <cmath>



#define G 6.67430e-11

using std::pair;
using std::vector;

class Point {
public:
    // Constructor with default values
    Point(double x = 0.0, double y = 0.0, double velocity = 0.0, double acceleration = 0.0, double mass = std::pow(10, 6), double timeFrame = 50)
        : position(std::make_pair(x, y)), velocity(velocity), acceleration(acceleration), mass(mass), timeFrame(timeFrame) {}

    // Getter and setter for position 
    pair<double, double> getPosition() const;
    void setPosition(double newX, double newY);

    double getvelocity() const;
    void setvelocity(double newvelocity);

    double getAcceleration() const;
    void setAcceleration(double newAcceleration);

    double getMass() const;
    void setMass(double newMass);
    

    void updatePoint(const vector<Point>& allPoints);
    
    double updateAcceleration(const vector<Point>& allPoints);
    double updateVelocity();
    void updatePosition(const vector<Point>& allPoints);

    double getDistance(const Point& otherPoint);




private:

    pair<double, double> position; // X and Y values represented as a pair
    double velocity;       // velocity of the point
    double acceleration; // Acceleration of the point
    double mass;        // Mass of the point
    double timeFrame;

    // function to calculate gravitational force to another single point
    double calcGravitationalForce(const Point& otherPoint) const;

    // function to calculate gravitational net force for all points (x,y directions)
    // returns x, y
    pair<double, double> calcNetForce(const vector<Point>& allPoints);


};

