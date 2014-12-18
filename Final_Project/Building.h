#ifndef __BUILDING__
#define __BUILDING__

#include <stdio.h>
#include <string>

#include "Matrix4.h"
#include "Vector3.h"
#include "Material.h"
#include "Geode.h"

#include "SOIL.h"

class Building {
    protected:
        GLuint textures[10];    // Building Textures
        bool bounding;       // Boolean for Bounding Box
    
    public:
        // CONSTRUCTOR
        Building();
        // DECONSTRUCTOR
        virtual ~Building();
    
        // BOUNDING BOX BOOLEAN RELATED
        void setBound(bool);
        void toggleBound();
        bool isBound();
    
        void loadTexture();
    
        void build(Vector3, Vector3, Vector3, Vector3, double, double, int, int);
        void buildPave(Vector3, Vector3, Vector3, Vector3, double);
        void buildBasic(Vector3, Vector3, Vector3, Vector3, double, double, int);
        void buildBound(Vector3, Vector3, Vector3, Vector3, double, double);
    
        void build01(Vector3, Vector3, Vector3, Vector3, double, double);
        void build02(Vector3, Vector3, Vector3, Vector3, double, double);
        void build03(Vector3, Vector3, Vector3, Vector3, double, double);
        void build04(Vector3, Vector3, Vector3, Vector3, double, double);
    
        
        double fRand(double, double);
        Vector3 calcNorm(Vector3, Vector3, Vector3);
    
};

#endif