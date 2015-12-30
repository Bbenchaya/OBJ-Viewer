//
//  Scene.cpp
//  CG_ex4
//
//  Created by Ben Benchaya on 12/12/15.
//  Copyright © 2015 asafch\bbc. All rights reserved.
//

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define DELETE 127
#define BACKSPACE 8
#define ESC 27

#include "Scene.hpp"

bool play;
bool left_button_pressed;
bool middle_button_pressed;
bool right_button_pressed;
bool camera_mode;
bool s_mode;
bool global_mode;
bool picking_mode;
bool erase_mode;
bool rotate_obj;
bool translate_obj;
bool scale_obj;
bool axes;
int old_x;
int old_y;
int rotation_direction;
int rotation_mode;

float degree;
unordered_map<int, Vector3f> vertexTable;
unordered_map<int, Vector3f> normalTable;
vector<Shape> shapes;
vector<ObjectColor> colors;
Camera *camera;
GLfloat shiftMinus100[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -100, 1};
GLfloat shiftPlus100[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 100, 1};
GLfloat *shapeRotation;
Vector3f id = Vector3f(0,0,0);

void printModelviewMatrix(){
    float modelviewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    printf("Modelview matrix: \n");
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4; j++)
            printf("%f ",modelviewMatrix[j * 4 + i]);
        printf("\n");
    }
}

void printProjectionMatrix(){
    float projectionMatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    printf("Projection matrix: \n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            printf("%f ", projectionMatrix[j * 4 + i]);
        printf("\n");
    }
}

void drawAxes(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLineWidth(1.5);
    
    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Vector3f(1,0,0));
    glVertex3fv(Vector3f(50,0,0));  glVertex3fv(Vector3f(-50,0,0));
    glMaterialfv(GL_FRONT, GL_AMBIENT, Vector3f(0,1,0));
    glVertex3fv(Vector3f(0,50,0));  glVertex3fv(Vector3f(0,-50,0));
    glMaterialfv(GL_FRONT, GL_AMBIENT, Vector3f(0,0,1));
    glVertex3fv(Vector3f(0,0,50));  glVertex3fv(Vector3f(0,0,-50));
    glEnd();
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

Vector3f objectCenterOfMass(){
    Vector3f sum(0, 0, 0);
    int numOfVertices = 0;
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
        sum += shape->getSumOfVertices();
        numOfVertices += shape->getNumOfVertices();
    }
    if (numOfVertices == 0) {
        cout << "Bad file: no vertices" << endl;
        exit(1);
    }
    return sum / numOfVertices;
}

void drawPolygon(ObjectColor color, Face &face){
    glMaterialfv(GL_FRONT, GL_AMBIENT, color.getAmbient());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color.getDiffused());
    glMaterialfv(GL_FRONT, GL_SPECULAR, color.getSpecular());
    glMaterialfv(GL_FRONT, GL_ALPHA, color.getAlpha());
    glBegin(GL_POLYGON);
    for (int i = 0; i < face.numOfVertices(); i++) {
        Vector3f normal = face.getPair(i).second;
        glNormal3f(normal.x, normal.y, normal.z);
        Vector3f vertex = face.getPair(i).first;
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
}

