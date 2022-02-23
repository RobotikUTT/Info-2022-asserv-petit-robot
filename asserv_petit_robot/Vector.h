#ifndef VECTOR_H
#define VECTOR_H

#include <Arduino.h>

class Vector
{
private:
    double x, y;
public:

    Vector();
    Vector(double x, double y);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    Vector operator*(const double k);
    Vector& operator+=(const Vector&);
    Vector& operator=(const Vector&);

    double get_x() const;
    double get_y() const;

    String to_string();
};

Vector operator*(const double k, const Vector& vector);



#endif