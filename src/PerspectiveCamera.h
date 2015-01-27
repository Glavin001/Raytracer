#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle){
        this->center = center;
        this->direction = direction.normalized();
        this->up = up.normalized();
        this->angle = angle;
        this->horizontal = Vector3f::cross(direction, up);
    }

    /**
    Generate a Ray given this pixel point and Camera

    @params point   x = (i + 0.5)/nx, y = (j + 0.5)/ny
    @return ray     new Ray

    ```
    u = l + (r − l)(i + 0.5)/nx
    v = b + (t − b)(j + 0.5)/ny
    ray.direction ← −d*vw + u*vu + v*vv
    ray.origin ← ve
    ```

    */
    virtual Ray generateRay( const Vector2f& point) {

        // std::cout << endl;
        // std::cout << "pt: (" << point.x() << ", " << point.y() << ")" << endl;

        /*
        Notes:
            tanf(theta) = (opp/adj);
            d = adj = opp / tanf(theta)
            opp = 1.0f
        */
        float halfAngle = angle / 2.0f;
        float hsize = tanf(halfAngle);
        float d = 1.0f;
        float left = -hsize;
        float right = hsize;
        float top = hsize;
        float bottom = -hsize;
        float u = left+(right-left)*point.x();
        float v = bottom+(top-bottom)*point.y();

        // direction = -d*vw+u*vu+v*vv
        // std::cout << "hsize: " << hsize << ", u: "<< u << ", v: " << v << ", d: " << d << endl;
        Vector3f dir = (d*direction) + (u*up) + (v*horizontal);
        // std::cout << "dir = (" << dir[0] << ", " << dir[1] << ", "<< dir[2] << ", " << ")" << endl;

        return Ray(center, dir);
    }

    virtual float getTMin() const {
        return 0.0f;
    }

private:
    float angle;
};

#endif //PERSPECTIVE_CAMERA_H
