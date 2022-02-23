#include "Vector.h"

Vector::Vector(double x, double y) : x(x), y(y) {};
Vector::Vector() : Vector(0, 0) {}

Vector Vector::operator+(const Vector& vector)
{
    double new_x = x + vector.x;
    double new_y = y + vector.y;
    
    return Vector(new_x, new_y);
}

Vector& Vector::operator+=(const Vector& vector)
{
    this->x = x + vector.x;
    this->y = y + vector.y;

    return *this;
}

Vector Vector::operator-(const Vector& vector)
{
    double new_x = x - vector.x;
    double new_y = y - vector.y;
    
    return Vector(new_x, new_y);
}

Vector Vector::operator*(const double k)
{
    double new_x = x * k;
    double new_y = y * k;
    
    return Vector(new_x, new_y);
}

Vector& Vector::operator=(const Vector& vector)
{
    x = vector.x;
    y = vector.y;
}

double Vector::get_x() const
{
    return x;
}

double Vector::get_y() const
{
    return y;
}

String Vector::to_string()
{
    String string = String("(") + String(x) + ", " + String(y) + ")";
    return string;
}

Vector operator*(const double k, const Vector& vector)
{
    double new_x = vector.get_x() * k;
    double new_y = vector.get_y() * k;
    
    return Vector(new_x, new_y);
}