#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

#include "Vector3.h"

//Constructor
Vector3::Vector3() {
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}


Vector3::Vector3(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}


// Destructor
Vector3::~Vector3() {
    
}



// Overloading for equals
Vector3& Vector3::operator=(const Vector3& v2) {
    v[0] = v2.getX();
    v[1] = v2.getY();
    v[2] = v2.getZ();
    
    return *this;
}


// Overloading for addition
Vector3 Vector3::operator+(const Vector3& v2) {
    Vector3* temp = new Vector3(0.0, 0.0, 0.0);
    
    for (int i = 0; i < 3; i++) {
        temp->v[i] = this->v[i] + v2.v[i];
    }
    return *temp;
}


// Overloading for subtraction
Vector3 Vector3::operator-(const Vector3& v2) {
    Vector3* temp = new Vector3(0.0, 0.0, 0.0);
    
    for (int i = 0; i < 3; i++) {
        temp->v[i] = this->v[i] - v2.v[i];
    }
    return *temp;
}



// setters for vector array
void Vector3::set(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Vector3::setX(double x) {
    v[0] = x;
}


void Vector3::setY(double y) {
    v[1] = y;
}


void Vector3::setZ(double z) {
    v[2] = z;
}



// getters for vector array
double Vector3::get(int i) const {
    return v[i];
}


double Vector3::getX() const {
    return v[0];
}


double Vector3::getY() const {
    return v[1];
}


double Vector3::getZ() const{
    return v[2];
}



// Negation of all values of the vector
void Vector3::negate(){
    for (int i = 0; i < 3; i++) {
        v[i] = v[i] * (-1);
    }
}


// Scaling
void Vector3::scale(double s) {
    for (int i = 0; i < 3; i++) {
        v[i] = v[i] * s;
    }
}



// dot product, returns result
double Vector3::dot(const Vector3& v1, const Vector3& v2) {
    double result = 0;
    
    for (int i = 0; i < 3; i++) {
        result += (v1.v[i] * v2.v[i]);
    }
    
    return result;
}


// cross product, returns result and puts it in calling vector
Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
    /*double x, y, z;
    
    // x = (y1 * z2) - (z1 * y2)
    x = (v1.getY() * v2.getZ()) - (v1.getZ() * v2.getY());
    
    // y = (z1 * x2) - (x1 * z2)
    y = (v1.getZ() * v2.getX()) - (v1.getX() * v2.getZ());
    
    // z = (x1 * y2) - (y1 * x2)
    z = (v1.getX() * v2.getY()) - (v1.getY() * v2.getX());
    
    return Vector3(x, y, z);*/
    
   /* v[0] = (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]);
    v[1] = (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]);
    v[2] = (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]);
    
    return *this;*/
    Vector3 temp;
    
    double x= (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]);
    double y = - (v1.v[0] * v2.v[2]) + (v1.v[2] * v2.v[0]);
    double z = (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]);
    temp.set(x, y, z);
    return temp;
    
}



// length of the vector
double Vector3::length() {
    double len = 0;
    
    for (int i = 0; i < 3; i++) {
        len += v[i] * v[i];
    }
    
    return sqrt(len);
}


// adds the passed in parameters to the corresponding values
void Vector3::translate(double tx, double ty, double tz) {
    v[0] += tx;
    v[1] += ty;
    v[2] += tz;
}

// resets all coordinates of the vector to 0
void Vector3::reset() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}

// Calculates the values when orbiting is applied
void Vector3::orbit(double angle) {
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    
    double x = v[0];
    double y = v[1];
    
    v[0] = x * cos(angle) + y * -sin(angle);
    v[1] = x * sin(angle) + y * cos(angle);
    v[2] = v[2];
}




// makes length of vector into 1
void Vector3::normalize() {
   	scale(1.0 / length());
}



// print x, y, and z components of the vector after a comment string
void Vector3::print(std::string cmt) {
    std::cout << cmt << std::endl;
    printf("%2.2f, %2.2f, %2.2f \n", v[0], v[1], v[2]);
    
}