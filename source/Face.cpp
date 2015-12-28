//
//  Face.cpp
//  CG_ex4
//
//  Created by Asaf Chelouche on 15/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "Face.hpp"

Face::Face(vector<pair<Vector3f, Vector3f> > &data){
    this->data = data;
}

pair<Vector3f, Vector3f> Face::getPair(int i){
    return data[i];
}

unsigned int Face::numOfVertices(){
    return data.size();
}