//
//  BaseObj.cpp
//  CG_ex4
//
//  Created by Asaf Chelouche on 20/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "BaseObj.hpp"

BaseObj::BaseObj(){
    /*
     Set the base object translation and rotation matrices to the identity matrix
     */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                translation[i * 4 +j] = 1;
                rotation[i * 4 + j] = 1;
                autorotation[i * 4 + j] = 1;
            }
            else {
                translation[i * 4 +j] = 0;
                rotation[i * 4 + j] = 0;
                autorotation[i * 4 + j] = 0;
            }
        }
    }
}

GLfloat* BaseObj::getTranslationMatrix(){
    return translation;
}

GLfloat* BaseObj::getRotationMatrix(){
    return rotation;
}

GLfloat* BaseObj::getAutorotationMatrix(){
    return autorotation;
}

void BaseObj::setTranslationMatrix(GLfloat *other){
    for (int i = 0; i < 16; i++) {
        translation[i] = other[i];
    }
}

void BaseObj::setRotationMatrix(GLfloat *other){
    for (int i = 0; i < 16; i++) {
        rotation[i] = other[i];
    }
}

void BaseObj::translateCenter(Vector3f center){
    GLfloat shiftCenter[16] = {1,       0,      0,      0,
        0,       1,      0,      0,
        0,       0,      1,      0,
        center.x, center.y, center.z, 1};
    glPushMatrix();
    glLoadMatrixf(getTranslationMatrix());
    glMultMatrixf(shiftCenter);
    glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
    glPopMatrix();
}

void BaseObj::translate(int direction){
    GLfloat matrix_up[16] = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 5, 0, 1};
    
    GLfloat matrix_down[16] =  {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, -5, 0, 1};
    
    GLfloat matrix_left[16] =  {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -5, 0, 0, 1};
    
    GLfloat matrix_right[16] = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        5, 0, 0, 1};
    
    GLfloat matrix_zoom_out[16] =  {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, -5, 1};
    
    GLfloat matrix_zoom_in[16]   = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 5, 1};
    
    switch (direction) {
        case UP:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_up);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case DOWN:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_down);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case LEFT:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_left);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case RIGHT:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_right);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case FARTEHR:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_zoom_in);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case NEARER:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_zoom_out);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
    }
}

void BaseObj::rotate(int axis, float by_degree, int kind){
    GLfloat object_Y_to_Z[16] = {1,                     0,                          0,                0,
        0,                     cosf(by_degree),            -sinf(by_degree), 0,
        0,                     sinf(by_degree),            cosf(by_degree),  0,
        0,                     0,                          0,                1};
    
    GLfloat object_Z_to_Y[16] = {1,                     0,                          0,                 0,
        0,                     cosf(-by_degree),           -sinf(-by_degree), 0,
        0,                     sinf(-by_degree),           cosf(-by_degree),  0,
        0,                     0,                          0,                 1};
    
    GLfloat object_X_to_Z[16] = {cosf(by_degree),       0,                          sinf(by_degree),   0,
        0,                     1,                          0,                 0,
        -sinf(by_degree),      0,                          cosf(by_degree),   0,
        0,                     0,                          0,                 1};
    
    GLfloat object_Z_to_X[16] = {cosf(-by_degree),      0,                          sinf(-by_degree),  0,
        0,                     1,                          0,                 0,
        -sinf(-by_degree),     0,                          cosf(-by_degree),  0,
        0,                     0,                           0,                1};
    
    GLfloat scene_X_to_Z[16] = {cosf(by_degree),        0,      -sinf(by_degree),       0,
        0,                      1,      0,                      0,
        sinf(by_degree),        0,      cosf(by_degree),        0,
        0,                      0,      0,                      1};
    
    GLfloat scene_Z_to_X[16] = {cosf(-by_degree),       0,      -sinf(-by_degree),      0,
        0,                      1,      0,                      0,
        sinf(-by_degree),       0,      cosf(-by_degree),       0,
        0,                      0,      0,                      1};
    
    GLfloat scene_Y_to_Z[16] = {1,          0,                      0,                      0,
        0,          cosf(by_degree),        sinf(by_degree),        0,
        0,          -sinf(by_degree),       cosf(by_degree),        0,
        0,          0,                      0,                      1};
    
    GLfloat scene_Z_to_Y[16] = {1,      0,                      0,                      0,
        0,      cosf(-by_degree),       sinf(-by_degree),       0,
        0,      -sinf(-by_degree),      cosf(-by_degree),       0,
        0,      0,                      0,                      1};
    
    switch (kind) {
        case OBJECT_ROTATION:
            switch (axis) {
                case Y_TO_Z:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(object_Y_to_Z);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case Z_TO_Y:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(object_Z_to_Y);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case X_TO_Z:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(object_X_to_Z);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case Z_TO_X:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(object_Z_to_X);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
            }
            break;
        case SCENE_ROTATION:
            switch (axis) {
                case Z_TO_Y:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(scene_Z_to_Y);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case Y_TO_Z:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(scene_Y_to_Z);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case X_TO_Z:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(scene_X_to_Z);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
                    break;
                case Z_TO_X:
                    glPushMatrix();
                    glLoadMatrixf(getRotationMatrix());
                    glMultMatrixf(scene_Z_to_X);
                    glGetFloatv(GL_MODELVIEW_MATRIX, getRotationMatrix());
                    glPopMatrix();
            }
    }
}

