//
//  Parser.hpp
//  CG_ex4
//
//  Created by Ben Benchaya on 11/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Face.hpp"
#include "ObjectColor.hpp"
#include "Shape.hpp"
#include "Vector3f.h"

//#define INPUT_FILE "/Users/bbenchaya/Documents/Xcode/CG_ex4/resource/simple.obj"
//#define INPUT_FILE "/Users/bbenchaya/Desktop/Untitled1.obj"
//#define COLOR_TABLE "/Users/bbenchaya/Documents/Xcode/CG_ex4/resource/colorTable.csv"
#define INPUT_FILE "/Users/asafchelouche/programming/CG-ex4/resource/simple.obj"
//#define INPUT_FILE "/Users/asafchelouche/programming/CG-ex4/resource/skeleton.obj"
//#define INPUT_FILE "/Users/asafchelouche/programming/CG-ex4/resource/doll.obj"
#define COLOR_TABLE "/Users/asafchelouche/programming/CG-ex4/resource/colorTable.csv"

using namespace std;

class Parser {
public:
    void parse(vector<ObjectColor> &colors,
               vector<Shape> &shapes,
               unordered_map<int, Vector3f> &vertexTable,
               unordered_map<int, Vector3f> &normalTable);
    
};


#endif /* Parser_hpp */
