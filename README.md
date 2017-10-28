## Raytracer: A simple raytracer

#### Authors:
    * Chance Nelson (cbn35@nau.edu)

#### Building
Run `make` for building
Run `make clean` to clean build

#### Usage
* `./raytrace width height config.csv image`

#### Known Issues
*None*

#### Config File Syntax Example
```csv
camera, width: 1, height: 1
sphere, color: [.5, 1.0, 1.0], position: [0, -1, 5], radius: 1
sphere, color: [.5, .5, 2], position: [0, -1, 10], radius: .1
plane, color: [1, 1, 1], position: [0, -1, 0], normal: [0, 1, 0]
sphere, color: [0, 1.0, 0], position: [.5, -1, 10], radius: 3 
plane, color: [.5, 0, 0], position: [0, 0, 10], normal: [0, 0, 1]
sphere, color: [0, 0, 1], position: [-.5, -1, 6], radius: 1
plane, color: [0, .5, 0], position: [-3, 0, 0], normal: [1, 0, 0]
plane, color: [0, .5, 0], position: [3, 0, 0], normal: [1, 0, 0]
plane, color: [1, 1, 1], position: [0, 2, 0], normal: [0, 1, 0]
```
**NOTE**: Config files accept a max of 255 entities
