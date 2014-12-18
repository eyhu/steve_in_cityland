#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "string"
#include "Vector3.h"
#include "Vector4.h"

//#define M_PI 3.14159265358979323846

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    // Constructors
    Matrix4();
    Matrix4(double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double);
    
    // Destructors
    virtual ~Matrix4();
    
    // Overloaded Operators
    Matrix4& operator=(const Matrix4&);
    //Matrix4& operator*(const Matrix4&);
    Matrix4 operator*(const Matrix4);
    Vector4& operator*(const Vector4&);
    Vector4& mult(const Vector4&);
    
    // Setter
    void set(int, int, double);
    // Getter
    double get(int, int) const;
    
    // gets pointer to matrix
    double* getPointer();
    // creates identity matrix
    void identity();
    // trasposes
    void transpose();
    
    // rotational functions
    void makeRotateY(double);
    void makeRotateX(double);
    void makeRotateZ(double);
    void makeRotate(double, const Vector3&);
    
    // creates a scaling matrix
    void makeScale(double, double, double);
    // creates a translation matrix
    void makeTranslate(double, double, double);
    // prints the matrix
    void print(std::string);
};

#endif