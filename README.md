# Raytracer

> Raytracer for CSCI 4471 Computer Graphics class project

See section `Documentation -> Features` below for a complete feature list.

## Author

- [Glavin Wiechert](https://github.com/Glavin001)

## Compiling

Build the executable in `bin/` directory.

```bash
make
```

### Cleaning

```bash
make clean
```

## Usage

After compiling (see above):

```bash
./bin/raytracer.o
```

## Testing

### Unit Testing

```bash
make test
```

### Rendering Sample Scenes

```bash
make render
```

Then look into the `out/` for all of the rendered images.

You can also copy and paste the commands that are printed out for each file render.

For instance, you may see:

```bash
cd in/ ; ../bin/raytracer.o -input test_noise_1.txt -size 200 200 -bounces 4 -output ../out/test_noise_1-no_back.bmp -normals ../out/test_noise_1_normals.bmp ; cd ../
```

You can easily copy and paste this command to re-render
this case for input `test_noise_1.txt` with those arguments.

#### Rendering Arguments

You can change the default arguments for `render` task.

- `PATTERN` - Defaults to `*.txt` - Globbing pattern to select input files from `in/` directory
- `SIZE` - Defaults to `200` - Size of rendered images
- `EXT` - Defaults to `bmp` (`bmp` or `tga` supported) - File extension of rendered images
- `BOUNCES` - Defaults to `4` - # of recursive bounces of a ray, used for reflections
- `SPECIALS` - Defaults to `on` (`on` or `off`) - Render special cases of the input files, such as with depth mapping

##### Examples

To render a single file, use full filename and
force the pattern to only match one:

```bash
make render PATTERN=test_bunny_1k.txt
```

You can use [Globbing / patterns](http://tldp.org/LDP/abs/html/globbingref.html) to select input files:

```bash
make render PATTERN=test_colored_reflective_sphere_shadows_2*
```

You can also change the rendered image size:

```bash
# Render all images with output size of 1000
make render SIZE=1000
# Render specific pattern of images with output size of 1000
make render PATTERN=test_texture_mapping_sphere.txt SIZE=1000
```

You can also disable the special custom rendered images:

```bash
make render SPECIAL=off
```

### Convert `.bmp` to `.png` images

First, install `imagemagick`:

```bash
brew install imagemagick
```

The following will convert the `.bmp` images to `.png` images and move them into the `img/` directory.

```bash
make convert-render
```

You should run this after you're satisfied with your `.bmp` renders.
It will render all of the `.bmp` images it can find in `out/`, and will take some time. Be patient and run only when you're ready.

```bash
make render # Render `.bmp` images to `out/`
make convert-render # Convert `.bmp` to `.png` and move to `img/`
```

## Documentation

### Source Code

Using [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

```bash
make docs
```

### Features

Here is the complete feature list.
**Bolded** list items are require features. 
Features marked with ✓ are implemented, while those without are not.


#### Electives (22 required marks)

> Your choice of additional features beyond the specific required ones.

#### Starting Out (5 required marks)

- [✓] **Basic classes, main function (5 marks)**
    - [✓] Material
    - [✓] Hit
    - [✓] Ray

#### Primitives and Modeling (29 required marks)

- [✓] **Object3D (4 marks)**

Example Scene:
Implementation Notes:

- [✓] **Sphere (6 marks)**

- [✓] **Group (5 marks)**

- [✓] **Plane (2 marks)**

- [✓] **Triangle (2 marks)**

- [✓] **.obj file importer (2 marks)**

- [✓] **Transformations (8 marks)**

- [ ] Constructive Solid Geometry (10 marks)

- [ ] Additional Primitives (3 or more marks)

- [ ] 3-D Iterated Function System (8 marks)


#### Light Simulation and Illumination (36 required marks)

- [✓] **Diffuse shading (5 marks)**

- [✓] **Phong model (5 marks)**

- [✓] **Specular Reflection (10 marks)**

- [✓] **Basic Shadows (6 marks)**

- [✓] **Refraction (10 marks)**

- [ ] Soft Shadows (6 marks)

- [✓] Multiple light sources (4 marks)

- [ ] Spotlights (4 marks)

- [ ] Glossy reflections (7 marks)

- [ ] Simple Fog (4 marks)

- [ ] Volumetric fog (8 marks)

- [ ] Photon Mapping (15 marks)

#### Camera and Lens Model (11 required marks)

- [✓] **Camera (2 marks)**

- [✓] **Orthographic Camera (4 marks)**

- [✓] **Perspective Camera (5 marks)**

- [ ] Bloom (4 marks)

- [ ] Depth-of-field (8 marks)

- [ ] Fisheye appearance (2 marks)

- [ ] Oblique Cameras (2 marks)

- [ ] Other Non-Linear Cameras (4+ marks)

#### Debugging Tools (12 required marks)

- [✓] **Depth Visualization (4 marks)**

- [✓] **Back face shading / no shading (4 marks)**

- [✓] **Normal Visualization (4 marks)**

- [ ] OpenGL Previsualization Tool (6 marks)

- [✓] Other Tools (2+ marks)

 - [✓] I developed [RayCapture](https://github.com/Glavin001/RayCapture) for the purpose of assisting me with quicker debugging and generating sample input scenes.
 - [✓] I have used Unit Tests to help me with my debugging. You can run `make test` to see the results. This has helped me in the initial development of this Raytracer for testing Camera's generateRay return values in comparison to the right values calculated "by hand".

#### Textures (10 required marks)

- [✓] **Simple Procedural (4 marks)**

- [✓] **Texture Mapping I (6 marks)**

- [ ] Texture Mapping II (up to 6 marks)

- [✓] Environment Mapping (5 marks)
> This could be sphere maps or cube maps.

Raytracer has Cube Map support:

- [ ] Additional texture model loading (4 marks)

- [ ] Bump mapping (6 marks)

#### Acceleration Techniques (0 required marks)

- [ ] Adaptive Ray Depth (5 marks)

- [ ] Intersection Methods (4 marks)

- [ ] BSP tree (6 marks)

- [ ] Grid (6 marks)

- [ ] Adaptive bounding boxes or bounding spheres (6 marks)

- [✓] Octree (6 marks)

Raytracer has Octree support for Meshes loaded by .obj files.

- [ ] Some other technique of your choice (6 marks)

#### Distributed Raytracing (0 required marks)

- [ ] Antialiasing (3-5)

- [ ] Adaptive Antialiasing (4 marks)

- [ ] Motion Blur (4 marks)

#### Software Engineering (0 required marks)

- [✓] Source Code Control (4 marks)

Using Git and GitHub!

- [ ] Parallelizing the Raytracer (5 marks)

