//
//  Face.hpp
//  CG_ex4
//
//  Created by Asaf Chelouche on 15/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp

#include <stdlib.h>
#include <utility>
#include <vector>
#include "Vector3f.h"

using namespace std;

class Face {
private:
    vector<pair<Vector3f, Vector3f> > data;

public:
    Face(vector<pair<Vector3f, Vector3f> > &data);
    pair<Vector3f, Vector3f> getPair(int i);
    unsigned int numOfVertices();
};

#endif /* Face_hpp */
