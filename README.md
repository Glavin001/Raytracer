# Raytracer

> Raytracer for CSCI 4471 Computer Graphics class project

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


## Documentation

Using [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

```bash
make docs
```

## Author

- Glavin Wiechert
