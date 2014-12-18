#ifndef __BOX__
#define __BOX__

#include <stdio.h>
#include <string>

#include "Geode.h"
#include "Vector3.h"

class Box : public Geode {
protected:
    double t;
    Vector3 center;
    
public:
    Box();
    Box(string);
    Box(string, double, Vector3);
    virtual ~Box();
    
    void render();
    void render(Matrix4);
    
    void setCenter(Vector3);
    void setT(double);
    void setMatrix(Matrix4);
    
    Matrix4 getModelView();

    
};

#endif