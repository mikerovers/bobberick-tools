//
// Created by Mike Rovers on 30/08/2018.
//

#ifndef CLIONTESTSDL_VECTOR2D_H
#define CLIONTESTSDL_VECTOR2D_H
#include <ostream>


class Vector2D
{
public:
	double x;
	double y;

	Vector2D();
	Vector2D(double x, double y);

	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};


#endif //CLIONTESTSDL_VECTOR2D_H
