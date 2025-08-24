#pragma once
#include "stdafx.h"
using namespace std;

enum Color
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Orange = 0x0000A5FF,
	White = 0x00FFFFFF,
	SomeColor // ������ �� ��������� ����� �� 1 ������ �����������
};

class Shape
{
	Color color;
public:
	Shape(Color color) :color(color) {/*���� ������������*/ }
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "������� ������: " << get_area() << endl;
		cout << "�������� ������: " << get_perimeter() << endl;
		draw();
	}

};
