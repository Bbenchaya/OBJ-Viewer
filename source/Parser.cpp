//
//  Parser.cpp
//  CG_ex4
//
//  Created by Ben Benchaya on 11/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#include "Parser.hpp"

void Parser::parse(vector<ObjectColor> &colors,
                   vector<Shape> &shapes,
                   unordered_map<int, Vector3f> &vertexTable,
                   unordered_map<int, Vector3f> &normalTable){
    FILE *file;
    file = fopen(COLOR_TABLE, "r");
    if (file == NULL){
        cout << "Error: opening input file" << endl;
        exit(1);
    }
    int objectName;
    float ambient[3]; // ambient[0] = R, ambient[1] = G, ambient[2] = B
    float diffuse[3];
    float specular[3];
    while (fscanf(file, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &objectName,
                  ambient,
                  ambient + 1,
                  ambient + 2,
                  diffuse,
                  diffuse + 1,
                  diffuse + 2,
                  specular,
                  specular + 1,
                  specular + 2) != EOF) {
        ObjectColor color = *new ObjectColor(objectName, Vector3f(ambient), Vector3f(diffuse), Vector3f(specular));
        colors.push_back(color);
    }
    fclose(file);
    int numOfShapes = 0;
    int numOfVertices = 1;
    int numOfNormals = 1;
    ifstream input(INPUT_FILE);
    if (!input.good()){
        cout << "Error: opening input file" << endl;
        exit(1);
    }
    for (string line; getline(input, line);) {
        if (line.find("#") != string::npos){            // the line is a comment, ignore it
            continue;
        }
        if (line.find("g ") != string::npos) {
            Shape shape = Shape(colors[numOfShapes], numOfShapes);
            shapes.push_back(shape);
            numOfShapes++;
            continue;
        }
        if (line.find("f ") != string::npos) {          // the line describes a face
            vector<pair<Vector3f, Vector3f> > data;
            size_t found = -1;
            /*
             A face can be composed by an unbound number of vertices, so decompose
             the line vertex-by-vertex.
             */
            while ((found = line.find(" ", found + 1)) != string::npos) {
                size_t until = line.find("/", found + 1);
                if (until == string::npos)
                    break;
                int vertexIndex = stoi(line.substr(found, until - found));
                found = until + 2;
                int normalIndex = stoi(line.substr(found));
                data.push_back(make_pair(vertexTable[vertexIndex], normalTable[normalIndex]));
            }
            Face face(data);
            shapes[numOfShapes - 1].setFace(face);
            continue;
        }
        if (line.find("vn ") != string::npos) {         // the line describes a normal to a vertex
            float normal_x, normal_y, normal_z;
            size_t found = line.find(" ") + 1;
            normal_x = stof(line.substr(found));
            found = line.find(" ", found + 1) + 1;
            normal_y = stof(line.substr(found));
            found = line.find(" ", found + 1) + 1;
            normal_z = stof(line.substr(found));
            Vector3f normal(normal_x, normal_y, normal_z);
            normalTable.emplace(numOfNormals, normal);
            shapes[numOfShapes - 1].setNormal(normalTable[numOfNormals]);
            numOfNormals++;
            continue;
        }
        if (line.find("v ") != string::npos) {          // the line describes a vertex
            /*
             If for some reason the first shape in the file isn't preceded by a 'g' or 'o',
             create it manually.
             */
            if (numOfShapes == 0) {
                Shape shape = Shape(colors[numOfShapes], numOfShapes);
                shapes.push_back(shape);
                numOfShapes++;
            }
            float vertex_x, vertex_y, vertex_z;
            size_t found = line.find(" ") + 1;
            vertex_x = stof(line.substr(found));
            found = line.find(" ", found + 1) + 1;
            vertex_y = stof(line.substr(found));
            found = line.find(" ", found + 1) + 1;
            vertex_z = stof(line.substr(found));
            Vector3f vertex(vertex_x, vertex_y, vertex_z);
            vertexTable.emplace(numOfVertices, vertex);
            shapes[numOfShapes - 1].setVertex(vertexTable[numOfVertices]);
            numOfVertices++;
        }
    }
    input.close();
    
//    file = fopen(INPUT_FILE, "r");
//    if (file == NULL){
//        cout << "Error: opening input file" << endl;
//        exit(1);
//    }
//    while (!feof(file)){
//        char lineHeader;// read the first word of the line
//        int res = fscanf(file, "%c", &lineHeader);
//        if (res == EOF)
//            break; // EOF = End Of File. Quit the loop.
//        if ((lineHeader == 'g') || (lineHeader == 'o')){
//            int res = fscanf(file, "%c", &lineHeader);
//            if (res == EOF)
//                break; // EOF = End Of File. Quit the loop.
//            if (lineHeader == ' ') {
//                Shape shape = Shape(colors[numOfShapes], numOfShapes);
//                shapes.push_back(shape);
//                numOfShapes++;
//                //                cout << "shape created!" << endl;
//            }
//        }
//        if ( lineHeader == 'v' ){
//            int res = fscanf(file, "%c", &lineHeader);
//            if (res == EOF)
//                break; // EOF = End Of File. Quit the loop.
//            if (lineHeader == ' ') {
//                float vertex_x, vertex_y, vertex_z;
//                fscanf(file, "%f %f %f\n", &vertex_x, &vertex_y, &vertex_z );
//                if (numOfShapes < 1) {
//                    printf("You'r format is not accurate\n");
//                    break;
//                }
//                Vector3f vertex = *new Vector3f(vertex_x, vertex_y, vertex_z);
//                vertexTable.emplace(numOfVertices, vertex);
//                shapes[numOfShapes - 1].setVertice(vertexTable[numOfVertices]);
//                numOfVertices++;
//                //                cout << "vertex created!" << endl;
//            }
//            else if ( lineHeader == 'n' ){
//                //            Vector3f normal;
//                float normal_x, normal_y, normal_z;
//                fscanf(file, "%f %f %f\n", &normal_x, &normal_y, &normal_z );
//                if (numOfShapes < 1) {
//                    printf("You'r format is not accurate\n");
//                    break;
//                }
//                Vector3f normal = *new Vector3f(normal_x, normal_y, normal_z);
//                normalTable.emplace(numOfNormals, normal);
//                shapes[numOfShapes - 1].setNormal(normalTable[numOfNormals]);
//                numOfNormals++;
//                //                cout << "normal created!" << endl;
//            }
//        }
//        else if ( lineHeader == 'f' ){
//            int res = fscanf(file, "%c", &lineHeader);
//            if (res == EOF)
//                break; // EOF = End Of File. Quit the loop.
//            if (lineHeader == ' ') {
//                vector<pair<Vector3f, Vector3f> > data;
//                while (lineHeader != '\n') {
//                    unsigned int vertexIndex, normalIndex;
//                    fscanf(file, "%d//%d", &vertexIndex, &normalIndex);
//                    data.push_back(make_pair(vertexTable[vertexIndex], normalTable[normalIndex]));
//                    int res = fscanf(file, "%c", &lineHeader);
//                    if (res == EOF)
//                        break; // EOF = End Of File. Quit the loop.
//                }
//                if (numOfShapes < 1) {
//                    printf("You'r format is not accurate\n");
//                    break;
//                }
//                Face face(data);
//                shapes[numOfShapes - 1].setFace(face);
//                //                cout << "face created!" << endl;
//            }
//        }
//    }
//    fclose(file);
}
