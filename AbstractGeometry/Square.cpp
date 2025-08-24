#include "Square.h"

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side;
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return 4 * side;
	}
	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны квадрата: " << get_side() << endl;
		Shape::info();
	}
};