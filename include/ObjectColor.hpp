//
//  ObjectColor.hpp
//  CG_ex4
//
//  Created by Ben Benchaya on 14/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#ifndef ObjectColor_hpp
#define ObjectColor_hpp

#include <fstream>
#include <iostream>

#include "Vector3f.h"

class ObjectColor {
    
private:
    int name;
    Vector3f ambient;
    Vector3f diffuse;
    Vector3f specular;
    float alpha;
    
public:
    ObjectColor(int name,
                Vector3f ambient,
                Vector3f diffuse,
                Vector3f specular);
    ObjectColor(const ObjectColor &other);
    ObjectColor& operator=(const ObjectColor &other);
    void printColor();
    Vector3f getAmbient();
    Vector3f getDiffused();
    Vector3f getSpecular();
    float getAlpha();
    void lighten();
    void darken();
    void erase();
};

#endif /* ObjectColor_hpp */
