#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane : public Object3D
{
public:

    Vector3f normal;
    float d;

    Plane(){
    }
    /**
       d is the offset from the origin, meaning that the plane equation is P * n = d.
       You can also implement other constructors (e.g. using 3 points).
     */
    Plane( const Vector3f& normal, float d, Material* m) : Object3D(m){
        this->normal = normal;
        this->d = d;
    }
    ~Plane(){
    }
    /*
       Implement intersect, and remember that you also need to update the normal stored by Hit,
       in addition to the intersection distance t and color.
     */
    virtual bool intersect( const Ray& r, Hit& h, float tmin) {
        // Ray: e+t*dr = r.getOrigin() + t * r.getDirection()
        // Plane: P * n = d
        // Intersection: (ray)*n=d = (e+t*dr)*n=d = n*e+n*t*dr=d
        // t = (d-n*e)/(n*dr)
        float t = (d - Vector3f::dot(normal, r.getOrigin()) ) / (Vector3f::dot(normal,r.getDirection()));
        if (t > 0.0f // Positive, has intersection
            && t > tmin // Greater than tmin
            && t < h.getT() // Closest than previous hit.t
            ) {
            h.set(t, material, normal);
            return true;
        }
        return false;
    }

protected:
};
#endif //PLANE_H
