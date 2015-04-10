#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
#include "Ray.h"

///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary

class Transform : public Object3D
{
public:
    Transform(){
    }
    Transform( const Matrix4f& m, Object3D* obj ) : o(obj) {
        this->m = m;
    }
    ~Transform(){
    }
    virtual bool intersect( const Ray& r, Hit& h, float tmin) {

        // get ray-prime = inverse transformed ray
        float epsilon = 0.0001;

        bool* pbIsSingular;
        Matrix4f inv = m.inverse( pbIsSingular, epsilon );

        Vector4f va = Vector4f(r.getOrigin(), 1); // point
        Vector4f vb = Vector4f(r.getDirection(), 0); // vector

        va = inv * va;
        vb = inv * vb;

        Ray ray2 = Ray(va.xyz(), vb.xyz());

        if (o->intersect( ray2, h, tmin)) {

            // Fix normal
            // multiply by transpose of inverse matrix
            Vector3f n = h.getNormal();
            Vector4f newNormal = inv.transposed() * Vector4f(n, 0);
            h.set(h.getT(), h.getMaterial(), newNormal.xyz().normalized());
            return true;
        }
        return false;

    }

protected:
    Object3D* o; //un-transformed object
    Matrix4f m;
};

#endif //TRANSFORM_H
