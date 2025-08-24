#include <iostream>
using namespace std;

#define PI 3.14159265358979323846

enum Color
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Orange = 0x0000A5FF,
	White = 0x00FFFFFF,
	SomeColor // Ничего не присвоили будет на 1 больше предыдущего
};

class Shape
{
	Color color;
public:
	Shape(Color color):color(color) {/*Тело конструктора*/}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}

};

class Rectangle :public Shape
{
	double length;
	double width;
public:
	Rectangle(double length, double width, Color color) :Shape(color)
	{
		set_length(length);
		set_width(width);
	}
	double get_length()const
	{
		return length;
	}
	double get_width()const
	{
		return width;
	}
	void set_length(double length)
	{
		this->length = length;
	}
	void set_width(double width)
	{
		this->width = width;
	}
	double get_area()const override
	{
		return length * width;
	}
	double get_perimeter()const override
	{
		return 2 * (length + width);
	}
	void draw()const override
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}

	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина прямоугольника: " << get_length() << endl;
		cout << "Ширина прямоугольника: " << get_width() << endl;
		Shape::info();
	}

};

class Square :public Rectangle
{
	double side;
public:
	Square(double side, Color color) :Rectangle(side, side, color) {}
};

class Circle : public Shape
{
	int radius;
public:
	Circle(int radius, Color color) :Shape(color)
	{
		set_radius(radius);
	}
	int get_radius()const
	{
		return radius;
	}
	void set_radius(int radius)
	{
		this->radius = radius;
	}
	double get_area()const override
	{
		return PI * pow(get_radius(), 2);
	}
	double get_perimeter()const override
	{
		return 2 * PI * radius;
	}

	void draw()const override
	{
		for (int y = radius; y >= -radius; y--) {
			for (int x = -radius; x <= radius; x++) {
				if (round(sqrt(x * x + y * y)) == radius) cout << "*";
				else cout << " ";
			}
			cout << endl;
		}
	}

	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Радиус круга: " << get_radius() << endl;
		Shape::info();
	}

};

void main()
{
	setlocale(LC_ALL, "");
	//cout << hex << Color::SomeColor << endl; // Ничего не присвоили будет на 1 больше чем предыдущего (то есть White)
	//Shape shape(Color::Red);

	Square square(5, Color::Red);
	square.draw();
	cout << "\n-----------------------------------------------\n" << endl;
	square.info();

	Circle cir(5, Color::Green);
	//cir.draw();
	cout << "\n-----------------------------------------------\n" << endl;
	cir.info();

	Rectangle rect(10, 4, Color::Yellow);
	rect.draw();
	cout << "\n-----------------------------------------------\n" << endl;
	rect.info();

}