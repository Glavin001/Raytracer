#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include <vecmath.h>
#include <float.h>
#include "../src/Camera.h"
#include "../src/OrthographicCamera.h"

TEST_CASE("OrthographicCamera - constructor","[OrthographicCamera]") {

    SECTION("should construct successfully") {

        Vector3f center (0, 0, 10);
        Vector3f direction (0, 0, 1);
        Vector3f up (0, 1, 0);
        int size = 5;
        Camera *camera = new OrthographicCamera(center, direction, up, size);
        CHECK(true);

    }

    SECTION("Direction") {
        Vector3f center (0, 0, 10);
        Vector3f direction (0, 0, 1);
        Vector3f up (0, 1, 0);
        int size = 5;

        Camera *camera = new OrthographicCamera(center, direction, up, size);

        CHECK(true);

    }

}

TEST_CASE("OrthographicCamera - generateRay","[OrthographicCamera]") {

    SECTION("should generate ray from center") {

        Vector3f center (0, 0, 10);
        Vector3f direction (0, 0, -1);
        Vector3f up (0, 1, 0);
        int size = 5;
        Camera *camera = new OrthographicCamera(center, direction, up, size);
        CHECK(true);

        Vector2f point ( 0.5, 0.5 ); // Middle
        Ray ray = camera->generateRay(point);

        std::cout << "ray origin : (" << ray.getOrigin()[0] << ", " << ray.getOrigin()[1] << ", "<< ray.getOrigin()[2] << ")" << endl;
        std::cout << "ray direction : (" << ray.getDirection()[0] << ", " << ray.getDirection()[1] << ", "<< ray.getDirection()[2] << ")" << endl;

        Vector3f origin = ray.getOrigin();
        Vector3f dir = ray.getDirection();
        
        CHECK(dir.x() == direction.x());
        CHECK(dir.y() == direction.y());
        CHECK(dir.z() == direction.z());

        CHECK(origin.x() == 0.0f);
        CHECK(origin.y() == 0.0f);
        CHECK(origin.z() == 10.0f);

    }

    SECTION("should generate ray from bottom left corner") {

        Vector3f center (0, 0, 10);
        Vector3f direction (0, 0, -1);
        Vector3f up (0, 1, 0);
        int size = 5;
        Camera *camera = new OrthographicCamera(center, direction, up, size);
        CHECK(true);

        Vector2f point ( 0, 0 ); // Middle
        Ray ray = camera->generateRay(point);

        std::cout << "ray origin : (" << ray.getOrigin()[0] << ", " << ray.getOrigin()[1] << ", "<< ray.getOrigin()[2] << ")" << endl;
        std::cout << "ray direction : (" << ray.getDirection()[0] << ", " << ray.getDirection()[1] << ", "<< ray.getDirection()[2] << ")" << endl;

        Vector3f origin = ray.getOrigin();
        Vector3f dir = ray.getDirection();

        CHECK(dir.x() == direction.x());
        CHECK(dir.y() == direction.y());
        CHECK(dir.z() == direction.z());

        CHECK(origin.x() == -2.5f);
        CHECK(origin.y() == -2.5f);
        CHECK(origin.z() == 10.0f);


    }


}
