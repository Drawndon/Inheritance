#include "Point.h"

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	// Constructors

	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	// Operators
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
	// Methods
	double distance(const Point& other)const
	{
		//other.x *= 100 // E0137
		//this->x *= 100 // E0137
		double x_diff = this->get_x() - other.get_x();
		double y_diff = this->get_y() - other.get_y();
		return sqrt(x_diff * x_diff + y_diff * y_diff);
	}

};