void drawObjects(GLenum mode){
    
    //    glAlphaFunc(GL_LESS, 0.5);
    int shape_number = 0;
    glMatrixMode(GL_MODELVIEW);
    
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++, shape_number++) {
        if (picking_mode) {
            glLoadName(shape_number);
        }
        glLoadIdentity();
        if(camera_mode || picking_mode) {
            glMultMatrixf(camera->getRotationMatrix());
            glMultMatrixf(camera->getTranslationMatrix());
            glMultMatrixf(shiftMinus100);
            glMultMatrixf(shape->getRotationMatrix());
            glMultMatrixf(shape->getTranslationMatrix());
        }
        else if (global_mode || s_mode || picking_mode){
            glMultMatrixf(camera->getRotationMatrix());
            glMultMatrixf(camera->getTranslationMatrix());
            glMultMatrixf(shiftMinus100);
            shape->rotate(rotation_direction, degree, rotation_mode);
            glMultMatrixf(shape->getRotationMatrix());
            glMultMatrixf(shape->getTranslationMatrix());
        }
        for (vector<Face>::iterator face = shape->getFaces().begin(); face != shape->getFaces().end(); face++) {
            drawPolygon(shape->getColor(), *face);
        }
        
        if (picking_mode && shape->isPicked()) {
            glDisable(GL_DEPTH_TEST);
            Vector3f com = shape->getSumOfVertices() / shape->getNumOfVertices();
            glTranslatef(com.x, com.y, com.z);
            glMaterialfv(GL_FRONT, GL_AMBIENT, Vector3f(1,0,0));
            glutSolidSphere(1, 50, 50);
            glTranslatef(-com.x, -com.y, -com.z);
            glEnable(GL_DEPTH_TEST);
        }
        drawAxes();
    }
    printModelviewMatrix();
    printProjectionMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawObjects(GL_RENDER);
    glFlush();
}

void initLight(){
    GLfloat light_direction[] = {0, 0, 1};
    GLfloat light_ambient[] = {0.5, 0.5, 0.5};
    GLfloat light_diffuse[] = {0, 0.5, 0.5};
    GLfloat light_specular[] = {0, 0.0, 0.5};
    GLfloat angle[] = {5.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
}

void init(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2, 500);
    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_ALPHA_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    degree = 0;
    play = true;
    left_button_pressed = false;
    middle_button_pressed = false;
    right_button_pressed = false;
    s_mode = false;
    camera_mode = false;
    global_mode = true;
    picking_mode = false;
    erase_mode = false;
    old_x = WINDOW_WIDTH / 2;
    old_y = WINDOW_HEIGHT / 2;
    camera = new Camera();
    shapeRotation = (GLfloat*) malloc(sizeof(GLfloat) * 16);
    glGetFloatv(GL_MODELVIEW, shapeRotation);
    initLight();
}

void list_hits(GLint hits, GLuint *names) {
    int i;
    printf("%d hits:\n", hits);
    for (i = 0; i < hits; i++)
        printf("Number: %d\n"
               "Min Z: %d\n"
               "Max Z: %d\n"
               "Name on stack: %d\n",
               (GLubyte)names[i * 4],
               (GLubyte)names[i * 4 + 1],
               (GLubyte)names[i * 4 + 2],
               (GLubyte)names[i * 4 + 3]
               );
    printf("\n");
}

void processPicks(GLint hits, GLuint *names) {
    for (int i = 0; i < hits; i++)
        shapes.at((GLubyte)names[i * 4 + 3]).pick();
}

void erasePickedObjects() {
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
        shape->unPick();
    }
}

void pick_objects(int x, int y){
    int num_of_objects = shapes.size();
    GLuint buff[num_of_objects];
    GLint hits, view[4];
    glSelectBuffer(64, buff);
    glGetIntegerv(GL_VIEWPORT, view);
    hits = glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(x, y, 1.0, 1.0, view);
    gluPerspective(60, 1.0, 2, 500);
    glMatrixMode(GL_MODELVIEW);
    drawObjects(GL_SELECT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    hits = glRenderMode(GL_RENDER);
    list_hits(hits, buff);
    processPicks(hits, buff);
    if (erase_mode) {
        erasePickedObjects();
    }
    glMatrixMode(GL_MODELVIEW);
}

void unpickAllObjects() {
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
        if (shape->isPicked()) {
            shape->erase();
        }
    }
}

void lightenObjects(){
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
        shape->lighten();
    }
}

void darkenObjects(){
    for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
        shape->darken();
    }
}

