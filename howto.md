## General
size width height
maxdepth depth
output filename

## Camera
camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov

## Geometry
sphere x y z
maxverts number
maxvertnorms number
vertex x y z
vertexnormal x y z nx ny nz
tri v1 v2 v3
trinormal v1 v2 v3

## Transformations
translate x y z
rotate x y z angle
scale x y z
pushTransform
popTransform

## Lights
directional x y z r g b
point x y z r g b
attenuation const linear quadratic
ambient r g b

## Materials
diffuse r g b
specular r g b
shininess s
emission r g b