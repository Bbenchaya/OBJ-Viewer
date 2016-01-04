//
//  ObjectColor.cpp
//  CG_ex4
//
//  Created by Ben Benchaya on 14/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "ObjectColor.hpp"

ObjectColor::ObjectColor(int name,
                         float *ambient,
                         float *diffuse,
                         float *specular) {
    this->name = name;
    for (int i = 0; i < 3; i++) {
        this->ambient[i] = ambient[i];
        this->diffuse[i] = diffuse[i];
        this->specular[i] = specular[i];
    }
    this->ambient[3] = 1;
    this->diffuse[3] = 1;
    this->specular[3] = 1;
}

ObjectColor::ObjectColor(const ObjectColor &other) {
    this->name = other.name;
    for (int i = 0; i < 4; i++) {
        this->ambient[i] = other.ambient[i];
        this->diffuse[i] = other.diffuse[i];
        this->specular[i] = other.specular[i];
    }
}

ObjectColor& ObjectColor::operator=(const ObjectColor &other){
    if (this == &other) {
        return *this;
    }
    this->name = other.name;
    for (int i = 0; i < 4; i++) {
        this->ambient[i] = other.ambient[i];
        this->diffuse[i] = other.diffuse[i];
        this->specular[i] = other.specular[i];
    }
    return *this;
}

void ObjectColor::printColor(){
    printf("%d, %f, %f, %f, %f, %f, %f ,%f ,%f ,%f\n", name, ambient[0], ambient[1], ambient[2], diffuse[0], diffuse[1], diffuse[2], specular[0], specular[1], specular[2]);
}

float* ObjectColor::getAmbient(){
    return ambient;
}

float* ObjectColor::getDiffused(){
    return diffuse;
}

float* ObjectColor::getSpecular(){
    return specular;
}

void ObjectColor::lighten(){
    for (int i = 0; i < 3; i++) {
        ambient[i] = fmin(1, ambient[i] * 1.15);
        diffuse[i] = fmin(1, diffuse[i] * 1.15);
        specular[i] = fmin(1, specular[i] * 1.15);
    }
}

void ObjectColor::darken(){
    for (int i = 0; i < 3; i++) {
        ambient[i] = fmin(1, ambient[i] / 1.15);
        diffuse[i] = fmin(1, diffuse[i] / 1.15);
        specular[i] = fmin(1, specular[i] / 1.15);
    }
}

void ObjectColor::erase(){
    ambient[3] = 0;
    diffuse[3] = 0;
    specular[3] = 0;
}

void ObjectColor::unerase(){
    ambient[3] = 1;
    diffuse[3] = 1;
    specular[3] = 1;
}