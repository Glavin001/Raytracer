#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include <vecmath.h>
#include <float.h>
#include "../src/Camera.h"

TEST_CASE("OrthographicCamera can be constructed","[OrthographicCamera]") {

    SECTION("Constructor") {

        Vector3f center (0, 0, 10);
        Vector3f direction (0, 0, 1);
        Vector3f up (0, 1, 0);
        int size = 5;
        Camera *camera = new OrthographicCamera(center, direction, up, size);
        CHECK(true);
        
    }

}
