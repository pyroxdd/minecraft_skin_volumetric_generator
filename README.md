**i use clang mingw64 compiler but gcc or msvc will likely work as well**

## i use:
**cmake --build build**
**.\build\main**

**the only thing you need to change are contents of the call function located in call.cpp**

you can check example call functions in call_examples

the default look of the skin is full black on the inner layer, and trasparent on outer layer

you can change boolean _slim_ to change from default skin or slim skin

## here are some minecraft skin rules:
### inner layer can't have transparency (alpha channel is always 255)
### outer layer has either alpha 0 or alpha 255, if your alpha isn't 0, then its 255
## call function parameters
### color *inner
output (default is black)
### color *outer
output (default is transparent)
### ivec3 world_pos
3D position of this pixel, used for volumetric generation
### ivec2 plane_pos
position of pixel relative to this plane, you can use it alongside plane_size to find out if youre at the edge
### ivec2 plane_size
size of this plane (for example top of head is 8x8)
### DIRECTION dir
direction enum (you can find it in call.h)
### PART part
body part enum (you can find it in call.h)