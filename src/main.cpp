#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "RayTracer.h"
#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>
#include <map>
#include <thread>
//#include <omp.h>

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
                       "\t-normals <file>\t\tnormal visualization file\n"
                       "\t-size <width> <height>\tsize of rendered image\n"
                       "\t-depth <depth_min> <depth_max> <depth_file>\tdepth\n"
                       "\t-jitter <samples> \tantialiasing using jittering method\n"
                       "\t-bounces <bounces> \tnumber of ray bounces off objects\n"
                       "\t-shadows \tenable shadows\n"
                       "\t-shade_back \tenable Back-Face Shading\n"
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

    ArgParser args = ArgParser(argc, argv);

    // First, parse the scene using SceneParser.
    SceneParser scene = SceneParser(args.input_file);
    Camera *camera = (Camera *) scene.getCamera();
    Group *group = (Group *) scene.getGroup();

    RayTracer raytracer = RayTracer(&scene,
                                    args.bounces,
                                    (bool) args.shadows,
                                    (bool) args.shade_back);

    char *outputFile = args.output_file;
    char *depthFile = args.depth_file;
    char *normalsFile = args.normals_file;
    int jitter = args.jitter;

    //std::cout << "# of Objects in Group: " << (int) group->getGroupSize() << endl;

    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
    Image image( args.width, args.height );
    Image depthImage ( args.width, args.height );
    Image normalsImage ( args.width, args.height );

    // unsigned int n = std::thread::hardware_concurrency();
    // std::cout << n << " concurrent threads are supported.\n";

    float tmin = camera->getTMin();
    int x, y = 0;

    //#pragma omp parallel for private(y) shared(image, depthImage, normalsImage, camera, raytracer)
    for (x = 0; x < args.width; x++)
    {
        // std::cout<<"Threads: "<<omp_get_num_threads() <<"."<<endl;

        for (y = 0; y < args.height; y++) {

            // std::cout << "p = ("<< x << ", " << y << ")" << endl;

            float t;
            Vector3f pixelColor;
            Vector3f normal;
            if (jitter < 2) {
                Vector2f point ( (x+0.5)/args.width, (y+0.5)/args.height );
                Ray ray = camera->generateRay(point);
                //std::cout << "(" << ray.getDirection()[0] << ", " << ray.getDirection()[1] << ", "<< ray.getDirection()[2] << ", " << ")" << endl;
                Hit hit = Hit();
                pixelColor = raytracer.traceRay(ray, tmin, 0, 1.0f, hit);
                t = hit.getT();
                normal = hit.getNormal();
            } else {
                // Antialiasing / Super-sampling
                // Using Jittering method
                int n = jitter; // To match the algorithm's notation
                Vector3f c = Vector3f(0,0,0);
                t = 0;
                normal = Vector3f(0,0,0);
                for (int p=0; p<n; p++) {
                    for (int q=0; q<n; q++) {

                        // Unfiform random number in the range 0 to 1
                        float e = ((double) rand() / (double) RAND_MAX);
                        // Hybrid strategy that randomly perturbs a regular grid
                        Vector2f point ( (x+((p+e)/n))/args.width, (y+((q+e)/n))/args.height );
                        Ray ray = camera->generateRay(point);

                        Hit hit = Hit();
                        // Accumulate colour, t, and normal values
                        c += raytracer.traceRay(ray, tmin, 0, 1.0f, hit);
                        t += hit.getT();
                        normal += hit.getNormal();

                    }
                }
                // Divide the accumulated sample values by the number of samples
                float n2 = pow(n, 2); // # of samples
                pixelColor = c / n2;
                t = t / n2;
                normal = normal / n2;

            }

            if (outputFile != NULL) {
                // Ray Caster Image
                image.SetPixel( x, y, pixelColor );
            }

            if (depthFile != NULL) {
                // std::cout << "T before: " << t << endl;
                t -= args.depth_min;
                t *= 1/(args.depth_max - args.depth_min);
                t = 1 - t;
                // std::cout << "T after: " << t << endl;
                Vector3f depthPixelColor (t, t, t);
                depthImage.SetPixel(x, y, depthPixelColor);
            }

            if (normalsFile != NULL) {
                normal = Vector3f (abs(normal.x()), abs(normal.y()), abs(normal.z()));
                // std::cout << "Normal: (" << normal[0] << ", " << normal[1] << ", "<< normal[2] << ", " << ")" << endl;
                normalsImage.SetPixel(x, y, normal);
            }

        }
    }

    // Save image to output file
    if (outputFile != NULL) {
        image.SaveImage(outputFile);
    }
    // Depth file
    if (depthFile != NULL) {
        depthImage.SaveImage(depthFile);
    }
    // Normals file
    if (normalsFile != NULL) {
        normalsImage.SaveImage(normalsFile);
    }

    return 0;
}
