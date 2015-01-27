#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Camera.h"


///TODO: Implement Orthographic camera
///Fill in functions and add more fields if necessary
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, int size){
        this->center = center;
        this->direction = direction.normalized();
        this->up = up.normalized();
        this->size = size;
        // find right/horizontal vector:
        this->horizontal = Vector3f::cross(direction, up);
    }

    /**
    u = l + (r − l)(i + 0.5)/nx
    v = b + (t − b)(j + 0.5)/ny
    ray.direction ← −vw
    ray.origin ← ve + u*vu + v*vv
    */
    virtual Ray generateRay( const Vector2f& point) {
        float hsize = size/2;
        float left = -hsize;
        float right = hsize;
        float top = hsize;
        float bottom = -hsize;
        float u = bottom+(top-bottom)*point.y();
        float v = left+(right-left)*point.x();
        Vector3f origin = center + (u*up) + (v*horizontal);
        return Ray(origin, this->direction);
    }

    virtual float getTMin() const {
        return -INFINITY;
    }

private:
    int size;

};

#endif //ORTHOGRAPHIC_CAMERA_H
