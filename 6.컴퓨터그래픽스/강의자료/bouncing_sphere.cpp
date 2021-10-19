#include <windows.h>
#include <iostream>
using namespace std;
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define		PI		3.1415926 
#define		width	800
#define		height	800

float	angle = 0.0f;
float	camera_radius, camera_theta, camera_phi;
int		object_type = 2;
float	object_radius = 30.0f;

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

float	objectZposition = 70.0;
float	objectZvelocity = -0.05;

float	groundZposition = -80.0f;
float	objectDistance ;

int		currentColor = 1;
int		draw_type = 1;
bool	spotEnabled = true;

int		v_no, f_no;


void	Initialize(void)
{
	camera_radius = 250.0f;
	camera_theta = 0.4;
	camera_phi = 0.3;

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
	float	x, y, z;

	x = camera_radius * cos(camera_theta)*cos(camera_phi);
	y = camera_radius * sin(camera_theta)*cos(camera_phi);
	z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1.0f, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
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
	
	glTranslatef(0.0f, 0.0f, objectZposition);

	switch (object_type) {
	case 1:	object_radius = 35.0f;
			if (draw_type % 2)
				glutSolidCube(2*object_radius);				  
			else
				glutWireCube(2*object_radius);			
			break;
	case 2:	object_radius = 30.0f;
			if (draw_type % 2)
				glutSolidSphere(object_radius, 100, 100);	  
			else
				glutWireSphere(object_radius, 100, 100);	  
			break;
	case 3: object_radius = 30.0f; 
			if (draw_type % 2)
				glutSolidTorus(20.0f, object_radius, 100, 100);
			else 
				glutWireTorus(20.0f, object_radius, 100, 100);
			break;
	default: break;
	}
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, groundZposition);
		glScalef(1.0f, 1.0f, 0.01f);
		glutSolidCube(400.0f);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	glFlush();
	glutSwapBuffers();

	objectDistance = (objectZposition - object_radius) - groundZposition;
	if  ( (objectZvelocity < 0 && objectDistance < 0) ||
		  (objectZvelocity > 0 && objectDistance > 150) )
		objectZvelocity *= -1.0;
	
	objectZposition += objectZvelocity;	
}


void  reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(54.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
}


void my_keyboeard(unsigned char key, int x, int y) {
	switch (key) {
	case 'o':	camera_radius += 1.0f; break;
	case 'p':	camera_radius -= 1.0f; break;

	case '1':	object_type = 1;	break;
	case '2':	object_type = 2;	break;
	case '3':	object_type = 3;	break;
	
	case 'd':	draw_type++;		break;

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
	glutSpecialFunc(special_key);
	glutIdleFunc(display);
	glutMainLoop();
}
