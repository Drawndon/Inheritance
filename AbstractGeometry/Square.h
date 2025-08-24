#pragma once
#include "Shape.h"

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	double get_side()const;
	void set_side(double side);
	double get_area()const override;
	double get_perimeter()const override;
	void draw()const override;

	void info()const override;
};
