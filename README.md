# Termak 3D

Termak 3D is a small OpenGL/GLUT based game written in C++. The source code
includes basic combat mechanics, map files and simple 3D models.

## Building

You need `g++` and the development packages for `GL`, `GLU` and `GLUT`.
On Debian based systems you can install them with:

```bash
sudo apt-get install g++ freeglut3-dev
```

Compile the project with:

```bash
make termak3d
```

This produces a binary named `termak3d`.

## Running

If all required libraries are available you can start the game with:

```bash
make run
```

## Controls

The following controls are taken from `how to use it.txt`:

1. `a`, `s`, `d`, `z`, `x`, `c` change the camera angle
2. Left mouse button zooms in, right mouse button zooms out
3. `r` resets the camera position
4. Arrow keys move the character
5. When touching an enemy on the field the battle mode begins. Get close and
   press `q` to attack.
6. Most USB gamepads are supported. The left stick mirrors the arrow keys,
   button A attacks and button B resets the camera.

Game maps are found in the `maps/` directory and 3D models are in
`models/`.
