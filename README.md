# OBJ files viewer

## Dependencies
* OpenGL

## Usage
* Define the file you wish to open in `Parser.hpp`. This repo has 3 files to select from in `/resource`.
* Right-click a shape's face to enter `picking mode`. Right clicking more faces would pick them too. The last face must be _left-clicked_ to exit picking mode. This would cause only the selected faces to react to the following commands:
  * Press `t`, then left-click and hold while moving the mouse to translate the object.
  * Press `r`, then left-click and hold while moving the mouse to rotate the object.
  * Press `l`, then left-click and hold while moving the mouse to scale the object.
* Press `g` to enter `global mode`: this would cause the entire object to be affected by actions, thus revoking `picking mode`.
* Press `c` to enter `camera mode`: this would cause the camera itself to rotate.
* Press `s` to enter `self-mode`: this would cause the object's faces to rotate around their center of mass.
* `esc` to exit.

## Example screenshots


![image 1](https://github.com/Bbenchaya/OBJ-Viewer/blob/master/image1.png)



![image 2](https://github.com/Bbenchaya/OBJ-Viewer/blob/master/image1.png)



![image 3](https://github.com/Bbenchaya/OBJ-Viewer/blob/master/image1.png)



## License

The MIT License (MIT)

Copyright (c) 2015 Asaf Chelouche, Ben Ben-Chaya

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
