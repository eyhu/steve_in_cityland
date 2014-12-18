#include <math.h>
#include <iostream>
#include "Vector4.h"


// Constructor
Vector4::Vector4() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    v[3] = 0;
}


Vector4::Vector4(double x, double y, double z, double w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}


// Destructor
Vector4::~Vector4() {

}


// Overloaded Operators
// overloading for addition
Vector4& Vector4::operator+(const Vector4& v2){
    Vector4 *temp;
    for (int i = 0; i < 4; i++) {
      temp->v[i] = temp->v[i] + v2.v[i];
    }
  
  return *temp;
  
}


// overloading for subtraction
Vector4& Vector4::operator-(const Vector4& v2) {
  /*Vector4 *temp;
  for (int i = 0; i < 4; i++) {
    temp->v[i] = temp->v[i] - v2.v[i];
  }
  
  return *temp;*/
    Vector4 retVec = Vector4( v[0] - v2.getValue(0), v[1] - v2.getValue(1),
                             v[2] - v2.getValue(2), v[3] - v2.getValue(3));
    
    return retVec;
}


// getter for vector array
double Vector4::getValue(int i) const {
  	return v[i];
}


// setter for vector array
void Vector4::setValue(int pos, double val) {
    v[pos] = val;
}


// length of the vector
double Vector4::length() {
    double len = 0;
  
    for (int i = 0; i < 3; i++) {
      len += v[i] * v[i];
    }
  
    return sqrt(len);
}


// scales vector so the fourth value equals 1 (ie: x/w; y/w; z/w)
void Vector4::dehomogenize(){
  if( v[3] != 0.0 ) {
    for (int i = 0; i < 4; i++) {
      v[i] = (v[i] / v[3]);
    }
  }
}


// shifts vector
void Vector4::translate(double tx, double ty, double tz){
    v[0] += tx;
    v[1] += ty;
    v[2] += tz;
}


// resets values to 0
void Vector4::reset(){
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}


// prints the elements of the array after a comment
void Vector4::print(std::string cmt){
    std::cout << cmt << "\n" << v[0] << ", " << v[1] << ", " << v[2]
		<< ", " << v[3] << std::endl;
}

// Sets entire vector
void Vector4::set(double x, double y, double z, double w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

double Vector4::get(int i) {
    return v[i];
}