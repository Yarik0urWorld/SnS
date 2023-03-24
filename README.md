# SnS

This is SnS 0.3 made by Yarik0urWorld (Yaroslav Kustov).
It's a game about breaking snowmen with a bow and running away from self-directed green gas.
It has got built-in instructions, so you won't be confused.

The game is opensource!

To compile, go to 'src' directory and run `make`.
It requires headers and shared binaries of following libraries:
 - OpenGL (libGL; apt package "libgl1-mesa-dev")
 - GLUT (libglut; apt package "freeglut3-dev")
 - GLU (libGLU; apt package "libglu1-mesa-dev")

To compile statically (aka release) (only GL, math and X11 libraries are linked dynamically) run `STATIC_BUILD=true make` instead of `make`.
Now it'll require headers and STATIC binaries of all aforementioned libraries (except OpenGL), and:
Shared libraries:
 - X11 (libX11; apt package "libx11-6")
Static libraries:
 - Xi (libXi; apt package "libxi-dev")
 - XFree86 video mode extension (libXxf86vm; apt package "libxxf86vm-dev")