void readKey(unsigned char key, int xmouse, int ymouse){
    switch (key){
        case 's':
            unpickAllObjects();
            if (!s_mode) {
                cout << "Entered s mode" << endl;
                lightenObjects();
                display();
            }
            s_mode = true;
            camera_mode = global_mode = picking_mode = false;
            break;
        case 'g':
            unpickAllObjects();
            if (s_mode) {
                darkenObjects();
                display();
            }
            if (!global_mode) {
                cout << "Entered global mode" << endl;
            }
            global_mode = true;
            camera_mode = s_mode = picking_mode = erase_mode = false;
            break;
        case 'c':
            unpickAllObjects();
            if (s_mode) {
                darkenObjects();
                display();
            }
            if (!camera_mode) {
                cout << "Entered camera mode" << endl;
            }
            camera_mode = true;
            global_mode = s_mode = picking_mode = erase_mode = false;
            break;
        case 'r':
            if (picking_mode) {
                rotate_obj = true;
            }
            break;
        case 't':
            if (picking_mode) {
                translate_obj = true;
            }
            break;
        case 'l':
            if (picking_mode) {
                scale_obj = true;
            }
            break;
        case 'e':
            if (picking_mode && !erase_mode) {
                erase_mode = true;
                camera_mode = global_mode = s_mode = false;
                cout << "Entered erase mode" << endl;
            }
            break;
        case '4':
            cout << "RESETTING SCENE" << endl;
            glLoadIdentity();
            for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
                glGetFloatv(GL_MODELVIEW_MATRIX, shape->getTranslationMatrix());
                glGetFloatv(GL_MODELVIEW_MATRIX, shape->getRotationMatrix());
            }
            unpickAllObjects();
            glGetFloatv(GL_MODELVIEW_MATRIX, camera->getTranslationMatrix());
            glGetFloatv(GL_MODELVIEW_MATRIX, camera->getRotationMatrix());
            global_mode = true;
            camera_mode = s_mode = picking_mode = false;
            display();
            break;
        case ESC:
            exit(0);
    }
}

void mouseClick(int button, int state, int x, int y){
    if (state == GLUT_UP)
        printf("Mouse button %d pressed at %d %d\n", button, x, y);
    switch (button) {
        case GLUT_LEFT_BUTTON:
            left_button_pressed = !left_button_pressed;
            old_x = WINDOW_WIDTH / 2;
            old_y = WINDOW_HEIGHT / 2;
            //            if (!left_button_pressed && picking_mode) {
            //                cout << "Exited picking mode, entered global mode" << endl;
            //                picking_mode = false;
            //                camera_mode = s_mode = false;
            //                global_mode = true;
            //                for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
            //                    shape->unPick();
            //                }
            //            }
            break;
        case GLUT_MIDDLE_BUTTON:
            middle_button_pressed = !middle_button_pressed;
            break;
        case GLUT_RIGHT_BUTTON:
            if (!right_button_pressed && picking_mode) {
                pick_objects(x, WINDOW_HEIGHT - y);
            }
            if (!right_button_pressed && !picking_mode) {
                picking_mode = true;
                if (s_mode) {
                    darkenObjects();
                    display();
                }
                camera_mode = global_mode = s_mode = false;
                cout << "Entered picking mode" << endl;
                pick_objects(x, WINDOW_HEIGHT - y);
            }
            right_button_pressed = !right_button_pressed;
    }
}

