#ifndef _GEODE_
#define _GEODE_

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>

#include "Node.h"
#include "Matrix4.h"

using namespace std;

class Geode : public Node {
  protected:
    double size;
    Matrix4 model2world;    // Model view matrix
  
  public:
  
  // Constructors
    Geode();
    Geode(Matrix4);
  
  // Destructor
    virtual ~Geode();
  
  // Setter and Getter
    void setMatrix(Matrix4);
    Matrix4 getModelView();
  
  // Drawing and Rendering
    void draw(Matrix4);
    void draw(Matrix4, bool);
    
    virtual void render(Matrix4) = 0;
};

#endif
