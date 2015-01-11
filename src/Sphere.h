#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
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

    Sphere(){
        //unit ball at the center
    }

    Sphere( Vector3f center, float radius, Material* material ) : Object3D(material){
        this->center = center;
        this->radius = radius;
    }


    ~Sphere(){
    }

    virtual bool intersect( const Ray& r, Hit& h, float tmin){

        // geometric solution
        float radius2 = radius * radius;
        Vector3f L = center - r.getOrigin();
        float tca = Vector3f::dot(L, r.getDirection());
        if (tca < 0) return false;
        float d2 = Vector3f::dot(L, L) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        float t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 > h.getT()) return false;
        // else h.t = t0;
        return true;

    }

protected:


};


#endif
