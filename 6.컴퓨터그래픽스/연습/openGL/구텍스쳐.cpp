//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//#include <GL/glut.h>
//
///**
// * \file
// * An application that displays a rotating sphere with a
// * texture-mapped image.
// *
// * On Linux, compile with:
// *   g++ -o sphere -Wall sphere.c -lglut -lGL -lGLU
// *
// * @author  Prof. David Bernstein, James Madison University
// */
//static GLfloat angle[] = { 0.0, 0.0, 0.0 };
//static GLint axis = 1;
//static GLint delay = 20;
//
////[name
//static GLuint textureName;
//
////]name
//
///**
// * Update the content.
// */
//void update() {
//    // Update the rotation angle (for the current axis
//    // of rotation)
//    angle[axis] += 2.0;
//
//    if (angle[axis] > 360.0)
//        angle[axis] -= 360.0;
//
//    // Make the modelview matrix current
//    glMatrixMode(GL_MODELVIEW);
//
//    // Clear the modelview matrix
//    glLoadIdentity();
//
//    // Concatenate the three rotations
//    glRotatef(angle[0], 1.0, 0.0, 0.0);
//    glRotatef(angle[1], 0.0, 1.0, 0.0);
//    glRotatef(angle[2], 0.0, 0.0, 1.0);
//}
//
///**
// * The mouse callback (i.e., the function that is called
// * each time a mouse button is pressed or released).
// *
// * @param button The button (e.g., GLUT_LEFT_BUTTON)
// * @param state  The state (e.g., GLUT_UP or GLUT_DOWN)
// * @param x      The x-position of the mouse
// * @param y      The y-position of the mouse
// */
//void mouseClicked(int button, int state, int x, int y) {
//    if (state == GLUT_DOWN) {
//        if (button == GLUT_LEFT_BUTTON)
//            axis = 0;
//        else if (button == GLUT_MIDDLE_BUTTON)
//            axis = 1;
//        else if (button == GLUT_RIGHT_BUTTON)
//            axis = 2;
//    }
//}
//
////[display
///**
// * The display callback.
// */
//void display() {
//    // Clear the screen
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Select the texture object
//    glBindTexture(GL_TEXTURE_2D, textureName);
//
//    // Create the sphere
//    glPushMatrix();
//    glRotatef(90.0, 1.0, 0.0, 0.0);
//
//    GLUquadric* quadric = gluNewQuadric();
//    gluQuadricDrawStyle(quadric, GLU_FILL);
//    gluQuadricNormals(quadric, GLU_SMOOTH);
//    gluQuadricTexture(quadric, GL_TRUE);
//    gluSphere(quadric, 1.0, 20, 20);
//    gluDeleteQuadric(quadric);
//    glPopMatrix();
//
//    // Force the rendering (off-screen)
//    glFlush();
//
//    // Handle the double buffering
//    glutSwapBuffers();
//}
////]display
//
///**
// * The reshape callback (i.e., the function that is called
// * each time the window is re-sized).
// *
// * @param width   The new width
// * @param height  The new height
// */
//void reshape(int width, int height) {
//    GLfloat aspect;
//
//    // Set the viewport
//    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
//
//    // Make the projection matrix current
//    glMatrixMode(GL_PROJECTION);
//
//    // Clear the projection matrix
//    glLoadIdentity();
//
//    // Set the projection matrix (based on the aspect ratio)
//    if (width <= height) {
//        aspect = (GLfloat)height / (GLfloat)width;
//        glOrtho(-2.0, 2.0, -2.0 * aspect, 2.0 * aspect, -10.0, 10.0);
//    }
//    else {
//        aspect = (GLfloat)width / (GLfloat)height;
//        glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, -10.0, 10.0);
//    }
//
//}
//
///**
// * The timer callback.
// */
//void timer(int value) {
//    // Update the content
//    update();
//
//    // Request a callback to the DisplayFunc
//    glutPostRedisplay();
//
//    // Re-start the timer
//    glutTimerFunc(delay, timer, 0);
//}
//
///**
// * Fill the given matrix with a RAW image.
// *
// * @param data          The matrix to fill
// */
//void readRAWImage(char* filename, GLbyte data[512][256][3]) {
//    FILE* file;
//
//    file = fopen(filename, "rb");
//    if (file != NULL) {
//        fread(data, 512 * 256 * 3, 1, file);
//        fclose(file);
//    }
//}
//
///**
// * OpenGL Initialization.
// */
//void init(char* filename) {
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_FLAT);
//
//    // Read the "image"
//    GLbyte image[512][256][3];
//    readRAWImage(filename, image);
//
//    // Get a name for the texture
//    glGenTextures(1, &textureName);
//
//    // Bind the texture object to its name
//    glBindTexture(GL_TEXTURE_2D, textureName);
//
//    // Specify the parameters
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//    // Specify the application mode
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//    // Create the texture object
//    glTexImage2D(GL_TEXTURE_2D, 0,                // One resolution (i.e. level 0)
//        3,                 // 3 components (i.e., RGB)
//        512,               // Width
//        256,               // Height
//        0,                 // Border width
//        GL_RGB,            // Format
//        GL_UNSIGNED_BYTE,  // Data type of the texels
//        image);
//
//    // Enable textures
//    glEnable(GL_TEXTURE_2D);
//}
//
///**
// * The entry point of the application.
// *
// * @param argc  The number of command line arguments
// * @param argv  The array of command line arguments
// * @return      A status code
// */
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//
//
//    // GLUT Initialization
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("Sphere");
//    glutReshapeFunc(reshape);
//    glutDisplayFunc(display);
//    glutTimerFunc(delay, timer, 0);
//    glutMouseFunc(mouseClicked);
//
//    // OpenGL Initialization
//    char name[] = { 'm','o','o','n','.','b','m','p' };
//    init(name);
//    // Start the event loop
//    glutMainLoop();
//}