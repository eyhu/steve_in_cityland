#include <math.h>
#include <iostream>
#include "Matrix4.h"

// Constructors
Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
}


Matrix4::Matrix4(double m0, double m1, double m2, double m3,
                 double m4, double m5, double m6, double m7,
                 double m8, double m9, double m10, double m11,
                 double m12, double m13, double m14, double m15){
    m[0][0] = m0;    m[0][1] = m1;    m[0][2] = m2;    m[0][3] = m3;
    m[1][0] = m4;    m[1][1] = m5;    m[1][2] = m6;    m[1][3] = m7;
    m[2][0] = m8;    m[2][1] = m9;    m[2][2] = m10;   m[2][3] = m11;
    m[3][0] = m12;   m[3][1] = m13;   m[3][2] = m14;   m[3][3] = m15;
    
}


// Destructor
Matrix4::~Matrix4() {

}


// Overloaded Operators
// overloads equals
Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}


// overloads multiplication for a Matrix4
/*Matrix4& Matrix4::operator*(const Matrix4& m2) {
    Matrix4* temp = new Matrix4();
    
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            double sum = 0;
            for (int i = 0; i < 4; i++) {
                sum += m[row][i] * m2.m[i][col];
            }
            temp->m[row][col] = sum;
        }
    }
    return *temp;
}*/

// overloads multiplication for a Matrix4
Matrix4 Matrix4::operator*(const Matrix4 m2) {
    Matrix4 temp = Matrix4();
    
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            double sum = 0;
            for (int i = 0; i < 4; i++) {
                sum += m[row][i] * m2.m[i][col];
            }
            temp.m[row][col] = sum;
        }
    }
    return temp;
}


Vector4& Matrix4::mult(const Vector4& v) {
    Vector4 vec = v;
    Vector4* temp = new Vector4(0, 0, 0, 1);
    
    for (int row = 0; row < 4; row++) {
        double sum = 0;
        for (int col = 0; col < 4; col++) {
            sum += m[row][col] * vec.getValue(col);
        }
        
        temp->setValue( row, sum);
    }
    return *temp;
}

// overloads multiplication for a Vector4
Vector4& Matrix4::operator*(const Vector4& v) {
    
    /*Vector4 vec = v;
    Vector4* temp = new Vector4(0, 0, 0, 1);
    
    for (int row = 0; row < 4; row++) {
        double sum = 0;
        for (int col = 0; col < 4; col++) {
            sum += m[row][col] * vec.getValue(col);
        }
        
        temp->setValue( row, sum);
    }
    return *temp;*/
    
    Vector4 vec = v;
    double x = m[0][0] * vec.getValue(0) + m[0][1] * vec.getValue(1) + m[0][2] * vec.getValue(2) + m[0][3] * vec.getValue(3);
    double y = m[1][0] * vec.getValue(0) + m[1][1] * vec.getValue(1) + m[1][2] * vec.getValue(2) + m[1][3] * vec.getValue(3);
    double z = m[2][0] * vec.getValue(0) + m[2][1] * vec.getValue(1) + m[2][2] * vec.getValue(2) + m[2][3] * vec.getValue(3);
    double w = m[3][0] * vec.getValue(0) + m[3][1] * vec.getValue(1) + m[3][2] * vec.getValue(2) + m[3][3] * vec.getValue(3);
    vec.set(x,y,z,w);
    return vec;
}


// Setter
void Matrix4::set(int x, int y, double num) {
    m[x][y] = num;
}


// Getter
double Matrix4::get(int x, int y) const {
    return m[x][y];
}


// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}


// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}


// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}


// Creates a rotation matrix which rotates about the x axis.
// angle is expected in degrees
void Matrix4::makeRotateX(double angle) {
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
    m[1][1] = cos(angle);
    m[2][1] = sin(angle);
    m[1][2] = -sin(angle);
    m[2][2] = cos(angle);
}


// Creates a rotation matrix which rotates about the z axis.
// angle is expected in degrees
void Matrix4::makeRotateZ(double angle) {
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
    m[0][0] = cos(angle);
    m[1][0] = sin(angle);
    m[0][1] = -sin(angle);
    m[1][1] = cos(angle);
}

// Creates a rotation matrix which rotates about an arbitrary axis.
// angle is expected in degrees
void Matrix4::makeRotate(double angle, const Vector3& axis) {
    angle = angle / 180.0 * M_PI;
    
    Vector3 ax = axis;
    
    ax.normalize();
    
    double x = ax.getX();
    double y = ax.getY();
    double z = ax.getZ();
    
    m[0][0] = 1 + (1 - cos(angle)) * (x * x - 1);
    m[0][1] = (-z) * sin(angle) + (1 - cos(angle)) * x * y;
    m[0][2] = y * sin(angle) + (1 - cos(angle))* x * z;
    m[0][3] = 0;
    
    m[1][0] = z * sin(angle) + (1 - cos(angle)) * y * x;
    m[1][1] = 1 + (1 - cos(angle)) * ( y * y - 1);
    m[1][2] = (-x) * sin(angle) + (1 - cos(angle)) * y * z;
    m[1][3] = 0;
    
    m[2][0] = (-y) * sin(angle) + (1 - cos(angle)) * z * x;
    m[2][1] = x * sin(angle) + (1 - cos(angle)) * z * y;
    m[2][2] = 1 + (1 - cos(angle)) * (z * z - 1);
    m[2][3] = 0;
    
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}

// creates a scaling matrix
void Matrix4::makeScale(double sx, double sy, double sz) {
    identity();
    m[0][0] *= sx;
    m[1][1] *= sy;
    m[2][2] *= sz;
}


// creates a translation matrix
void Matrix4::makeTranslate(double tx, double ty, double tz) {
    identity();
    m[0][3] += tx;
    m[1][3] += ty;
    m[2][3] += tz;
}


// prints the matrix
void Matrix4::print(std::string cmt) {
    std::cout << cmt << "\n" << m[0][0] << ", " << m[0][1] << ", " << m[0][2]
    << ", " << m[0][3] << "\n" << m[1][0] << ", " << m[1][1] << ", "
    << m[1][2] << ", " << m[1][3] << "\n" << m[2][0] << ", " << m[2][1]
    << ", " << m[2][2] << ", " << m[2][3] << "\n" << m[3][0] << ", "
    << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << std::endl;
}
