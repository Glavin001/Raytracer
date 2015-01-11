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

std::string parseArgString(std::string argName, std::map<std::string, int> argsMap, int argc, char* argv[])
{

    if ( argsMap.find(argName) == argsMap.end() ) {
        // not found
        std::cout << "Missing `" << argName << "` argument." << endl;
        return "";
    } else {
        // found
        int pos = argsMap.at(argName);
        int strPos = pos+1;
        if (strPos >= argc) {
            // Out of bounds
            std::cout << "Missing <value> of `" << argName << "` <value>` argument." << endl;
            return "";
        } else {
            return argv[strPos];
        }
    }

}


std::pair<int, int> parseArgIntPair(std::string argName, std::map<std::string, int> argsMap, int argc, char* argv[])
{

    if ( argsMap.find(argName) == argsMap.end() ) {
        // not found
        std::cout << "Missing `" << argName << "` argument." << endl;
        return (std::pair<int, int>(0,0));
    } else {
        // found
        int pos = argsMap.at(argName);
        int strPos = pos+1;
        int strPos2 = pos+2;
        if (strPos2 >= argc) {
            // Out of bounds
            std::cout << "Missing <value2> of `" << argName << "` <value1> <value2>` argument." << endl;
            return (std::pair<int, int>(0,0));
        } else {
            char *valStr1 = argv[strPos];
            char *valStr2 = argv[strPos2];
            int val1 = atoi(valStr1);
            int val2 = atoi(valStr2);
            return (std::pair<int, int>(val1,val2));
        }
    }

}

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

    // === Build map of options and their positions ===
    std::map<std::string, int> argsMap;
    // This loop loops over each of the input arguments.
    // argNum is initialized to 1 because the first
    // "argument" provided to the program is actually the
    // name of the executable (in our case, "raytracer").
    for( int argNum = 1; argNum < argc; ++argNum )
    {
        // std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
        std::string arg = argv[argNum];
        if (arg[0] == '-') // Check if it is an argument
        {
            argsMap.insert(std::pair<string, int>(arg, argNum));
        }
    }

    // === Help ===
    if ( argsMap.find("-help") != argsMap.end() || argc == 1) {
        std::cout << help << endl;
        return 0;
    }

    // === Version ===
    if ( argsMap.find("-version") != argsMap.end() ) {
        std::cout << version << endl;
        return 0;
    }

    // === Input ===
    std::string inputFileName = parseArgString("-input", argsMap, argc, argv);
    if (inputFileName.empty()) {
        return 1;
    }
    std::cout << "Input file: " << inputFileName << endl;

    // === Output ===
    std::string outputFileName = parseArgString("-output", argsMap, argc, argv);
    if (outputFileName.empty()) {
        return 1;
    }
    std::cout << "Output file: " << outputFileName << endl;

    std::pair<int, int> size = parseArgIntPair("-size", argsMap, argc, argv);
    int width = size.first;
    int height = size.second;
    if (width > 0 && height > 0) {
        std::cout << "Size (width, height): (" << width << ", " << height << ")" << endl;
    } else {
        std::cout << "Please enter a valid image size (width > 0, height > 0)." << endl;
        return 1;
    }

    // First, parse the scene using SceneParser.
    SceneParser::SceneParser(inputFileName.c_str());

    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.




    ///TODO: below demonstrates how to use the provided Image class
    ///Should be removed when you start
    Vector3f pixelColor (1.0f,0,0);
    //width and height
    Image image( 10, 15 );
    image.SetPixel( 5,5, pixelColor );
    image.SaveImage("demo.bmp");
    return 0;
}
