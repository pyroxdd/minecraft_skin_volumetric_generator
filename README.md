# Minecraft skin volumetric generator

![Direction part](examples/direction_part/3d.png?raw=true)
![Distance](examples/distance/3d.png?raw=true)
![Edges](examples/edges/3d.png?raw=true)
![Noise](examples/noise/3d.png?raw=true)
![Plane cutoff](examples/plane_cutoff/3d.png?raw=true)
![Plane overflow](examples/plane_overflow/3d.png?raw=true)
![Plane overflow 2](examples/plane_overflow_2/3d.png?raw=true)

## what i use
i use clang mingw64 compiler but gcc or msvc will likely work as well

> cmake --build build

> .\build\main

i use this website to view the result, but there's a ton of websites that work\
https://www.minecraftskins.net/skineditor

## info
***the only thing you need to change are contents of the call function located in call.cpp***

you can check example call functions in examples\
the default look of the skin is full black on the inner layer and trasparent on outer layer\
you can change boolean _slim_ to change between default skin and slim skin

## here are some minecraft skin rules:
inner layer can't have transparency (alpha channel is always 255)\
outer layer has either alpha 0 or alpha 255, if your alpha isn't 0, then its 255
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
direction enum (you can find it in helper.h)
### PART part
body part enum (you can find it in helper.h)

## future update ideas (if a single soul likes this project)
input skin or texture, for example to apply filters and add palettes\
lua scripting, compiler won't be needed\
automatically fix, what minecraft would fix (transparency)\
command line interface?

explorable skins: https://www.minecraftskins.com/profile/8398143/pyroxdd
