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

        // Precompute variables
        float radius2 = pow(radius, 2);
        Vector3f d = r.getDirection(); // Ray Direction
        Vector3f eMinusC = r.getOrigin() - center;
        float dTimesD = Vector3f::dot(d, d);
        // Calculate the discriminate
        float discriminate = (
            pow(
                Vector3f::dot(
                    r.getDirection(),
                    eMinusC
                    )
                , 2
                )
            -
            (
                dTimesD * (
                    Vector3f::dot(eMinusC, eMinusC)
                    - radius2
                    )
            )
            );

        // Check for possible intersection
        // If discriminate is negative then there is no intersection
        // and it is not necessary to continue calculations
        if (discriminate >= 0)
        {
            float sqrtDiscr = sqrt(discriminate);
            // Complete Quadratic Equation calculation
            // Get Left-Hand-Side
            float lhs = -1*Vector3f::dot(d, eMinusC);
            // Calculate for positive and negative discriminate
            float pos = (lhs + sqrtDiscr) / dTimesD;
            float neg = (lhs - sqrtDiscr) / dTimesD;
            // Check if either positive or negative discriminate solutions
            // are greater than tmin
            if (pos > tmin || neg > tmin) {
                // Positive discriminate solution
                if (pos > tmin )
                {
                    // Check if new t is better/closer than old t
                    if (pos < h.getT())
                    {
                        // Closer than current t in hit
                        Vector3f normal (0.0, 0, 0);
                        h.set(pos, material, normal);
                    }
                }
                // Negative discriminate solution
                if (neg > tmin) {
                    // Check if new t is better/closer than old t
                    if (neg < h.getT()) {
                        // Closer than current t in hit
                        Vector3f normal (0.0, 0, 0);
                        h.set(neg, material, normal);
                    }
                }
                return true;
            }
        }
        // No intersection
        return false;
    }

protected:


};


#endif
