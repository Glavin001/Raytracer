#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere : public Object3D
{
public:

    Vector3f center;
    float radius;

    Sphere();

    Sphere( Vector3f center, float radius, Material* material );

    ~Sphere();

    virtual bool intersect( const Ray& r, Hit& h, float tmin);

protected:

    Vector2f texCoord(Vector3f p);

};


#endif
