#include <gl/glut.h>  
#include <math.h>

#define		PI	3.1415926
#define		N	36
#define		M	18 

static int	sphere_drawing_type = 0;

float	sphere_radius = 1.0;
float	camera_radius = 5.0;
float	camera_theta = 0.0;
float	camera_phi = 0.0;

float	ver[N][M + 1][3];


void Vertex_Generation(void) {
	float	theta, phi;
	float	delta_theta, delta_phi;
	float	start_theta, start_phi;

	start_theta = 0.0;
	delta_theta = 2.0*PI / N;

	start_phi = -1.0*PI / 2.0;
	delta_phi = PI / M;

	for (int j = 0; j <= M; j++) {
		for (int i = 0; i < N; i++) {
			theta = start_theta + i * delta_theta;
			phi = start_phi + j * delta_phi;
			ver[i][j][0] = sphere_radius * cos(phi) * cos(theta);
			ver[i][j][1] = sphere_radius * cos(phi) * sin(theta);
			ver[i][j][2] = sphere_radius * sin(phi);
		}
	}
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


void Draw_Wire_Sphere(void) {
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(1.01*ver[i][j][0],		1.01*ver[i][j][1],		1.01*ver[i][j][2]);
			glVertex3f(1.01*ver[i+1][j][0],		1.01*ver[i+1][j][1],	1.01*ver[i+1][j][2]);
			glVertex3f(1.01*ver[i+1][j+1][0],	1.01*ver[i+1][j+1][1],	1.01*ver[i+1][j+1][2]);
			glVertex3f(1.01*ver[i][j+1][0],		1.01*ver[i][j+1][1],	1.01*ver[i][j+1][2]);
			glEnd();
		}
	}
}

void Draw_Wire_Sphere1(void) {
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(1.01*ver[i][j][0],			1.01*ver[i][j][1],			1.01*ver[i][j][2]);
			glVertex3f(1.01*ver[(i+1)%N][j][0],		1.01*ver[(i+1)%N][j][1],	1.01*ver[(i+1)%N][j][2]);
			glVertex3f(1.01*ver[(i+1)%N][j+1][0],	1.01*ver[(i+1)%N][j+1][1],	1.01*ver[(i+1)%N][j+1][2]);
			glVertex3f(1.01*ver[i][j+1][0],			1.01*ver[i][j+1][1],		1.01*ver[i][j+1][2]);
			glEnd();
		}
	}
}


void Sphere(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
				glVertex3fv(ver[i][j]);
				glVertex3fv(ver[i+1][j]);
				glVertex3fv(ver[i+1][j+1]);
				glVertex3fv(ver[i][j+1]);
			glEnd();
		}
	}
}

void Sphere1(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[i+1][j]);
			glVertex3fv(ver[i+1][j+1]);
			glVertex3fv(ver[i][j+1]);
			glEnd();
		}
	}
	Draw_Wire_Sphere();
}

void Sphere2(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[(i+1)%N][j]);
			glVertex3fv(ver[(i+1)%N][j+1]);
			glVertex3fv(ver[i][j+1]);
			glEnd();
		}
	}
	Draw_Wire_Sphere1();
}

void Sphere3(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(cos(exp(i + j)*sin(i + j)), sin(j*sin(i*j)), sin(i*j));
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[(i+1)%N][j]);
			glVertex3fv(ver[(i+1)%N][j+1]);
			glVertex3fv(ver[i][j+1]);
			glEnd();
		}
	}
}


void init(void)
{
	glEnable(GL_DEPTH_TEST);
	Vertex_Generation();
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

	x = camera_radius * cos(camera_theta)*cos(camera_phi);
	y = camera_radius * sin(camera_theta)*cos(camera_phi);
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
	axis();

	switch (sphere_drawing_type) {
	case 0: Sphere(); break;
	case 1: Sphere1(); break;
	case 2: Sphere2(); break;
	case 3: Sphere3(); break;
	default:break;
	}

	glFlush();

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
	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':	camera_radius += 0.1; break;
	case 's':	camera_radius -= 0.1; break;
	case '0':   sphere_drawing_type = 0;	break;
	case '1':   sphere_drawing_type = 1;	break;
	case '2':   sphere_drawing_type = 2;	break;
	case '3':   sphere_drawing_type = 3;	break;
	default: break;
	}
	glutPostRedisplay();
}


void main(void)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("2D_Sphere");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	glutSpecialFunc(special_key);
	glutMainLoop();
}