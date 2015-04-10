#include "Sphere.h"

Sphere::Sphere(){
    //unit ball at the center
}


Sphere::Sphere( Vector3f center, float radius, Material* material ) : Object3D(material){
    this->center = center;
    this->radius = radius;
}


Sphere::~Sphere(){
}

bool Sphere::intersect( const Ray& r, Hit& h, float tmin){

    // Precompute variables
    float radius2 = pow(radius, 2);
    Vector3f d = r.getDirection();     // Ray Direction
    Vector3f e = r.getOrigin();
    Vector3f eMinusC = e - center;
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
                    Vector3f p = r.pointAtParameter(pos);
                    Vector3f normal = (2*(p - center)).normalized();
                    h.set(pos, material, normal);
                    h.setTexCoord(texCoord(p));
                }
            }
            // Negative discriminate solution
            if (neg > tmin) {
                // Check if new t is better/closer than old t
                if (neg < h.getT()) {
                    // Closer than current t in hit
                    Vector3f p = r.pointAtParameter(neg);
                    Vector3f normal = (2*(p - center)).normalized();
                    h.set(neg, material, normal);
                    h.setTexCoord(texCoord(p));
                }
            }
            return true;
        }
    }
    // No intersection
    return false;
}

Vector2f Sphere::texCoord(Vector3f p) {
    float theta = acos((p.z() - center.z())/radius);
    float phi = atan2(p.y() - center.y(), p.x() - center.x());
    if (phi < 0) {
        phi = phi + 2 * M_PI;
    }
    float u = phi / (2 * M_PI);
    float v = (M_PI-theta)/M_PI;
    Vector2f tc = Vector2f(u,v);
    // tc.print();
    return tc;
}

