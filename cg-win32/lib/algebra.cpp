#include <cmath>
#include "../include/algebra.h"

double min (double a, double b) {
    if (a < b) {
        return a;
    }

    return b;
}

double max (double a, double b) {
    if (a > b) {
        return a;
    }

    return b;
}

Vector rotateX(Vector a, double angle) {
    return Vector(
        a[0],
        a[1]*cos(angle) - a[2]*sin(angle),
        a[1]*sin(angle) + a[2]*cos(angle)
    );
}

Vector rotateZ(Vector a, double angle) {
    return Vector(
        a[0]*cos(angle) - a[1]*sin(angle),
        a[0]*sin(angle) + a[1]*cos(angle),
        a[2]
    );
}

Vector rotateY(Vector a, double angle) {
    return Vector(
        a[0]*cos(angle) + a[2]*sin(angle),
        a[1],
        -a[0]*sin(angle) + a[2]*cos(angle)
    );
}

Vector translate(Vector a, double x, double y, double z) {
    return Vector(
        a[0] + x,
        a[1] + y,
        a[2] + z
    );
}

Vector scale(Vector a, double sx, double sy, double sz) {
    return Vector(
        a[0] * sx,
        a[1] * sy,
        a[2] * sz
    );
}

Vector reflectXY(Vector a) {
    return Vector(
        a[0],
        a[1],
        -a[2]
    );
}

Vector reflectXZ(Vector a) {
    return Vector(
        a[0],
        -a[1],
        a[2]
    );
}

Vector reflectYZ(Vector a) {
    return Vector(
        -a[0],
        a[1],
        a[2]
    );
}

Vector shearYX(Vector a, double angle) {
    return Vector(
        a[0] + a[1] * tan(angle),
        a[1],
        a[2]
    );
}

Vector shearXY(Vector a, double angle) {
    return Vector(
        a[0],
        a[1] + a[0] * tan(angle),
        a[2]
    );
}

Vector shearXZ(Vector a, double angle) {
    return Vector(
        a[0],
        a[1],
        a[2] + a[0] * tan(angle)
    );
}

Vector shearZX(Vector a, double angle) {
    return Vector(
       a[0] + a[2] * tan(angle),
       a[1],
       a[2]
    );
}

Vector shearYZ(Vector a, double angle) {
    return Vector(
        a[0],
        a[1],
        a[2] + a[1] * tan(angle)
    );
}

Vector shearZY(Vector a, double angle) {
    return Vector(
        a[0],
        a[1] + a[2] * tan(angle),
        a[2]
    );
}

Vector vectorProduct (Vector a, Vector b) {
    return Vector (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    );
}

Vector::Vector () {}

Vector::Vector (double x, double y, double z) {
    this->positions[0] = x;
    this->positions[1] = y;
    this->positions[2] = z;
}

double& Vector::operator [] (int idx) {
    return this->positions[idx % 3];
}

Vector Vector::operator + (const Vector& operand) {
    Vector result (
        this->positions[0] + operand.positions[0],
        this->positions[1] + operand.positions[1],
        this->positions[2] + operand.positions[2]
    );

    return result;
}

Vector Vector::operator + (const double& operand) {
    Vector result (
        this->positions[0] + operand,
        this->positions[1] + operand,
        this->positions[2] + operand
    );

    return result;
}

Vector Vector::operator - (const Vector& operand) {
    Vector result (
        this->positions[0] - operand.positions[0],
        this->positions[1] - operand.positions[1],
        this->positions[2] - operand.positions[2]
    );

    return result;
}

Vector Vector::operator - (const double& operand) {
    Vector result (
        this->positions[0] - operand,
        this->positions[1] - operand,
        this->positions[2] - operand
    );

    return result;
}

Vector Vector::operator * (const Vector& operand) {
    Vector result (
        this->positions[0] * operand.positions[0],
        this->positions[1] * operand.positions[1],
        this->positions[2] * operand.positions[2]
    );

    return result;
}

Vector Vector::operator * (const double& operand) {
    Vector result (
        this->positions[0] * operand,
        this->positions[1] * operand,
        this->positions[2] * operand
    );

    return result;
}

Vector Vector::operator / (const Vector& operand) {
    Vector result (
        this->positions[0] / operand.positions[0],
        this->positions[1] / operand.positions[1],
        this->positions[2] / operand.positions[2]
    );

    return result;
}

Vector Vector::operator / (const double& operand) {
    Vector result (
        this->positions[0] / operand,
        this->positions[1] / operand,
        this->positions[2] / operand
    );

    return result;
}

ostream& operator << (ostream& os, Vector vector) {
    os << "Vector [" << vector[0] << ", " << vector[1] << ", " << vector[2] << "]";
    return os;
}

double Vector::getMagnitude () {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += pow (this->positions[i], 2.0);
    }

    return sqrt (result);
}

double scalarProduct (Vector a, Vector b)  {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += a[i] * b[i];
    }

    return result;
}

double scalarProduct (Vector *a, Vector *b)  {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += (*a)[i] * (*b)[i];
    }

    return result;
}