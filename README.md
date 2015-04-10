# Raytracer

> Raytracer for CSCI 4471 Computer Graphics class project

See [`Features`](#features) section below for a complete feature list.

## Author

- [Glavin Wiechert](https://github.com/Glavin001)


## Downloads

[Pre-Built Binary for Mac (188 KB)](https://github.com/Glavin001/Raytracer/releases/download/v1.0.0/raytracer.o) | [zip of `in/` directory (32.6 MB)](https://github.com/Glavin001/Raytracer/releases/download/v1.0.0/in.zip) | [zip of `out/` directory (4.22 MB)](https://github.com/Glavin001/Raytracer/releases/download/v1.0.0/out.zip) | [zip of `img/` directory (2.79 MB)](https://github.com/Glavin001/Raytracer/releases/download/v1.0.0/img.zip)
--- | --- | --- | ---

**Note:** Some of the required files are ignored by Git to keep the repository's size at a minimum. The complete `in/` directory can be downloaded and swapped in place after downloading this repository. This will allow you to test all of the files, including those with large `.obj` and texture files.

The `out/` directory contains all of the rendered images as `.bmp`.
The `img/` directory contains all of the images converted into `.png`.
You may prefer to download the resulting images in `out/` and `img/`, and skip compiling and running the Raytracer entirely.

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

#### Cleaning Rendered Images

After running `make render` and populating your `out/` directory with images you may wish to clean / delete all of those images.

```bash
make clean-render
```

#### Rendering with a clean build

By default, `make render` will only compile any new / changed files.
To force a `make clean` before building the binary and running the `render` task you can use the `render-clean` task.

```bash
# Exactly like using just `render` task
# Except it runs `clean` task before building
make render-clean
```

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

**In addition to the 103 required marks there were 26 elective marks implemented, totalling to 129 marks out of the 125 marks for 100%**.

Below is the complete list of features and details about each where applicable.

#### Electives (22 required marks)

> Your choice of additional features beyond the specific required ones.

Implemented 26 elective marks:

- Multiple light sources (4 marks)
- Other debugging tools (2 marks)
- Environment Mapping (5 marks)
- Octree (6 marks)
- Antialiasing (5 marks)
- Source Control (4 marks)

#### Starting Out (5 required marks)

Implemented 5 out of 5 required marks.

- [✓] **Basic classes, main function (5 marks)**
    - [✓] Material
    	- See [Material.h](src/Material.h) and [Material.cpp](src/Material.cpp)
    - [✓] Hit
    	- See [Hit.h](src/Hit.h)
    - [✓] Ray
    	- See [Ray.h](src/Ray.h)

#### Primitives and Modeling (29 required marks)

Implemented 29 out of 29 required marks.

- [✓] **Object3D (4 marks)**
	- See [Object3D.h](src/Object3D.h)

- [✓] **Sphere (6 marks)**
	- See [Sphere.h](src/Scene.h) and [Sphere.cpp](src/Scene.cpp)
		
		![scene2_12_rotated_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081345/cb65f854-df16-11e4-8423-57660cc6857b.png)
![scene4_01_sphere_shadow-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081346/cb67c508-df16-11e4-8ef6-6c4690265950.png)

		
- [✓] **Group (5 marks)**
	- See [Group.h](src/Group.h)

- [✓] **Plane (2 marks)**
	- See [Plane.h](src/Plane.h)

	![scene01_plane_normals](https://cloud.githubusercontent.com/assets/1885333/7034666/7cc7edf2-dd58-11e4-8bbc-2ec1506ba66a.png)
![scene01_plane-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034669/7ccc3dbc-dd58-11e4-9f8a-f69d6b92d383.png)


- [✓] **Triangle (2 marks)**
	- See [Triangle.h](src/Triangle.h)
	
![image](https://cloud.githubusercontent.com/assets/1885333/5970409/2673bfa0-a809-11e4-90b7-64c8a72afd3b.png)

![image](https://cloud.githubusercontent.com/assets/1885333/5970407/19de901c-a809-11e4-9c3f-df200d103cc6.png)


- [✓] **.obj file importer (2 marks)**
	- See [Mesh.hpp](src/Mesh.hpp) and [Mesh.cpp](src/Mesh.cpp)

![render](https://lh5.googleusercontent.com/-2RMtHuBmemM/VMefM80W0yI/AAAAAAAAJeM/SvdTFoSqZnU/s320/normal_test_car_1-500x500.bmp)

![scene2_09_bunny_200-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034589/16400240-dd58-11e4-9901-c377d99820fc.png)

![scene2_10_bunny_1k_normals](https://cloud.githubusercontent.com/assets/1885333/7034588/163ee40a-dd58-11e4-9a1e-7f10cc6803fd.png)
![scene2_10_bunny_1k-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034592/164c43e8-dd58-11e4-93a3-f7c43f1710c9.png)

![scene12_vase_normals](https://cloud.githubusercontent.com/assets/1885333/7034607/278586a6-dd58-11e4-9d9b-ab2439f7178f.png)
![scene12_vase-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034605/27853f66-dd58-11e4-8632-b0441be9f35d.png)

![scene13_diamond_normals](https://cloud.githubusercontent.com/assets/1885333/7034606/278554ec-dd58-11e4-9157-88e9053075d8.png)
![scene13_diamond-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034613/27952c8c-dd58-11e4-9c0c-983f0323e8d1.png)

![test_bunny_1k_normals](https://cloud.githubusercontent.com/assets/1885333/7034610/27948714-dd58-11e4-8c03-0660780e2316.png)
![test_bunny_1k-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034618/27a37fda-dd58-11e4-887c-0ad5fd55a9ad.png)


- [✓] **Transformations (8 marks)**
	- See [Transform.h](src/Transform.h)

![scene2_11_squashed_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034358/65d1c196-dd57-11e4-9c57-12e8b9ef527f.png)
![scene2_11_squashed_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034361/65e1788e-dd57-11e4-865e-c5f7b7ac0c60.png)

![scene2_13_rotated_squashed_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034364/65e59e14-dd57-11e4-9c43-5fe357494427.png)
![scene2_13_rotated_squashed_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034366/65ec8fda-dd57-11e4-9c0e-accff881d675.png)

![scene2_14_axes_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034369/65f20550-dd57-11e4-8245-dad39229e706.png)
![scene2_14_axes_cube-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034371/65f84672-dd57-11e4-8dac-ab4dd241fc82.png)

![scene2_15_crazy_transforms_normals](https://cloud.githubusercontent.com/assets/1885333/7034374/65fed8e8-dd57-11e4-89fa-0d6772726238.png)
![scene2_15_crazy_transforms-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034376/6601bafe-dd57-11e4-920f-f51aa96d1064.png)


- [ ] Constructive Solid Geometry (10 marks)

- [ ] Additional Primitives (3 or more marks)

- [ ] 3-D Iterated Function System (8 marks)


#### Light Simulation and Illumination (36 required marks)

Implemented 36 out of 36 required marks and 4 elective marks.

- [✓] **Diffuse shading (5 marks)**
	- See [Material.cpp](src/Material.cpp)

![image](https://cloud.githubusercontent.com/assets/1885333/5970443/727b5b92-a809-11e4-9bed-ca63234f7103.png)


- [✓] **Phong model (5 marks)**
	- See [Material.cpp](src/Material.cpp)

![scene_shininess_variations-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081295/3252f7f2-df16-11e4-9fe0-dfcf2500bb2d.png)


- [✓] **Specular Reflection (10 marks)**
	- See [RayTracer.cpp](src/RayTracer.cpp)

![scene4_03_mirrored_floor_normals](https://cloud.githubusercontent.com/assets/1885333/7081271/0976aaa4-df16-11e4-9214-cc4091b9d61a.png)
![scene4_03_mirrored_floor-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081274/0979eebc-df16-11e4-8a5a-00beda6cf091.png)

![scene4_04_reflective_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7081275/097a215c-df16-11e4-80ae-b6961ed9eff6.png)
![scene4_04_reflective_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081279/098977d8-df16-11e4-9fe9-44a853105ec9.png)

![scene_reflective_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7081574/908e07ae-df1a-11e4-80d2-aa9fe7be0731.png)
![scene_reflective_sphere_bounces_0](https://cloud.githubusercontent.com/assets/1885333/7081570/908cabac-df1a-11e4-9005-a23d5281a2c3.png)
![scene_reflective_sphere_bounces_1](https://cloud.githubusercontent.com/assets/1885333/7081571/908d3f9a-df1a-11e4-95ad-273181498725.png)
![scene_reflective_sphere_bounces_2](https://cloud.githubusercontent.com/assets/1885333/7081575/908e0f6a-df1a-11e4-9506-22ef85325912.png)
![scene_reflective_sphere_bounces_3](https://cloud.githubusercontent.com/assets/1885333/7081572/908d86c6-df1a-11e4-8ca5-684c482bb536.png)
![scene_reflective_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081576/909f075c-df1a-11e4-9518-8d82ef2379c7.png)

![scene_reflective_shininess_variations_normals](https://cloud.githubusercontent.com/assets/1885333/7081284/24b65378-df16-11e4-9218-2e35303ae443.png)
![scene_reflective_shininess_variations-shade_back](https://cloud.githubusercontent.com/assets/1885333/7081287/24b7e832-df16-11e4-9723-e93499c0e7fb.png)
![scene_reflective_shininess_variations-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081286/24b747d8-df16-11e4-95e7-35e01788352d.png)


- [✓] **Basic Shadows (6 marks)**
	- See [RayTracer.cpp](src/RayTracer.cpp)

	![image](https://cloud.githubusercontent.com/assets/1885333/5970451/7a49bd50-a809-11e4-9c9b-db90a5eb4240.png)
![image](https://cloud.githubusercontent.com/assets/1885333/5970452/7b7c3388-a809-11e4-8611-5e0438ea0cfd.png)


- [✓] **Refraction (10 marks)**
	- See [RayTracer.cpp](src/RayTracer.cpp)

		`scene4_06_transparent_bars.txt` |  `scene4_07_transparent_sphere_1.txt`
--- | --- | --- | ---
![scene4_06_transparent_bars-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034433/9a5896d8-dd57-11e4-9f7d-abf04b03402c.png) | ![scene4_07_transparent_sphere_1-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034439/9a69ffae-dd57-11e4-88b8-0ec941c65b55.png) 
`scene4_06_transparent_bars-shadows_shade_back.bmp` | `scene4_07_transparent_sphere_1-shadows_shade_back`

		`scene4_08_transparent_sphere_1.txt` |  `scene4_09_transparent_sphere_2.txt`
--- | --- | --- | ---
![scene4_08_transparent_sphere_1-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034443/9a723868-dd57-11e4-8b67-66b1c72c1450.png) | ![scene4_09_transparent_sphere_2-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034448/9a86ca44-dd57-11e4-9952-0f6309529653.png)
`scene4_08_transparent_sphere_1-shadows_shade_back.bmp` | `scene4_09_transparent_sphere_2-shadows_shade_back.bmp`

- [ ] Soft Shadows (6 marks)

- [✓] Multiple light sources (4 marks)
	- See [RayTracer.cpp](src/RayTracer.cpp)

![scene2_03_colored_lights-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081311/5a480e1e-df16-11e4-935e-4947a8619d86.png)
![scene4_02_colored_shadows-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7081322/68b568b6-df16-11e4-8c8b-73c5c92255c8.png)

- [ ] Spotlights (4 marks)

- [ ] Glossy reflections (7 marks)

- [ ] Simple Fog (4 marks)

- [ ] Volumetric fog (8 marks)

- [ ] Photon Mapping (15 marks)

#### Camera and Lens Model (11 required marks)

Implemented 11 out of 11 required marks.

- [✓] **Camera (2 marks)**
	- See [Camera.h](src/Camera.h)

- [✓] **Orthographic Camera (4 marks)**
	- See [OrthographicCamera.h](src/OrthographicCamera.h)

- [✓] **Perspective Camera (5 marks)**
	- See [PerspectiveCamera.h](src/PerspectiveCamera.h)

- [ ] Bloom (4 marks)

- [ ] Depth-of-field (8 marks)

- [ ] Fisheye appearance (2 marks)

- [ ] Oblique Cameras (2 marks)

- [ ] Other Non-Linear Cameras (4+ marks)

#### Debugging Tools (12 required marks)

Implemented 12 out of 12 required marks and 2 elective marks.

- [✓] **Depth Visualization (4 marks)**
	- See [main.cpp](src/main.cpp)

![scene1_01_depth](https://cloud.githubusercontent.com/assets/1885333/7034694/8f284960-dd58-11e4-8aeb-41e4a6b37a2b.png)
![scene1_02_depth](https://cloud.githubusercontent.com/assets/1885333/7034695/8f298672-dd58-11e4-8ec7-0bc8d4ed539d.png)
![scene1_03_depth](https://cloud.githubusercontent.com/assets/1885333/7034696/8f2a728a-dd58-11e4-880e-646070703c52.png)
![scene1_04_depth](https://cloud.githubusercontent.com/assets/1885333/7034698/8f2b952a-dd58-11e4-9390-8b809c06c0bc.png)
![scene1_05_depth](https://cloud.githubusercontent.com/assets/1885333/7034697/8f2b2342-dd58-11e4-9854-ab4b982310cc.png)
![scene1_06_depth](https://cloud.githubusercontent.com/assets/1885333/7034699/8f2c3d86-dd58-11e4-9de3-23acb77fefa6.png)
![scene1_07_depth](https://cloud.githubusercontent.com/assets/1885333/7034700/8f36409c-dd58-11e4-9ea8-4316ae1ebdc4.png)
![scene2_04_perspective_depth](https://cloud.githubusercontent.com/assets/1885333/7034702/8f379046-dd58-11e4-8a82-6af8e9e22ab0.png)
![scene2_05_depth](https://cloud.githubusercontent.com/assets/1885333/7034703/8f39ab88-dd58-11e4-8488-123edaaf595d.png)
![scene2_06_depth](https://cloud.githubusercontent.com/assets/1885333/7034704/8f3a791e-dd58-11e4-8ded-97f99a783de9.png)
![scene2_07_depth](https://cloud.githubusercontent.com/assets/1885333/7034705/8f3b9b3c-dd58-11e4-99a7-3f0c9ecfe5a9.png)


- [✓] **Back face shading / no shading (4 marks)**
	- See [Material.cpp](src/Material.cpp)

![scene2_07_depth](https://cloud.githubusercontent.com/assets/1885333/7034546/e4eb305c-dd57-11e4-9542-3e9fd270f91c.png)
![scene2_07_sphere_triangles_normals](https://cloud.githubusercontent.com/assets/1885333/7034545/e4eab7ee-dd57-11e4-89a2-fe635149929a.png)
![scene2_07_sphere_triangles-no_back](https://cloud.githubusercontent.com/assets/1885333/7034548/e4edd500-dd57-11e4-834e-01a289217b9a.png)
![scene2_07_sphere_triangles-shade_back](https://cloud.githubusercontent.com/assets/1885333/7034547/e4ed22b8-dd57-11e4-91c3-b677752833d5.png)

![scene2_05_depth](https://cloud.githubusercontent.com/assets/1885333/7034567/fd20a1fc-dd57-11e4-99a6-4138aaa2917d.png)
![scene2_05_inside_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034569/fd220aa6-dd57-11e4-800c-d46f37c7f4dd.png)
![scene2_05_inside_sphere-no_back](https://cloud.githubusercontent.com/assets/1885333/7034568/fd21cdc0-dd57-11e4-83f4-4b45ac07a4ab.png)
![scene2_05_inside_sphere-shade_back](https://cloud.githubusercontent.com/assets/1885333/7034570/fd223404-dd57-11e4-9b0b-4bda46e59282.png)


- [✓] **Normal Visualization (4 marks)**
	- See [main.cpp](src/main.cpp)

![octahedron_2_normals](https://cloud.githubusercontent.com/assets/1885333/7034466/c675fb70-dd57-11e4-8b35-3fae026059c9.png)
![octahedron_normals](https://cloud.githubusercontent.com/assets/1885333/7034471/c67900c2-dd57-11e4-8cd8-10044f82ee06.png)
![scene_reflective_shininess_variations_normals](https://cloud.githubusercontent.com/assets/1885333/7034468/c6770d94-dd57-11e4-802f-a29a45768b7b.png)
![scene_reflective_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034467/c676b8b2-dd57-11e4-87a3-dfdb0c2a06b1.png)
![scene_shininess_variations_normals](https://cloud.githubusercontent.com/assets/1885333/7034469/c6773198-dd57-11e4-9daf-906ef107f79d.png)
![scene1_01_normals](https://cloud.githubusercontent.com/assets/1885333/7034470/c678e9a2-dd57-11e4-9321-0009f4b52481.png)
![scene1_02_normals](https://cloud.githubusercontent.com/assets/1885333/7034477/c6869eda-dd57-11e4-93e1-d7c5cb30b8fb.png)
![scene1_03_normals](https://cloud.githubusercontent.com/assets/1885333/7034475/c684ffb2-dd57-11e4-9022-888a0cd4cb25.png)
![scene1_04_normals](https://cloud.githubusercontent.com/assets/1885333/7034472/c6833f60-dd57-11e4-96ed-8c3c99c9723c.png)
![scene1_05_normals](https://cloud.githubusercontent.com/assets/1885333/7034473/c6846890-dd57-11e4-8634-0ef36ad731fe.png)
![scene1_06_normals](https://cloud.githubusercontent.com/assets/1885333/7034474/c684b908-dd57-11e4-9a68-575d0a812c73.png)
![scene1_07_normals](https://cloud.githubusercontent.com/assets/1885333/7034476/c6860a06-dd57-11e4-9459-f15e0173f8fe.png)
![scene1_08_normals](https://cloud.githubusercontent.com/assets/1885333/7034478/c69061ae-dd57-11e4-9d37-308b23a31424.png)
![scene01_plane_normals](https://cloud.githubusercontent.com/assets/1885333/7034479/c69068de-dd57-11e4-8c06-119115c7b309.png)
![scene2_01_diffuse_normals](https://cloud.githubusercontent.com/assets/1885333/7034482/c694512e-dd57-11e4-9992-5fe918294cb2.png)
![scene2_02_ambient_normals](https://cloud.githubusercontent.com/assets/1885333/7034480/c6917a44-dd57-11e4-9920-6b81c91add5d.png)
![scene2_03_colored_lights_normals](https://cloud.githubusercontent.com/assets/1885333/7034483/c694ada4-dd57-11e4-9ed1-511157770b73.png)
![scene2_04_perspective_normals](https://cloud.githubusercontent.com/assets/1885333/7034481/c692b45e-dd57-11e4-8e7d-6f6312ca970d.png)
![scene2_05_inside_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034484/c69be862-dd57-11e4-936c-90141c508514.png)
![scene2_06_plane_normals](https://cloud.githubusercontent.com/assets/1885333/7034485/c69bfa0a-dd57-11e4-930c-fdf985c6e696.png)
![scene2_07_sphere_triangles_normals](https://cloud.githubusercontent.com/assets/1885333/7034486/c69e5458-dd57-11e4-9cf2-684aa10c0b72.png)
![scene2_08_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034488/c6a2f044-dd57-11e4-83dd-82cf51ac53fe.png)
![scene2_09_bunny_200_normals](https://cloud.githubusercontent.com/assets/1885333/7034487/c6a1e38e-dd57-11e4-98a9-6ef62ee706ac.png)
![scene2_10_bunny_1k_normals](https://cloud.githubusercontent.com/assets/1885333/7034489/c6a4417e-dd57-11e4-84c3-2ec3fe8a5162.png)
![scene2_11_squashed_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034490/c6a7f454-dd57-11e4-9dae-80cd35212ed2.png)
![scene2_12_rotated_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034491/c6aadffc-dd57-11e4-96d5-ecd370f4e623.png)
![scene2_13_rotated_squashed_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034492/c6ab4e88-dd57-11e4-9f6d-c0abc50ecd71.png)
![scene2_14_axes_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034494/c6b03fc4-dd57-11e4-9e6c-118bdd7159f4.png)
![scene2_15_crazy_transforms_normals](https://cloud.githubusercontent.com/assets/1885333/7034493/c6af5960-dd57-11e4-909d-1bb4dca719c1.png)
![scene2_16_t_scale_normals](https://cloud.githubusercontent.com/assets/1885333/7034495/c6b3b3e8-dd57-11e4-8e70-d3c1abe0ce86.png)
![scene02_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034496/c6b43e6c-dd57-11e4-829d-838044d0d83b.png)
![scene4_01_sphere_shadow_normals](https://cloud.githubusercontent.com/assets/1885333/7034497/c6bda614-dd57-11e4-9a98-ceee3507fdd9.png)
![scene4_02_colored_shadows_normals](https://cloud.githubusercontent.com/assets/1885333/7034499/c6c07132-dd57-11e4-9f75-77a7e873ae09.png)
![scene4_03_mirrored_floor_normals](https://cloud.githubusercontent.com/assets/1885333/7034498/c6bf3830-dd57-11e4-8e25-91ab2b513a11.png)
![scene4_04_reflective_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034500/c6c358de-dd57-11e4-9371-1bb5f0fd5205.png)
![scene4_05_transparent_bar_angle_view_normals](https://cloud.githubusercontent.com/assets/1885333/7034501/c6c4dae2-dd57-11e4-8541-eea868a8d877.png)
![scene4_05_transparent_bar_normals](https://cloud.githubusercontent.com/assets/1885333/7034502/c6c577cc-dd57-11e4-9c90-9ac324f6b331.png)
![scene4_06_transparent_bars_normals](https://cloud.githubusercontent.com/assets/1885333/7034503/c6d408f0-dd57-11e4-91de-6137f5c1de0b.png)
![scene4_07_transparent_sphere_1_normals](https://cloud.githubusercontent.com/assets/1885333/7034504/c6d527d0-dd57-11e4-865f-73f88c5e89c0.png)
![scene4_08_transparent_sphere_1_normals](https://cloud.githubusercontent.com/assets/1885333/7034506/c6d7524e-dd57-11e4-8b7a-6e900e5042e6.png)
![scene4_09_transparent_sphere_2_normals](https://cloud.githubusercontent.com/assets/1885333/7034505/c6d72f62-dd57-11e4-8f68-1cbf6b2a548f.png)
![scene4_10_point_light_distance_normals](https://cloud.githubusercontent.com/assets/1885333/7034507/c6d8d830-dd57-11e4-957b-29ab066a0004.png)
![scene4_11_point_light_circle_normals](https://cloud.githubusercontent.com/assets/1885333/7034508/c6da1a10-dd57-11e4-8c1f-6476127b2907.png)
![scene4_12_point_light_circle_d_attenuation_normals](https://cloud.githubusercontent.com/assets/1885333/7034510/c6e00ce0-dd57-11e4-9167-543d9e152d7f.png)
![scene4_13_point_light_circle_d2_attenuation_normals](https://cloud.githubusercontent.com/assets/1885333/7034509/c6dfef12-dd57-11e4-8ade-08c6d5fb1f4c.png)
![scene4_14_faceted_gem_normals](https://cloud.githubusercontent.com/assets/1885333/7034511/c6e4b1e6-dd57-11e4-8f86-3abedd3c17d0.png)
![scene05_bunny_200_normals](https://cloud.githubusercontent.com/assets/1885333/7034512/c6e5fba0-dd57-11e4-9576-9ae8f52d112a.png)
![scene06_bunny_1k_normals](https://cloud.githubusercontent.com/assets/1885333/7034513/c6e7750c-dd57-11e4-9cf5-5b690cc7ac17.png)
![scene10_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034514/c6e815b6-dd57-11e4-8aa6-b563ce83047f.png)
![scene11_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034516/c6ed4284-dd57-11e4-9613-70c37140c5fa.png)
![scene12_vase_normals](https://cloud.githubusercontent.com/assets/1885333/7034515/c6ed4be4-dd57-11e4-8306-f1b1265f8b39.png)
![scene13_diamond_normals](https://cloud.githubusercontent.com/assets/1885333/7034517/c6f1971c-dd57-11e4-92a6-ef207049f7e2.png)
![test_bunny_1k_normals](https://cloud.githubusercontent.com/assets/1885333/7034518/c6f1b670-dd57-11e4-9d2c-ca449fe3b795.png)
![test_colored_reflective_sphere_shadows_2_normals](https://cloud.githubusercontent.com/assets/1885333/7034519/c6f32ab4-dd57-11e4-9626-2afaf27198b9.png)
![test_colored_reflective_sphere_shadows_3_normals](https://cloud.githubusercontent.com/assets/1885333/7034520/c6f5dafc-dd57-11e4-8a30-4fdc95b30ad2.png)
![test_colored_reflective_sphere_shadows_4_normals](https://cloud.githubusercontent.com/assets/1885333/7034522/c6fb9ef6-dd57-11e4-8ab4-2ee99a94eefe.png)
![test_colored_reflective_sphere_shadows_normals](https://cloud.githubusercontent.com/assets/1885333/7034521/c6fb94d8-dd57-11e4-8405-adbd93a127ef.png)
![test_noise_1_normals](https://cloud.githubusercontent.com/assets/1885333/7034523/c70267b8-dd57-11e4-86ac-a2964ce065b0.png)
![test_ortho_cube_normals](https://cloud.githubusercontent.com/assets/1885333/7034525/c70723c0-dd57-11e4-889a-545009615870.png)
![test_ortho_cube_refraction_normals](https://cloud.githubusercontent.com/assets/1885333/7034524/c70564ae-dd57-11e4-929d-f35fc607d227.png)
![test_perspective_1_normals](https://cloud.githubusercontent.com/assets/1885333/7034527/c7096ff4-dd57-11e4-880d-dcf89241e516.png)
![test_plane_1_normals](https://cloud.githubusercontent.com/assets/1885333/7034526/c708480e-dd57-11e4-9f6a-08d6b1414564.png)
![test_refraction_inside_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034528/c7099fce-dd57-11e4-951c-f588099bf277.png)
![test_texture_mapping_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034529/c70f2818-dd57-11e4-980b-db6630a4d56f.png)
![test_transparent_sphere_normals](https://cloud.githubusercontent.com/assets/1885333/7034530/c710ecfc-dd57-11e4-83f0-e5d7581af548.png)
![test_wine_glasses_normals](https://cloud.githubusercontent.com/assets/1885333/7034531/c714d614-dd57-11e4-9a1f-8235422c3f68.png)
![tetrahedron_normals](https://cloud.githubusercontent.com/assets/1885333/7034532/c715ae5e-dd57-11e4-8c61-ee7851f0cbd3.png)


- [ ] OpenGL Previsualization Tool (6 marks)

- [✓] Other Tools (2+ marks)

 - [✓] I developed [RayCapture](https://github.com/Glavin001/RayCapture) for the purpose of assisting me with quicker debugging and generating sample input scenes.
 - [✓] I have used Unit Testing to help me with my debugging. You can run `make test` to see the results. This has helped me in the initial development of this Raytracer for testing Camera's generateRay return values in comparison to the right values calculated "by hand". See [test/unit/](test/unit/) directory for source code of the unit tests.
 - [✓] I developed a `render.sh` script that allows me to pass arguments in to customize which input files are rendered and how they are rendered, size of image, number of ray bounces, etc. See [Rendering Arguments](#rendering-arguments) section above for more details. 

#### Textures (10 required marks)

Implemented 10 out of 10 required marks and 5 elective marks.

- [✓] **Simple Procedural (4 marks)**
	- See [Noise.h](src/Noise.h) and [Noise.cpp](src/Noise.cpp) 
	and [PerlinNoise.h](src/PerlinNoise.h) and [PerlinNoise.cpp](src/PerlinNoise.cpp)

		`scene12_vase.txt` |  `test_noise_1.txt`
--- | --- | ---
![scene12_vase-no_back](https://cloud.githubusercontent.com/assets/1885333/7034295/00a17bcc-dd57-11e4-87f3-864d92024855.png)  | ![test_noise_1-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034300/00aa9f36-dd57-11e4-9c7d-1a9ce8fca952.png)
`scene12_vase-no_back.bmp` | `test_noise_1-shadows_shade_back.bmp`

- [✓] **Texture Mapping I (6 marks)**
	- See [texture.hpp](src/texture.hpp) and [texture.cpp](src/texture.cpp) and [Sphere.cpp](src/Sphere.cpp)

		`test_texture_mapping_sphere.txt` | 
--- | ---
![test_texture_mapping_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034323/23bd2246-dd57-11e4-9c98-4d8724831cc8.png) |  
`test_texture_mapping_sphere-shadows_shade_back.bmp` |

- [ ] Texture Mapping II (up to 6 marks)

- [✓] Environment Mapping (5 marks)
> This could be sphere maps or cube maps.
	- [✓] Cube Map support
  		- See [CubeMap.h](src/CubeMap.h) and [CubeMap.cpp](src/CubeMap.cpp)

		`scene10_sphere.txt` | `scene12_vase.txt`
--- | ---
![scene10_sphere-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034279/ecb7456a-dd56-11e4-9a71-ec6432b491ee.png) | ![scene12_vase-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7034278/ecb4d690-dd56-11e4-99e2-f86c4ba732a9.png)
`scene10_sphere-shadows_shade_back.bmp` | `scene12_vase-shadows_shade_back.bmp`

- [ ] Additional texture model loading (4 marks)

- [ ] Bump mapping (6 marks)

#### Acceleration Techniques (0 required marks)

Implemented 6 elective marks.

- [ ] Adaptive Ray Depth (5 marks)

- [ ] Intersection Methods (4 marks)

- [ ] BSP tree (6 marks)

- [ ] Grid (6 marks)

- [ ] Adaptive bounding boxes or bounding spheres (6 marks)

- [✓] Octree (6 marks)
	- [✓] Raytracer has Octree support for Meshes loaded by .obj files
		- See [octree.hpp](src/octree.hpp) and [octree.cpp](src/octree.cpp) and [Mesh.cpp](src/Mesh.cpp)

- [ ] Some other technique of your choice (6 marks)

#### Distributed Raytracing (0 required marks)

Implemented 5 elective marks.

- [✓] Antialiasing (5)
	- [✓] Jittering method for antialiasing
		- See [main.cpp](src/main.cpp)  

	Normal | Antialiasing with `n=2` | Antialiasing with `n=4`
--- | --- | ---
![scene_reflective_shininess_variations-shadows_shade_back](https://cloud.githubusercontent.com/assets/1885333/7079742/74ccac8a-defe-11e4-8b0a-564481695bd2.png) | ![scene_reflective_shininess_variations-jitter_2](https://cloud.githubusercontent.com/assets/1885333/7079741/74cc105e-defe-11e4-9210-2d8e22ea324c.png) | ![scene_reflective_shininess_variations-jitter_4](https://cloud.githubusercontent.com/assets/1885333/7079743/74cd723c-defe-11e4-963e-52a9df8951e6.png)

- [ ] Adaptive Antialiasing (4 marks)

- [ ] Motion Blur (4 marks)

#### Software Engineering (0 required marks)

Implement 4 elective marks.

- [✓] Source Code Control (4 marks)
	- Using Git and [GitHub](https://github.com/)!

- [ ] Parallelizing the Raytracer (5 marks)

