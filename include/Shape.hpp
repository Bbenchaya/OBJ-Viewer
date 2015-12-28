//
//  Shape.hpp
//  CG_ex4
//
//  Created by Ben Benchaya on 12/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <vector>

#include "BaseObj.hpp"
#include "Face.hpp"
#include "ObjectColor.hpp"
#include "Vector3f.h"

using namespace std;

class Shape : public BaseObj {
    
private:
    int name;
    vector <Vector3f> vertices;
    vector <Vector3f> normals;
    vector<Face> faces;
    ObjectColor color;
    
public:
    Shape(ObjectColor &color, int name);
    void setVertex(Vector3f vertex);
    void setNormal(Vector3f normal);
    void setFace(Face &face);
    void printShape();
    vector<Face>& getFaces();
    Vector3f getSumOfVertices();
    int getNumOfVertices();
    ObjectColor getColor();
    void lighten();
    void darken();
};


#endif /* Shape_hpp */