void BaseObj::autorotate(int axis, float by_degree){
    GLfloat object_Y_to_Z[16] = {1,                     0,                          0,                0,
        0,                     cosf(by_degree),            -sinf(by_degree), 0,
        0,                     sinf(by_degree),            cosf(by_degree),  0,
        0,                     0,                          0,                1};
    
    GLfloat object_Z_to_Y[16] = {1,                     0,                          0,                 0,
        0,                     cosf(-by_degree),           -sinf(-by_degree), 0,
        0,                     sinf(-by_degree),           cosf(-by_degree),  0,
        0,                     0,                          0,                 1};
    
    GLfloat object_X_to_Z[16] = {cosf(by_degree),       0,                          sinf(by_degree),   0,
        0,                     1,                          0,                 0,
        -sinf(by_degree),      0,                          cosf(by_degree),   0,
        0,                     0,                          0,                 1};
    
    GLfloat object_Z_to_X[16] = {cosf(-by_degree),      0,                          sinf(-by_degree),  0,
        0,                     1,                          0,                 0,
        -sinf(-by_degree),     0,                          cosf(-by_degree),  0,
        0,                     0,                           0,                1};
    
    GLfloat scene_X_to_Z[16] = {cosf(by_degree),        0,      -sinf(by_degree),       0,
        0,                      1,      0,                      0,
        sinf(by_degree),        0,      cosf(by_degree),        0,
        0,                      0,      0,                      1};
    
    GLfloat scene_Z_to_X[16] = {cosf(-by_degree),       0,      -sinf(-by_degree),      0,
        0,                      1,      0,                      0,
        sinf(-by_degree),       0,      cosf(-by_degree),       0,
        0,                      0,      0,                      1};
    
    GLfloat scene_Y_to_Z[16] = {1,          0,                      0,                      0,
        0,          cosf(by_degree),        sinf(by_degree),        0,
        0,          -sinf(by_degree),       cosf(by_degree),        0,
        0,          0,                      0,                      1};
    
    GLfloat scene_Z_to_Y[16] = {1,      0,                      0,                      0,
        0,      cosf(-by_degree),       sinf(-by_degree),       0,
        0,      -sinf(-by_degree),      cosf(-by_degree),       0,
        0,      0,                      0,                      1};
    
    switch (axis) {
        case Y_TO_Z:
            glPushMatrix();
            glLoadMatrixf(getAutorotationMatrix());
            glMultMatrixf(object_Y_to_Z);
            glGetFloatv(GL_MODELVIEW_MATRIX, getAutorotationMatrix());
            glPopMatrix();
            break;
        case Z_TO_Y:
            glPushMatrix();
            glLoadMatrixf(getAutorotationMatrix());
            glMultMatrixf(object_Z_to_Y);
            glGetFloatv(GL_MODELVIEW_MATRIX, getAutorotationMatrix());
            glPopMatrix();
            break;
        case X_TO_Z:
            glPushMatrix();
            glLoadMatrixf(getAutorotationMatrix());
            glMultMatrixf(object_X_to_Z);
            glGetFloatv(GL_MODELVIEW_MATRIX, getAutorotationMatrix());
            glPopMatrix();
            break;
        case Z_TO_X:
            glPushMatrix();
            glLoadMatrixf(getAutorotationMatrix());
            glMultMatrixf(object_Z_to_X);
            glGetFloatv(GL_MODELVIEW_MATRIX, getAutorotationMatrix());
            glPopMatrix();
    }
}

void BaseObj::scale(int kind){
    GLfloat matrix_shrink[16] = {0.5, 0,   0,   0,
        0,   0.5, 0,   0,
        0,   0,   0.5, 0,
        0,   0,   0,   1};
    GLfloat matrix_enlarge[16] = {2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1};
    switch (kind) {
        case SHRINK:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_shrink);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
            break;
        case ENLARGE:
            glPushMatrix();
            glLoadMatrixf(getTranslationMatrix());
            glMultMatrixf(matrix_enlarge);
            glGetFloatv(GL_MODELVIEW_MATRIX, getTranslationMatrix());
            glPopMatrix();
    }
}


void BaseObj::pick(){
    is_picked = true;
}

void BaseObj::unPick(){
    is_picked = false;
}

bool BaseObj::isPicked(){
    return is_picked;
}

void BaseObj::reset() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                translation[i * 4 +j] = 1;
                rotation[i * 4 + j] = 1;
                autorotation[i * 4 + j] = 1;
            }
            else {
                translation[i * 4 +j] = 0;
                rotation[i * 4 + j] = 0;
                autorotation[i * 4 + j] = 0;
            }
        }
    }
}