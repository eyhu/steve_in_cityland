#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "string"

class Vector4 {
protected:
    double v[4];   // array elements
    
public:
    
    // Constructor
    Vector4();
    Vector4(double, double, double, double);
    
    // Destructor
    virtual ~Vector4();
    
    // Overloaded Operators
    Vector4& operator+(const Vector4&);
    Vector4& operator-(const Vector4&);
    
    // getter for vector array
    double getValue(int) const;
    // setter for vector array
    void setValue(int, double);
    // length of the vector
    double length();
    // scales vector so the fourth value equals 1 (ie: x/w; y/w; z/w)
    void dehomogenize();
    // shifts vector
    void translate(double, double, double);
    // resets values to 0
    void reset();
    // prints the elements of the array after a comment
    void print(std::string);
    
    // What does this set?  IDK; ALL OF IT
    void set(double, double, double, double);
    double get(int);
  
};

#endif