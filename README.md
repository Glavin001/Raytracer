# Raytracer

> Raytracer for CSCI 4471 Computer Graphics class project

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

#### Starting Out (5)

- [✓] **Basic classes, main function (5)**
    - [✓] Material
    - [✓] Hit
    - [✓] Ray

#### Electives (22)

Your choice of additional features beyond the specific required ones.


#### Primitives and Modeling (29 required)

- [✓] **Object3D (4 marks)**

Example Scene:
Implementation Notes:

- [✓] **Sphere (6)**

- [✓] **Group (5)**

- [✓] **Plane (2)**

- [✓] **Triangle (2)**

- [✓] **.obj file importer (2)**

- [✓] **Transformations (8)**

- [ ] Constructive Solid Geometry (10)

- [ ] Additional Primitives (3 or more)

- [ ] 3-D Iterated Function System (8)


#### Light Simulation and Illumination (36)

- [✓] **Diffuse shading (5)**

- [✓] **Phong model (5)**

- [✓] **Specular Reflection (10)**

- [✓] **Basic Shadows (6)**

- [✓] **Refraction (10)**

- [ ] Soft Shadows (6)

- [✓] Multiple light sources (4)

- [ ] Spotlights (4)

- [ ] Glossy reflections (7%)

- [ ] Simple Fog (4)

- [ ] Volumetric fog (8)

- [ ] Photon Mapping (15)

#### Camera and Lens Model (11)

- [✓] **Camera (2)**

- [✓] **Orthographic Camera (4)**

- [✓] **Perspective Camera (5)**

- [ ] Bloom (4)

- [ ] Depth-of-field (8)

- [ ] Fisheye appearance (2)

- [ ] Oblique Cameras (2)

- [ ] Other Non-Linear Cameras (4+)

#### Debugging Tools (12)

- [✓] **Depth Visualization (4)**

- [✓] **Back face shading / no shading (4)**

- [✓] **Normal Visualization (4)**

- [ ] OpenGL Previsualization Tool (6)

- [✓] Other Tools (2+)

 I developed https://github.com/Glavin001/RayCapture for the purpose of assisting me with quicker debugging and generating sample input scenes.

#### Textures (10)

- [✓] **Simple Procedural (4)**

- [✓] **Texture Mapping I (6)**

- [ ] Texture Mapping II (up to 6)

- [✓] Environment Mapping (5)
> This could be sphere maps or cube maps.

Raytracer has Cube Map support:

- [ ] Additional texture model loading (4)

- [ ] Bump mapping (6)

#### Acceleration Techniques (0)

- [ ] Adaptive Ray Depth (5)

- [ ] Intersection Methods (4)

- [ ] BSP tree (6)

- [ ] Grid (6)

- [ ] Adaptive bounding boxes or bounding spheres (6)

- [✓] Octree (6)

Raytracer has Octree support for Meshes loaded by .obj files.

- [ ] Some other technique of your choice (6)

#### Distributed Raytracing (0)

- [ ] Antialiasing (3-5)

- [ ] Adaptive Antialiasing (4)

- [ ] Motion Blur (4)

#### Software Engineering (0)

- [✓] Source Code Control (4)

Using Git and GitHub!

- [ ] Parallelizing the Raytracer (5)

