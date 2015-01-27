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

#endif //CAMERA_H
