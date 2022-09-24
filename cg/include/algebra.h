#pragma once

#include <iostream>

using std::ostream;

// vector of 3 positions (x, y, z)
class Vector {
    private:
        double positions[3];

    public:
        // get the magnitude of vector: || vector ||
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

// returns the scalar product of two vectors
double scalarProduct (Vector a, Vector b);
// returns the scalar product of two vectors
double scalarProduct (Vector *a, Vector *b);

// return the max of a and b
double min (double a, double b);

// return the min of a and b
double max (double a, double b);

// return the vector product of two vectors a and b
Vector vectorProduct (Vector a, Vector b);