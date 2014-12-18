#ifndef _MATRIXTRANSFORM_
#define _MATRIXTRANSFORM_


#include <stdio.h>
#include <iostream>
#include <string>

#include "Group.h"
#include "Matrix4.h"

using namespace std;

class MatrixTransform : public Group {
  protected:
    Matrix4 trans;    // Transformation matrix
  
  public:
  // Constructors
    MatrixTransform();
    MatrixTransform(string, Matrix4);
  
  // Desctructor
    virtual ~MatrixTransform();
  
  // Setter and Getter
    void setMatrix(Matrix4);
    Matrix4 getMatrix();
  
  // applies the transformation matrix to the matrix
    void draw(Matrix4);
    void draw(Matrix4, bool);
    
  
};

#endif