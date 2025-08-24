#pragma once

class Point
{

public:
	double get_x()const;
	double get_y()const;
	void set_x(double x);
	void set_y(double y);

	// Constructors

	Point(double x = 0, double y = 0);
	Point(const Point& other);

	// Operators
	Point& operator=(const Point& other);
	// Methods
	double distance(const Point& other)const;

};