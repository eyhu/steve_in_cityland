#ifndef _LIGHT_
#define _LIGHT_

#include <stdio.h>

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <GLUT/glut.h>


class Light {
  protected:
    
    int num;
    GLenum light;
    
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float position[4];
    float direction[3];
    float exponent;
    float cutOff;
    float cAtten, lAtten, qAtten;
    bool spotLight;

  public:
    
    // Constructor
    Light();
    
    // Deconstructor
    virtual ~Light();
    
    // Three light properties
    void setAmbient(float*);
    void setDiffuse(float*);
    void setSpecular(float*);
    
    void setPosition(float*);
    void setSpotDirection(float*);
    void setSpotExponent(float);
    void setSpotCutoff(float);
    
    void setAtten(float, float, float);
    void setNum(int);
    void setSpotlight(bool);
    
    void turnOn();
    void turnOff();
};

#endif
