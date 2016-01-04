//
//  Shape.cpp
//  CG_ex4
//
//  Created by Ben Benchaya on 12/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "shape.hpp"

Shape::Shape(ObjectColor &color, int name) : color(color){
    this->name = name;
}

void Shape::setVertex(Vector3f vertex){
    vertices.push_back(vertex);
}

void Shape::setNormal(Vector3f normal){
    normals.push_back(normal);
}

void Shape::setFace(Face &face){
    faces.push_back(face);
}

void Shape::printShape(){
    if (name != -1) {
        printf("Shape name is: %d\n", name);
    }
    for (vector<Vector3f>::iterator vertex_it = vertices.begin() ; vertex_it != vertices.end(); ++vertex_it){
        Vector3f vec = *vertex_it;
        float x = vec.x;
        float y = vec.y;
        float z = vec.z;
        printf("vertex: %f, %f, %f\n", x,y,z);
    }
    for (vector<Vector3f>::iterator normals_it = normals.begin() ; normals_it != normals.end(); ++normals_it){
        Vector3f vec = *normals_it;
        float x = vec.x;
        float y = vec.y;
        float z = vec.z;
        printf("normal: %f, %f, %f\n", x,y,z);
    }
    for (vector <Face>::iterator faces_it = faces.begin() ; faces_it != faces.end(); ++faces_it){
        Face fce = *faces_it;
        printf("face: ");
        for (int i = 0; i < fce.numOfVertices(); i++) {
            Vector3f vertex = fce.getPair(i).first;
            Vector3f normal = fce.getPair(i).second;
            //Vertex
            float x1_A1 = vertex.x;
            float y1_B1 = vertex.y;
            float z1_C1 = vertex.z;
            //Normal
            float x1_A2 = normal.x;
            float y1_B2 = normal.y;
            float z1_C2 = normal.z;
            
            printf("<(%f, %f, %f), (%f,%f,%f)> ", x1_A1, y1_B1, z1_C1, x1_A2, y1_B2, z1_C2);
        }
        printf("\n");
    }
}

vector<Face>& Shape::getFaces(){
    return this->faces;
}

Vector3f Shape::getSumOfVertices(){
    Vector3f sum(0, 0, 0);
    for (vector<Vector3f>::iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++) {
        sum += *vertex;
    }
    return sum;
}

int Shape::getNumOfVertices(){
    return vertices.size();
}

ObjectColor Shape::getColor(){
    return this->color;
}

void Shape::lighten(){
    this->color.lighten();
}

void Shape::darken(){
    this->color.darken();
}

void Shape::erase(){
    color.erase();
}

void Shape::unerase(){
    color.unerase();
}