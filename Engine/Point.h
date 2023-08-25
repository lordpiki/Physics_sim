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
    Point(pair<double, double> position = std::make_pair(0, 0), pair<double, double> velocity = std::make_pair(0, 0), pair<double, double> acceleration = std::make_pair(0, 0), double mass = std::pow(10, 6), double timeFrame = 50);
        

    // Getter and setter for position 
    pair<double, double> getPosition() const;
    void setPosition(double newX, double newY);

    pair<double, double> getvelocity() const;
    void setVelocity(pair<double, double> newvelocity);

    pair<double, double> getAcceleration() const;
    void setAcceleration(pair<double, double> newAcceleration);

    double getMass() const;
    void setMass(double newMass);
    

    void updatePoint(const vector<Point>& allPoints);
    
    pair<double, double> updateAcceleration(const vector<Point>& allPoints);
    pair<double, double> updateVelocity();
    void updatePosition(const vector<Point>& allPoints);

    double getDistance(const Point& otherPoint) const;
    double getMomentum() const;


    double getTotalVelocity() const;
    double getTotalAcceleration() const;
    double getDirection() const;
    int getRadius() const;


private:

    pair<double, double> position; // X and Y values represented as a pair
    pair<double, double> velocity;       // velocity of the point
    pair<double, double> acceleration; // Acceleration of the point
    double direction;
    int radius;
    double mass;        // Mass of the point
    double timeFrame;

    // function to calculate gravitational force to another single point
    double calcGravitationalForce(const Point& otherPoint) const;

    // function to calculate gravitational net force for all points (x,y directions)
    // returns x, y
    pair<double, double> calcNetForce(const vector<Point>& allPoints);



};

