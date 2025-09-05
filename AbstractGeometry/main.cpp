#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		Black = 0x00000000,
		White = 0x00FFFFFF,
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
		HDC hdc;
		HPEN hPen;
		HBRUSH hBrush;

	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 512;

		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			hdc = GetDC(GetDesktopWindow());

			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

			hPen = CreatePen(PS_SOLID, line_width, color);
			hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
		}
		~Shape()
		{
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(GetDesktopWindow(), hdc);
		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int filter_size(int size) const
		{
			return	size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		int get_start_x() const
		{
			return start_x;
		}
		int get_start_y() const
		{
			return start_y;
		}
		int get_line_width() const
		{
			return line_width;
		}
		virtual double get_area() const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw() const = 0;
		virtual void info() const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square : public Shape
	{
	private:
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		double get_side() const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area() const override
		{
			return side * side;
		}
		double get_perimeter() const override
		{
			return side * 4;
		}
		void draw() const override
		{
			for (int i = 0; i < side; ++i)
			{
				for (int j = 0; j < side; ++j)
				{
					cout << "* ";
				}
				cout << endl;
			}
			cout << endl;
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle : public Shape
	{
	private:
		double height;
		double width;

	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_height(height);
			set_width(width);
		}

		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_width() const
		{
			return width;
		}
		double get_height() const
		{
			return height;
		}
		double get_area() const override
		{
			return width * height;
		}
		double get_perimeter() const override
		{
			return 2 * (width + height);
		}

		void draw() const override
		{
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << "x" << height << endl;
			Shape::info();
		}
	};

	class Square : public Rectangle
	{
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};

	class Circle : public Shape
	{
	private:
		double radius;

	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}

		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius() const
		{
			return radius;
		}
		double get_diameter() const
		{
			return 2 * radius;
		}
		double get_area() const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter() const override
		{
			return M_PI * get_diameter();
		}

		void draw() const override
		{
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
		}
	};

	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}

		virtual double get_height() const = 0;
	};

	class EquilateralTriangle : public Triangle
	{
	private:
		double side;

	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side() const
		{
			return side;
		}
		double get_height() const override
		{
			return sqrt(pow(side, 2) - pow(side, 2) / 2);
		}
		double get_area() const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter() const override
		{
			return side * 3;
		}

		void draw() const override
		{
			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + side, start_y + get_height() },
				{ start_x + side / 2, start_y }
			};

			::Polygon(hdc, vertices, 3);
		}
	};

	class IsoscelesTriangle : public Triangle
	{
	private:
		double side;
		double base;

	public:
		IsoscelesTriangle(double side, double base, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_base(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side() const
		{
			return side;
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		double get_base() const
		{
			return base;
		}
		double get_height() const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area() const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter() const override
		{
			return side * 2 + base;
		}

		void draw() const override
		{
			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + base, start_y + get_height() },
				{ start_x + base / 2, start_y }
			};

			::Polygon(hdc, vertices, 3);
		}
	};

	class ScaleneTriangle : public Triangle
	{
	private:
		double side1;
		double side2;
		double side3;

	public:
		ScaleneTriangle(double side1, double side2, double side3, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			if (side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2)
			{
				set_side1(side1);
				set_side2(side2);
				set_side3(side3);
			}
			else
			{
				set_side1(50);
				set_side2(50);
				set_side3(50);
			}
		}
		void set_side1(double side1)
		{
			this->side1 = filter_size(side1);
		}
		double get_side1() const
		{
			return side1;
		}
		void set_side2(double side2)
		{
			this->side2 = filter_size(side2);
		}
		double get_side2() const
		{
			return side2;
		}
		void set_side3(double side3)
		{
			this->side3 = filter_size(side3);
		}
		double get_side3() const
		{
			return side3;
		}
		double get_height() const override
		{
			return 2 * get_area() / side1;
		}
		double get_area() const override
		{
			double halfperimeter = get_perimeter() / 2;
			return sqrt(halfperimeter * (halfperimeter - side1) * (halfperimeter - side2) * (halfperimeter - side3));
		}
		double get_perimeter() const override
		{
			return side1 + side2 + side3;
		}

		void draw() const override
		{
			double cos_angle = (side2 * side2 + side1 * side1 - side3 * side3) / (2 * side2 * side1);
			double sin_angle = sqrt(1 - cos_angle * cos_angle);

			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + side1, start_y + get_height() },
				{ start_x + side2 * cos_angle, start_y + get_height() - side2 * sin_angle }
			};

			::Polygon(hdc, vertices, 3);
		}
	};
}

int main()
{
	setlocale(LC_ALL, "");

	Geometry::Square square(100, 100, 100, 1, Geometry::Color::Red);
	square.info();

	Geometry::Rectangle rect(150, 100, 550, 100, 2, Geometry::Color::Orange);
	rect.info();

	Geometry::Circle circle(50, 800, 200, 1, Geometry::Color::Yellow);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(50, 550, 350, 1, Geometry::Color::Green);
	e_triangle.info();

	Geometry::IsoscelesTriangle i_triangle(80, 50, 650, 450, 1, Geometry::Color::Red);
	i_triangle.info();

	Geometry::ScaleneTriangle s_triangle(40, 50, 80, 750, 550, 1, Geometry::Color::White);
	s_triangle.info();

	while (true)
	{
		square.draw();
		rect.draw();
		circle.draw();
		e_triangle.draw();
		i_triangle.draw();
		s_triangle.draw();
	}

	return 0;
}