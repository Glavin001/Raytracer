#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
    //generate rays for each screen-space coordinate
    virtual Ray generateRay( const Vector2f& point ) = 0;

    virtual float getTMin() const = 0;
    virtual ~Camera(){
    }
protected:
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up, float angle){

    }

    virtual Ray generateRay( const Vector2f& point){

    }

    virtual float getTMin() const {
        return 0.0f;
    }

private:

};


///TODO: Implement Orthographic camera
///Fill in functions and add more fields if necessary
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up, int size){
        this->center = center;
        this->direction = direction.normalized();
        this->up = up.normalized();
        this->size = size;
        // find right/horizontal vector:
        this->horizontal = Vector3f::cross(direction, up);
    }

    virtual Ray generateRay( const Vector2f& point) {
        float hsize = size/2;
        float left = -hsize;
        float right = hsize;
        float top = hsize;
        float bottom = -hsize;
        float u = left+(right-left)*point.x();
        float v = bottom+(top-bottom)*point.y();
        Vector3f origin = center + (v*up) + (u*horizontal);
        return Ray::Ray(origin, this->direction);
    }

    virtual float getTMin() const {
        return -INFINITY;
    }

private:
    int size;

};

#endif //CAMERA_H
