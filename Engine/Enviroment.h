#pragma once
#include "Point.h"


class Enviroment
{
public:
	// c'tor
	Enviroment();

	// adding point
	void addPoint(const Point& point);
	void reset();

	vector<Point> getPoints() const;

	void upatePoints();

	void checkColision();
	

private:
	vector<Point> points;

	void updateColision(Point& point1, Point& point2);
};

