#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle : public Object3D
{
public:
    Triangle();
    ///@param a b c are three vertex positions of the triangle
    Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m){
        hasTex = false;
        this->a = a;
        this->b = b;
        this->c = c;
    }

    virtual bool intersect( const Ray& ray,  Hit& hit, float tmin){

        // Get Vectors
        Vector3f vd = ray.getDirection();
        Vector3f ve = ray.getOrigin();
        Vector3f va = this->a;
        Vector3f vb = this->b;
        Vector3f vc = this->c;
        // Assign vars
        float xa = va.x();
        float xb = vb.x();
        float xc = vc.x();
        float xd = vd.x();
        float xe = ve.x();
        float ya = va.y();
        float yb = vb.y();
        float yc = vc.y();
        float yd = vd.y();
        float ye = ve.y();
        float za = va.z();
        float zb = vb.z();
        float zc = vc.z();
        float zd = vd.z();
        float ze = ve.z();
        // Matrix vars
        float a = xa-xb;
        float b = ya-yb;
        float c = za-zb;
        float d = xa-xc;
        float e = ya-yc;
        float f = za-zc;
        float g = xd;
        float h = yd;
        float i = zd;
        float j = xa-xe;
        float k = ya-ye;
        float l = za-ze;
        // Precomputed vars
        float eiMinusHf = e*i - h*f;
        float M = a*(eiMinusHf)+b*(g*f-d*i)+c*(d*h-e*g);

        // compute t
        float t = -1*(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
        if ((t < tmin) || (t > hit.getT()))
        {
            return false;
        }
        // compute gamma
        float gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
        if ((gamma < 0) || (gamma > 1))
        {
            return false;
        }

        // compute beta
        float beta = (j*(eiMinusHf)+k*(g*f-d*i)+l*(d*h-e*g))/M;
        if ((beta < 0) || (beta > (1 - gamma)))
        {
            return false;
        }

        // Closer than current t in hit
        Vector3f normal = Vector3f::cross(vb-va, vc-va).normalized();
        // std::cout << "Normal: (" << normal[0] << ", " << normal[1] << ", "<< normal[2] << ")" << endl;

        hit.set(t, material, normal);

        return true;

    }
    bool hasTex;
    Vector3f normals[3];
    Vector2f texCoords[3];
    Vector3f a;
    Vector3f b;
    Vector3f c;
protected:

};

#endif //TRIANGLE_H
