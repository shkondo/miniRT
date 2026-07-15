*This project has been created as part of the 42 curriculum by djspright.*

# miniRT

A minimal **ray tracer** written in C with [MiniLibX](https://github.com/42Paris/minilibx-linux).
It reads a simple `.rt` scene description and renders it from a configurable
camera using ambient + diffuse (Lambert) lighting and hard shadows. The three
mandatory primitives — **plane**, **sphere**, and **cylinder** — are supported,
with correct handling of every intersection (including the inside of objects and
the cylinder caps).

![sample render](docs/sample.png)

## Description

Ray tracing produces an image by shooting one ray per pixel from the camera into
the scene, finding the closest surface each ray hits, and shading that point
according to the lights. This project implements the essential pieces from
scratch:

- a small 3D vector library (dot/cross products, normalization…);
- a pinhole camera with translation, rotation and a horizontal field of view;
- analytic ray/object intersection for planes, spheres and finite cylinders
  (body + the two end caps);
- a lighting model with ambient light, diffuse shading and hard shadows;
- a hand-written parser for the `.rt` scene format with strict validation and
  clean error reporting (`Error\n` + a human-readable message);
- a MiniLibX window that displays the rendered image and closes cleanly on
  `ESC` or the window's close button.

The code targets **both Linux (X11) and macOS (Metal)** from a single source
tree; the `Makefile` selects the right MiniLibX and the platform-specific
details (key codes, teardown) are isolated behind `#ifdef` at file scope.

## Instructions

### Build

```sh
make          # builds the matching MiniLibX, then miniRT
make clean    # remove object files
make fclean   # remove object files and the binary
make re       # fclean + all
```

On **macOS** the bundled `minilibx_mms_20200219` (Metal/Swift) is compiled into
`libmlx.dylib`; on **Linux** the bundled `minilibx-linux` is compiled into
`libmlx.a`. The correct one is chosen automatically from `uname`.

### Run

```sh
./miniRT scenes/all.rt
```

The program takes exactly one argument: a scene file ending in `.rt`.
Ready-made scenes live in `scenes/` (e.g. `sphere.rt`, `plane.rt`,
`cylinder.rt`, `all.rt`, `multi.rt`, `minimal.rt`). Intentionally broken scenes
for testing error handling are under `scenes/bad/`.

Controls:

- `ESC` — close the window and quit cleanly.
- window close button (red cross) — quit cleanly.

### Scene file format (`.rt`)

Each element is on its own line; fields are separated by spaces/tabs; elements
may appear in any order. `A`, `C` and `L` may be declared only once.

| id   | meaning   | format                                                        |
|------|-----------|---------------------------------------------------------------|
| `A`  | ambient   | `A <ratio 0-1> <r,g,b>`                                        |
| `C`  | camera    | `C <x,y,z> <nx,ny,nz> <fov 0-180>`                             |
| `L`  | light     | `L <x,y,z> <ratio 0-1> <r,g,b>`                               |
| `sp` | sphere    | `sp <x,y,z> <diameter> <r,g,b>`                               |
| `pl` | plane     | `pl <x,y,z> <nx,ny,nz> <r,g,b>`                              |
| `cy` | cylinder  | `cy <x,y,z> <ax,ay,az> <diameter> <height> <r,g,b>`         |

Colours are integers in `[0,255]`; coordinates and sizes are floating-point.

## Resources

Classic references used while implementing the maths:

- *Ray Tracing in One Weekend* — Peter Shirley (camera, sphere intersection,
  shading basics).
- *Scratchapixel* — "Ray-Tracing: Generating Camera Rays" and
  "A Minimal Ray-Tracer" (FOV/aspect ratio, ray–plane and ray–cylinder maths).
- The MiniLibX manual pages (`man/`) shipped with the library.
- The 42 *Norm* (v4.1) for the coding standard.

### How AI was used

AI assistance (Claude Code) was used as a pair-programming and reviewing tool:
to scaffold the repetitive, norm-constrained boilerplate (the vector library,
per-object intersection skeletons), to cross-check the cross-platform MiniLibX
build, and to run adversarial reviews for norm compliance, memory safety and
edge cases. Every generated piece was read, verified by rendering reference
scenes, and is fully understood by the author — nothing is included that cannot
be explained during evaluation. The mathematical conventions (camera basis,
normal orientation, shadow bias) were validated visually against rendered
images, not taken on faith.
