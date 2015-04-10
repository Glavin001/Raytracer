#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Camera.h"


///TODO: Implement Orthographic camera
///Fill in functions and add more fields if necessary
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float size){
        this->center = center;
        this->size = size;

        this->direction = direction.normalized(); // w
        this->horizontal = Vector3f::cross(this->direction, up).normalized(); // v
        this->up = Vector3f::cross(this->horizontal, this->direction); // u

        // Cache results
        float hsize = size/2.0f;
        left = -hsize;
        right = hsize;
        top = hsize;
        bottom = -hsize;

        // std::cout << "(left, bottom) -> ("<<left<<", "<<bottom<<"), (right, top) -> (" << right << ", " << top << ")" <<endl;

    }

    /**
    u = l + (r − l)(i + 0.5)/nx
    v = b + (t − b)(j + 0.5)/ny
    ray.direction ← −vw
    ray.origin ← ve + u*vu + v*vv
    */
    virtual Ray generateRay( const Vector2f& point) {
        float u = bottom+(top-bottom)*point.y();
        float v = left+(right-left)*point.x();
        Vector3f origin = center + (u*up) + (v*horizontal);
        return Ray(origin, this->direction);
    }

    virtual float getTMin() const {
        return -INFINITY;
    }

private:
    float size;
    float left;
    float right;
    float top;
    float bottom;

};

#endif //ORTHOGRAPHIC_CAMERA_H
