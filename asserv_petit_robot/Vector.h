#ifndef VECTOR_H
#define VECTOR_H

#include <Arduino.h>

class Vector {
    private:
        double x, y;
    public:
        /**
         * Default constructor. Default vector has coordinates (0, 0)
         */
        Vector();
        /**
         * Constructor with named parameters
         * @param x x coordinate
         * @param y y coordinate
         */
        Vector(double x, double y);
        Vector(const Vector &copy);
        Vector operator+(const Vector &);
        Vector operator-(const Vector &);
        Vector operator*(const double k);
        Vector &operator*=(const double k);
        Vector &operator+=(const Vector &);
        Vector &operator=(const Vector &);
        /**
         * Compute the scalar product of two vectors.
         * @example Vector v1(1, 2); Vector v2(2, 3); double scalar = v1.scalar(v2); // returns 8.0
         * @param other the other Vector to do the product with.
         * @return the result of the scalar product
         */
        inline double scalar(const Vector &other) const;
        /**
         * Create and return the normal vector to this vector.
         * The new vector is normal in trigonometrical direction.
         * @example Vector v1(1, 2); Vector v2(v1.normal()); // v2 has coordinates (-2, 1)
         * @return a new Vector which is normal to this vector
         */
        inline Vector normal() const;

        /**
         * Compute and return the angle between this vector and another.
         * @example Vector v1(1, 2), v2(-2, 1); double angle = v1.angle_with(v2); // angle has value 1.570, which pi / 2
         * @param other the other vector to calculate the angle with
         * @return the angle between this vector and the other
         */
        double angle_with(const Vector &other) const;
        /**
         * Compute and return the norm of the vector
         * @example double norm = Vector(1, 2).norm(); // norm has value 2.236
         * @return the norm of the vector
         */
        double get_norm() const;
        inline double get_x() const;
        inline double get_y() const;

        String to_string();
};

Vector operator*(const double k, const Vector &vector);


#endif