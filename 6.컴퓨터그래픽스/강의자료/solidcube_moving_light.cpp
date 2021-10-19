#include <windows.h>
#include <iostream>
using namespace std;
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define width	800
#define height	800

float	angle = 0.0f;
float	camera_radius = 100.0f;
int		object_type = 1;

float	lightPositionR[] = { 0.0f, 0.0f, 75.0f, 1.0f };
float	lightPositionG[] = { 0.0f, 0.0f, 75.0f, 1.0f };
float	lightPositionB[] = { 0.0f, 0.0f, 75.0f, 1.0f };

float	diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float	diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float	diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

float	specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float	specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float	specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

float	spotRirection[] = { 0.0f, 0.0f, -1.0f };

float	diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float	specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float	lightPosition[] = { 0.0f, 0.0f, 100.0f, 1.0f };

float	objectXRot;
float	objectYRot;
float	objectZRot;

float	redXRot;
float	redYRot;

int		currentColor = 1;
bool	spotEnabled = true;

int		v_no, f_no;


void	Initialize(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


void Draw_Axis(void) {

	glLineWidth(3.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // red color
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // green color
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // blue color
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
}


void camera_setting(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(54.0f, 1.0f, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_radius, camera_radius, 0.5 * camera_radius, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void	display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_setting();
	
	glDisable(GL_LIGHTING);
	Draw_Axis();
	glEnable(GL_LIGHTING);


	glPushMatrix();
	glRotatef(redYRot, 0.0f, 1.0f, 0.0f);
	glRotatef(redXRot, 1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

	switch (currentColor) {
	case 1:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightR);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);
		glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightG);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightG);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightG);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionG);
		glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
		glColor3f(0.0f, 1.0f, 0.0f);
		break;

	case 3:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightB);
		glLightfv(GL_LIGHT1, GL_EMISSION, diffuseLightB);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightB);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionB);
		glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	}

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glutSolidSphere(2.5f, 100, 100);
	glEnable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();

	glPushMatrix();
	glRotatef(objectXRot, 1.0f, 0.0f, 0.0f);
	glRotatef(objectYRot, 0.0f, 1.0f, 0.0f);
	glRotatef(objectZRot, 0.0f, 0.0f, 1.0f);
	
	switch (object_type) {
	case 1:	glutSolidCube(70.0f);				break;
	case 2:	glutSolidSphere(30.0f, 100, 100);	break;
	case 3:glutSolidTorus(10.f, 30.f, 100, 100); break;
	default: break;
	}
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

	objectXRot += 0.002f;
	objectYRot += 0.004f;
	objectZRot += 0.002f;

	redXRot += 0.03f;
	redYRot += 0.01f;
}


void  reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(54.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
}


void my_keyboeard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':	object_type = 1;	break;
	case '2':	object_type = 2;	break;
	case '3':	object_type = 3;	break;

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

void main(void)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Cube_Sphere_Torus under a moving light source");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(my_keyboeard);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
}
