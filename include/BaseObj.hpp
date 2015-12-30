//
//  BaseObj.hpp
//  CG_ex4
//
//  Created by Ben Benchaya on 12/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#ifndef BaseObj_hpp
#define BaseObj_hpp

#include <cmath>
#include "Vector3f.h"
#include <GLUT/GLUT.h>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define FARTEHR 5
#define NEARER 6
#define X_TO_Z 1
#define Z_TO_X 2
#define Z_TO_Y 3
#define Y_TO_Z 4
#define SHRINK 1
#define ENLARGE 2
#define SCENE_ROTATION 1
#define OBJECT_ROTATION 2
#define NEUTRAL_VALUE 0

class BaseObj {
    
private:
    GLfloat translation[16];
    GLfloat rotation[16];
    bool is_picked;
public:
    BaseObj();
    GLfloat* getTranslationMatrix();
    GLfloat* getRotationMatrix();
    void setTranslationMatrix(GLfloat *other);
    void setRotationMatrix(GLfloat *other);
    void translateCenter(Vector3f center);
    void translate(int direction);
    void rotate(int axis, float by_degree, int kind);
    void scale(int kind);
    void pick();
    void unPick();
    bool isPicked();
    void reset();
};

#endif /* BaseObj_hpp */