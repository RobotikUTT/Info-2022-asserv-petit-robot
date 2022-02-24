#include "Vector.h"
#include <math.h>

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector() : Vector(0, 0) {}

Vector::Vector(const Vector &copy): Vector(copy.x, copy.y) {}

Vector Vector::operator+(const Vector &vector) {
    return Vector(this->x + vector.x, this->y + vector.y);
}

Vector &Vector::operator+=(const Vector &vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector Vector::operator-(const Vector &vector) {
    return Vector(this->x - vector.x, this->y - vector.y);
}

Vector Vector::operator*(const double k) {
    return Vector(x * k, y * k);
}

Vector &Vector::operator*=(const double k) {
    x *= k;
    y *= k;
    return *this;
}

Vector &Vector::operator=(const Vector &vector) {
    this->x = vector.x;
    this->x = vector.y;
    return *this;
}

double Vector::scalar(const Vector &other) const {
    return this->x * other.x + this->y * other.y;
}

Vector Vector::normal() const {
    return Vector(-y, x);
}

double Vector::angle_with(const Vector &other) const {
    return acos(this->scalar(other) / this->get_norm() / other.get_norm());
}

double Vector::get_norm() const {
    return sqrt(x * x + y * y);
}

double Vector::get_x() const {
    return x;
}

double Vector::get_y() const {
    return y;
}

String Vector::to_string() {
    String string = String("(") + String(x) + ", " + String(y) + ")";
    return string;
}

Vector operator*(const double k, const Vector &vector) {
    return Vector(vector.get_x() * k, vector.get_y() * k);
}