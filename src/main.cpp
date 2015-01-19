#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>
#include <map>

using namespace std;

float clampedDepth ( float depthInput, float depthMin, float depthMax);

#include "bitmap_image.hpp"
#include "ArgParser.h"

int main( int argc, char* argv[] )
{
    // Fill in your implementation here.
    std::string version = "v0.1.0";

    std::string help = "\n"
                       "Raytracer version: " + version + "\n"
                       "\n"
                       "Usage: raytracer [options]\n"
                       "\n"
                       "Options:\n"
                       "\t-help\t\t\toutput usage information\n"
                       "\t-version\t\toutput the version number\n"
                       "\t-input <file>\t\tinput file\n"
                       "\t-output <file>\t\toutput file\n"
                       "\t-size <width> <height>\tsize of rendered image\n"
                       "\t-depth <depth_min> <depth_max> <depth_file>\tdepth\n"
                       "\n"
                       "Examples:\n"
                       "\traytracer -input scene1_01.txt -size 200 200 -output output1_01.tga -depth 9 10 depth1_01.tga\n"
                       "\traytracer -input scene1_02.txt -size 200 200 -output output1_02.tga -depth 8 12 depth1_02.tga\n"
                       "\traytracer -input scene1_03.txt -size 200 200 -output output1_03.tga -depth 8 12 depth1_03.tga\n"
                       "\traytracer -input scene1_04.txt -size 200 200 -output output1_04.tga -depth 12 17 depth1_04.tga\n"
                       "\traytracer -input scene1_05.txt -size 200 200 -output output1_05.tga -depth 14.5 19.5 depth1_05.tga\n"
                       "\traytracer -input scene1_06.txt -size 200 200 -output output1_06.tga -depth 3 7 depth1_06.tga\n"
                       "\traytracer -input scene1_07.txt -size 200 200 -output output1_07.tga -depth -2 2 depth1_07.tga\n"
                       "\n";

    if (argc == 1 || (strcmp(argv[1], "-help") == 0)) {
        // No arguments or `-help`
        // Print help
        std::cout << help << endl;
        return 0;
    }
    else if (argc == 2 && (strcmp(argv[1], "-version") == 0)) {
        // `-version`
        // Print version
        std::cout << version << endl;
        return 0;
    }

    ArgParser args = ArgParser::ArgParser(argc, argv);

    // First, parse the scene using SceneParser.
    SceneParser scene = SceneParser::SceneParser(args.input_file);
    Camera *camera = (Camera *) scene.getCamera();
    Group *group = (Group *) scene.getGroup();

    std::cout << "# of Objects in Group: " << (int) group->getGroupSize() << endl;

    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
    Image image( args.width, args.height );
    float tmin = camera->getTMin();
    for (int x = 0; x < args.width; x++)
    {
        for (int y = 0; y < args.height; y++) {

            Vector2f point ( (x+0.5)/args.width, (y+0.5)/args.height );
            Ray ray = camera->generateRay(point);
            Hit hit = Hit();
            bool doesIntersect = group->intersect(ray, hit, tmin);

            if (doesIntersect) {
                float t = hit.getT();
                // std::cout << "T before: " << t << endl;
                t -= args.depth_min;
                t *= 1/(args.depth_max - args.depth_min);
                t = 1 - t;
                // std::cout << "T after: " << t << endl;
                Vector3f pixelColor (t, t, t);
                // Vector3f pixelColor (1.0f, 0, 0);
                //width and height
                image.SetPixel( x, y, pixelColor );
            }

        }
    }

    // Save image to output file
    image.SaveImage(args.output_file);

    return 0;
}