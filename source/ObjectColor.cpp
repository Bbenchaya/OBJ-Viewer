//
//  ObjectColor.cpp
//  CG_ex4
//
//  Created by Ben Benchaya on 14/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "ObjectColor.hpp"

ObjectColor::ObjectColor(int name,
                         Vector3f ambient,
                         Vector3f diffuse,
                         Vector3f specular){
    this->name = name;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

ObjectColor::ObjectColor(const ObjectColor &other){
    this->name = other.name;
    this->ambient = other.ambient;
    this->diffuse = other.diffuse;
    this->specular = other.specular;
}

ObjectColor& ObjectColor::operator=(const ObjectColor &other){
    if (this == &other) {
        return *this;
    }
    this->name = other.name;
    this->ambient = other.ambient;
    this->diffuse = other.diffuse;
    this->specular = other.specular;
    return *this;
}

void ObjectColor::printColor(){
    printf("%d, %f, %f, %f, %f, %f, %f ,%f ,%f ,%f\n", name, ambient[0], ambient[1], ambient[2], diffuse[0], diffuse[1], diffuse[2], specular[0], specular[1], specular[2]);
}

Vector3f ObjectColor::getAmbient(){
    return this->ambient;
}

Vector3f ObjectColor::getDiffused(){
    return this->diffuse;
}

Vector3f ObjectColor::getSpecular(){
    return this->specular;
}

void ObjectColor::lighten(){
    this->ambient *= 1.15;
    this->diffuse *= 1.15;
    this->specular *= 1.15;
}

void ObjectColor::darken(){
    this->ambient /= 1.15;
    this->diffuse /= 1.15;
    this->specular /= 1.15;
}