void mouseMotion(int x, int y){
    if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT || x < 0 || y < 0)
        return;
    if (left_button_pressed) {
        if (camera_mode) { // camera mode
            if (old_x - x > 0){         // rotate the scene from x axis to z axis
                camera->rotate(Z_TO_X, 0.1, SCENE_ROTATION);
                display();
                old_x = x;
            }
            else {                      // rotate the scene from x axis to -z axis
                camera->rotate(X_TO_Z, 0.1, SCENE_ROTATION);
                display();
                old_x = x;
            }
            if (old_y - y > 0){         // rotate the scene from z axis to y axis
                camera->rotate(Z_TO_Y, 0.1, SCENE_ROTATION);
                display();
                old_y = y;
            }
            else {                      // rotate the scene from z axis to -y axis
                camera->rotate(Y_TO_Z, 0.1, SCENE_ROTATION);
                display();
                old_y = y;
            }
        }
        else if (s_mode || global_mode){
            glPushMatrix();
            Vector3f center = objectCenterOfMass();
            GLfloat shiftCenter[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, center.x, center.y, center.z, 1};
            GLfloat shiftBack[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -center.x, -center.y, -center.z, 1};
            if (s_mode) {
                glPushMatrix();
                glLoadMatrixf(camera->getTranslationMatrix());
                glMultMatrixf(shiftCenter);
                glGetFloatv(GL_MODELVIEW_MATRIX, camera->getTranslationMatrix());
                glPopMatrix();
            }
            if (old_x - x > 0){         // rotate the scene from x axis to z axis
                //                camera->rotate(X_TO_Z, 0.1, OBJECT_ROTATION);
                rotation_direction = X_TO_Z;
                rotation_mode = OBJECT_ROTATION;
                degree = 0.1;
                display();
                degree = 0.0;
                old_x = x;
            }
            else {                      // rotate the scene from x axis to -z axis
                //                camera->rotate(Z_TO_X, 0.1, OBJECT_ROTATION);
                rotation_direction = Z_TO_X;
                rotation_mode = OBJECT_ROTATION;
                degree = 0.1;
                display();
                degree = 0.0;
                old_x = x;
            }
            if (old_y - y > 0){         // rotate the scene from z axis to y axis
                //                camera->rotate(Z_TO_Y, 0.1, OBJECT_ROTATION);
                rotation_direction = Y_TO_Z;
                rotation_mode = OBJECT_ROTATION;
                degree = 0.1;
                display();
                degree = 0.0;
                old_y = y;
            }
            else {                      // rotate the scene from z axis to -y axis
                //                camera->rotate(Y_TO_Z, 0.1, OBJECT_ROTATION);
                rotation_direction = Z_TO_Y;
                rotation_mode = OBJECT_ROTATION;
                degree = 0.1;
                display();
                degree = 0.0;
                old_y = y;
            }
            if (s_mode) {
                glPushMatrix();
                glLoadMatrixf(camera->getTranslationMatrix());
                glMultMatrixf(shiftBack);
                glGetFloatv(GL_MODELVIEW_MATRIX, camera->getTranslationMatrix());
                glPopMatrix();
                //                glPushMatrix();
                //                glMultMatrixf(shiftBack);
                //                glPopMatrix();
            }
            glPopMatrix();
        }
    }
    else if (middle_button_pressed && !s_mode){
        if (old_x - x > 0){         // move object left
            camera->translate(LEFT);
            display();
            old_x = x;
        }
        else {                      // move object right
            camera->translate(RIGHT);
            display();
            old_x = x;
        }
        if (old_y - y > 0){         // move object up
            camera->translate(UP);
            display();
            old_y = y;
        }
        else {                      // move object down
            camera->translate(DOWN);
            display();
            old_y = y;
        }
    }
    else if (right_button_pressed){ // right button is pressed
        if (old_y - y > 0){         // zoom in or scale up
            if (camera_mode) {
                camera->translate(NEARER);
            }
            else {                  // s mode\global mode
                for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
                    shape->scale(ENLARGE);
                }
            }
            display();
            old_y = y;
        }
        else {                      // zoom out or scale down
            if (camera_mode) {
                camera->translate(FARTEHR);
            }
            else {                  // s mode\global mode
                for (vector<Shape>::iterator shape = shapes.begin(); shape != shapes.end(); shape++) {
                    shape->scale(SHRINK);
                }
            }
            display();
            old_y = y;
        }
    }
}

int main(int argc, char **argv) {
    Parser parser;
    parser.parse(colors, shapes, vertexTable, normalTable);
    //    for (vector<Shape>::iterator shape_it = shapes.begin() ; shape_it != shapes.end(); ++shape_it){
    //        Shape shp = *shape_it;
    //        shp.printShape();
    //    }
    //    objParser.parseColorTable(colors);
    //        for (vector<ObjectColor>::iterator color_it = colors.begin() ; color_it != colors.end(); ++color_it){
    //            ObjectColor oc = *color_it;
    //            oc.printColor();
    //        }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D object rendering");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(readKey);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
    
}