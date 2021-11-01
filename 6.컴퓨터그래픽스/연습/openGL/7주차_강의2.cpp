#include <windows.h>           
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl/glut.h>   
#include <math.h>
#include <iostream>
using namespace std;

#define	PI	3.1415926

float	camera_radius, camera_theta, camera_phi;


float	lightPositionR[] = { 0.0f, 0.0f, 7.5f, 1.0f };
float	lightPositionG[] = { 0.0f, 0.0f, 7.5f, 1.0f };
float	lightPositionB[] = { 0.0f, 0.0f, 7.5f, 1.0f };

float	diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float	diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float	diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

float	specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float	specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float	specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

float	spotRirection[] = { 0.0f, 0.0f, -1.0f };

float	diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float	specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float	lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };

int		currentColor = 1;
bool	spotEnabled = true;


int		v_no;
struct	point3d {
	float	x;
	float	y;
	float	z;
}*vertices, * normals;


int		f_no;
struct	face4 {
	int		v1;
	int		v2;
	int		v3;
	int		v4;
}*face;



void	file_load(void) {

	FILE* fp1;

	if (fopen_s(&fp1, "box.txt", "r") != NULL) {
		cout << " Can not compute \n";
		exit(1);
	}

	fscanf_s(fp1, "%d", &v_no); //input vertex number
	vertices = new point3d[v_no];
	for (int i = 0; i < v_no; i++)
		fscanf_s(fp1, "%f %f %f", &(vertices[i].x), &(vertices[i].y), &(vertices[i].z));

	fscanf_s(fp1, "%d", &f_no); //input faces number
	face = new face4[f_no];
	for (int i = 0; i < f_no; i++)
		fscanf_s(fp1, "%d %d %d %d", &(face[i].v1), &(face[i].v2), &(face[i].v3), &(face[i].v4)); // face information

	fclose(fp1);
}

void vertex_normal_computation(void)
{
	float	distance;
	normals = new point3d[v_no];

	for (int i = 0; i < v_no; i++) {
		distance = sqrt(vertices[i].x * vertices[i].x +
			vertices[i].y * vertices[i].y +
			vertices[i].z * vertices[i].z);

		normals[i].x = vertices[i].x / distance;
		normals[i].y = vertices[i].y / distance;
		normals[i].z = vertices[i].z / distance;

	}
}


void draw_object(void) {
	int index;

	for (int i = 0; i < f_no; i++) {

		glBegin(GL_POLYGON);

		index = face[i].v1;
		glNormal3f(normals[index].x, normals[index].y, normals[index].z);
		glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);

		index = face[i].v2;
		glNormal3f(normals[index].x, normals[index].y, normals[index].z);
		glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);

		index = face[i].v3;
		glNormal3f(normals[index].x, normals[index].y, normals[index].z);
		glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);

		index = face[i].v4;
		glNormal3f(normals[index].x, normals[index].y, normals[index].z);
		glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);
		glEnd();
	}
}




void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	camera_radius = 6.0;
	camera_theta = 0.4;
	camera_phi = 0.5;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);


	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 80.0f);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);


	file_load();
	vertex_normal_computation();

}

void axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // xÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // yÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // zÃà 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000);
}


void camera_setting(void)
{
	float	x, y, z;

	x = camera_radius * cos(camera_theta) * cos(camera_phi);
	y = camera_radius * sin(camera_theta) * cos(camera_phi);
	z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}



void display(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_setting();

	glDisable(GL_LIGHTING);
	axis();
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	switch (currentColor) {
	case 1:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightR);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightG);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightG);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightG);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionG);

		glColor3f(0.0f, 1.0f, 0.0f);
		break;

	case 3:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightB);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightB);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightB);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionB);

		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	}

	draw_object();

	glFlush();
	glutSwapBuffers();
}


void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:		camera_theta -= 0.01; 	break;
	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
	default: break;
	}
	if (camera_theta > 2.0 * PI)
		camera_theta -= (2.0 * PI);
	else if (camera_theta < 0.0)
		camera_theta += (2.0 * PI);

	if (camera_phi > PI / 2.0)
		camera_phi -= PI;
	else if (camera_phi < -PI / 2.0)
		camera_theta += PI;

	glutPostRedisplay();
}

void my_key(unsigned char key, int x, int y)
{
	switch (key) {
	case 'o':	camera_radius += 0.1; break;
	case 'p':	camera_radius -= 0.1; break;
	case 'r':	currentColor = 1;	break;
	case 'g':	currentColor = 2;	break;
	case 'b':	currentColor = 3;	break;
	case 's':
		if (spotEnabled) {
			spotEnabled = false;
			glDisable(GL_LIGHT0);
		}
		else {
			spotEnabled = true;
			glEnable(GL_LIGHT0);
		}
		break;
	default: break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("file_loaded_cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special_key);
	glutKeyboardFunc(my_key);
	glutIdleFunc(display);
	init();
	glutMainLoop();
	return 0;
}
