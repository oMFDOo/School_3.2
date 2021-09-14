#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

// Camera variables//
float	camera_theta, camera_phi, camera_radius;

GLfloat		vertices[][3] = {
	{ -1.0, -1.0,  1.0 },		// 0 
	{ -1.0,  1.0,  1.0 },		// 1
	{ 1.0,  1.0,  1.0 },		// 2
	{ 1.0, -1.0,  1.0 },		// 3
	{ -1.0, -1.0, -1.0 },		// 4
	{ -1.0,  1.0, -1.0 },		// 5
	{ 1.0,  1.0, -1.0 },		// 6
	{ 1.0, -1.0, -1.0 } };		// 7

GLfloat		colors[][3] = {
	{ 1.0, 0.0, 0.0 },			// red
	{ 0.0, 1.0, 0.0 },			// green 
	{ 1.0, 1.0, 0.0 },			// yellow
	{ 1.0, 1.0, 1.0 },			// white
	{ 0.0, 0.0, 1.0 },			// blue
	{ 1.0, 0.0, 1.0 } };		// magenta

void polygon(int a, int b, int c, int d) {
	glColor3fv(colors[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void cube(void) {
	polygon(2, 3, 7, 6);
	polygon(4, 5, 6, 7);
	polygon(3, 0, 4, 7);
	polygon(1, 2, 6, 5);
	polygon(5, 4, 0, 1);
	polygon(0, 3, 2, 1);

}

void init(void)
{
	camera_theta = 0.0;
	camera_phi = 0.0;
	camera_radius = 5.0;

	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
}

void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	float	camera_x, camera_y, camera_z;

	camera_x = camera_radius * cos(camera_phi) * cos(camera_theta);
	camera_y = camera_radius * cos(camera_phi) * sin(camera_theta);
	camera_z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}


void display(void)
{
	frame_reset();

	camera();
	axis();
	cube();

	glFlush();
	glutSwapBuffers();
}

void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
	case GLUT_KEY_LEFT:		camera_theta -= 0.01;	break;
	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
	default: break;
	}
	glutPostRedisplay();
}


void my_key(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':		camera_radius += 0.01;		break;
	case 's':		camera_radius -= 0.01;		break;
	default: break;
	}
	glutPostRedisplay();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(special_key);
	glutKeyboardFunc(my_key);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
