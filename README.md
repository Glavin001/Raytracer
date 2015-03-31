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

#### Render Specific Input Scenes

You can use `render-files` to and `PATTERN={filename pattern}` to
render only certain files at a time.

##### Examples

To render a single file, use full filename and
force the pattern to only match one:

```bash
make render-files PATTERN=test_bunny_1k.txt
```

You can use [Globbing / patterns](http://tldp.org/LDP/abs/html/globbingref.html) to select input files:

```bash
make render-files PATTERN=test_colored_reflective_sphere_shadows_2*
```


## Documentation

Using [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

```bash
make docs
```

## Author

- Glavin Wiechert
