#include <glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926
// 모델 사이즈 설정 : 위도, 경도
#define M 36 
#define N 18 

float radius = 1;
float theta;
float phi;
float delta_theta;
float delta_phi;

struct Point3D
{
	float x;
	float y;
	float z;
};

Point3D vertices[M][N + 1];

// Camera variables//
float	camera_theta, camera_phi, camera_radius;

void sphere(void) {

	delta_theta = 2 * PI / M;	// 위도
	delta_phi = PI / N;			// 경도

	//// 각 정점 값 설정
	//for (int j = 0; j <= N; j++) {
	//	for (int i = 0; i < M; i++) {
	//		// 각 위/경도에 맞는 델타, 파이값 설정
	//		theta = i * delta_theta;
	//		phi = j * delta_phi - (PI / 2.0);

	//		// 
	//		vertices[i][j].x = radius * cos(theta) * cos(phi);
	//		vertices[i][j].y = radius * sin(theta) * cos(phi);
	//		vertices[i][j].z = radius * sin(phi);
	//	}
	//}

	//for (int j = 0; j < N; j++) {
	//	for (int i = 0; i < M; i++) {
	//		
	//		theta = i * delta_theta;
	//		phi = j * delta_phi - (PI / 2);

	//		// 각 정점값을 설정하여 그리기
	//		glColor3f(1.0, 1.0, 0.0);
	//		glBegin(GL_POLYGON);
	//		glVertex3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);
	//		glVertex3f(vertices[(i + 1) % M][j].x, vertices[(i + 1) % M][j].y, vertices[(i + 1) % M][j].z);
	//		glVertex3f(vertices[(i + 1) % M][j + 1].x, vertices[(i + 1) % M][j + 1].y, vertices[(i + 1) % M][j + 1].z);
	//		glVertex3f(vertices[i][j + 1].x, vertices[i][j + 1].y, vertices[i][j + 1].z);
	//		glEnd();
	//	}
	//}

	double x, y, z, c = 0.3;
	for (float phi = -90.0; phi <= 70.0; phi += 20.0)
	{
		glBegin(GL_QUAD_STRIP);
		for (float theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			x = sin(c * theta) * cos(c * phi);
			y = cos(c * theta) * cos(c * phi);
			z = sin(c * phi);
			glVertex3d(x, y, z);
			x = sin(c * theta) * cos(c * (phi + 20.0));
			y = cos(c * theta) * cos(c * (phi + 20.0));
			z = sin(c * (phi + 20.0));
			glVertex3d(x, y, z);
		}
		glEnd();
	}
}


// 조명 처리
float   light0_position[] = { 2.8, 1.0, -1.5, 1.0 };
float   light0_ambient[] = { 2.0, 1.0, 1.5, 1.0 };
float   light0_diffuse[] = { 2.0, 1.0, 1.5, 1.0 };
float   light0_specular[] = { 2.0, 1.0, 1.5, 1.0 };

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	camera_theta = 0.0;
	camera_phi = 0.0;
	camera_radius = 3.2;

	glEnable(GL_DEPTH_TEST);

	// 쉐이드 모델 설정
	glShadeModel(GL_SMOOTH);

	// 깊이 테스트 실행 및 조명 활성화
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// 커스텀 조명값 적용
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
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

	glLineWidth(7.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 
	glLineWidth(8.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z축 
	glLineWidth(8.0);
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
	sphere();

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
	glutCreateWindow("draw sphere 20193148-황진주");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(special_key);
	glutKeyboardFunc(my_key);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
