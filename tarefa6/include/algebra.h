#pragma once

#include <iostream>

using std::ostream;

// vector of 3 positions (x, y, z)
class Vector {
    private:
        double positions[3];

    public:
        double getMagnitude ();

        double& operator [] (int index);
        Vector operator + (const Vector& operand);
        Vector operator + (const double& operand);
        Vector operator - (const Vector& operand);
        Vector operator - (const double& operand);
        Vector operator * (const Vector& operand);
        Vector operator * (const double& operand);
        Vector operator / (const Vector& operand);
        Vector operator / (const double& operand);
        
        Vector ();
        Vector (double x, double y, double z);
};

ostream& operator << (ostream& os, Vector vector);

double scalarProduct (Vector a, Vector b);
double scalarProduct (Vector *a, Vector *b);

double min (double a, double b);

double max (double a, double b);

Vector rotateX(Vector a, double angle);
Vector rotateZ(Vector a, double angle);
Vector rotateY(Vector a, double angle);
Vector translate(Vector a, double x, double y, double z);
Vector scale(Vector a, double sx, double sy, double sz);
Vector reflectXY(Vector a);
Vector reflectXZ(Vector a);
Vector reflectYZ(Vector a);
Vector shearYX(Vector a, double angle);
Vector shearXY(Vector a, double angle);
Vector shearXZ(Vector a, double angle);
Vector shearZX(Vector a, double angle);
Vector shearYZ(Vector a, double angle);
Vector shearZY(Vector a, double angle);

Vector vectorProduct (Vector a, Vector b);