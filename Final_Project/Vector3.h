#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>
#include <math.h>

using namespace std;

class Vector3 {
protected:
    
    double v[3]; // Array elements
    
public:
    
    //Constructor
    Vector3();
    Vector3(double, double, double);
    
    // Destructor
    virtual ~Vector3();
    
    // Overloaded Operators
    Vector3& operator=(const Vector3&);
    Vector3 operator+(const Vector3&);
    Vector3 operator-(const Vector3&);
    
    // setters for vector array
    void set(double, double, double);
    void setX(double);
    void setY(double);
    void setZ(double);
    
    // getters for vector array
    double get(int) const;
    double getX() const;
    double getY() const;
    double getZ() const;
    
    void negate();
    void scale(double s); // scales vector elements

    // dot product, returns result
    double dot(const Vector3&, const Vector3&);
    // cross product, returns result and puts it in calling vector
    Vector3 cross(const Vector3&, const Vector3&);
    // length of the vector
    double length();
    // makes length of vector into 1
    void normalize();
    // shifts vector
    void translate(double, double, double);
    // resets to 0
    void reset();
    // orbiting
    void orbit(double);
    // prints the elements of the array after a comment
    void print(std::string);
    
};
#endif