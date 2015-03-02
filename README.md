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

#### Render Specific Scene

You can use `render-file` to and `INPUT={filename pattern}` to
render only certain files at a time.

##### Examples

Omit the extension and it will still match the pattern without extension `.txt`:

```bash
make render-file INPUT=test_colored_reflective_sphere_shadows_2
```

To render a single file, use full filename and
force the pattern to only match one:

```bash
make render-file INPUT=test_bunny_1k.txt
```

## Documentation

Using [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

```bash
make docs
```

## Author

- Glavin Wiechert
