# Lighting demo

This is a simple demo of lighting that i have implemented so far.
An executable is located in the demo-bin folder.
This is compiled for windows and should run on most systems with opengl 3+.

## textures and models:

* https://opengameart.org/content/pietextureset

* https://opengameart.org/content/wood-barrels-pack

# Controls

|    input:   |         action:         |
|:-----------:|:-----------------------:|
|    mouse    |       orbit camera      |
|    w-key    |       move forward      |
|    s-key    |        move back        |
| '[' and ']' | iterate through shaders |

# preview

flat:
![mesh and a color only](color.png)

with texture:
![mesh and a texture only](texture.png)

with lighting:
![mesh, texture, and lighting](t-with-light.png)

with normal maps:
![mesh,texture,light with normal map](t-with-light-and-norm.png)

with specular maps:
![mesh,texture,light with normal and specular map](t-light-norm-spec.png)
