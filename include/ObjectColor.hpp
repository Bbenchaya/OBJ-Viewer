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
    /*
     * the color channels are defined like so:
     * ambient[0] = R; ambient[1] = G, ambient[2] = B; ambient[3] = alpha
     * and the same goes for diffuse and specular
     */
    float ambient[4];
    float diffuse[4];
    float specular[4];
    
public:
    ObjectColor(int name,
                float *ambient,
                float *diffuse,
                float *specular);
    ObjectColor(const ObjectColor &other);
    ObjectColor& operator=(const ObjectColor &other);
    void printColor();
    float* getAmbient();
    float* getDiffused();
    float* getSpecular();
    void lighten();
    void darken();
    void erase();
    void unerase();
};

#endif /* ObjectColor_hpp */
