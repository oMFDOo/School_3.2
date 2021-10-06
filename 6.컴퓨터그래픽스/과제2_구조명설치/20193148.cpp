#include <gl/glut.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>

#pragma warning (disable : 4996)


#define		PI	3.1415926
#define		N	36
#define		M	18 

static int	sphere_drawing_type = 0;
static int	material_able = 0;
static int	switching_shade = 0;

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
	delta_theta = 2.0 * PI / N;

	start_phi = -1.0 * PI / 2.0;
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
	glColor3f(1.0, 0.0, 0.0); // x축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}


// 선과 면의 구분을 위해 선에는 벡터 값 미설정
void Draw_Wire_Sphere(void) {
	glColor3f(0.5, 0.2, 1.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);

			glVertex3f(1.01 * ver[i][j][0], 1.01 * ver[i][j][1], 1.01 * ver[i][j][2]);

			glVertex3f(1.01 * ver[i + 1][j][0], 1.01 * ver[i + 1][j][1], 1.01 * ver[i + 1][j][2]);

			glVertex3f(1.01 * ver[i + 1][j + 1][0], 1.01 * ver[i + 1][j + 1][1], 1.01 * ver[i + 1][j + 1][2]);
			
			glVertex3f(1.01 * ver[i][j + 1][0], 1.01 * ver[i][j + 1][1], 1.01 * ver[i][j + 1][2]);
			glEnd();
		}
	}
}

// 선과 면의 구분을 위해 선에는 벡터 값 미설정
void Draw_Wire_Sphere1(void) {
	glColor3f(0.5, 0.2, 1.0);
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glBegin(GL_LINE_LOOP);

			glVertex3f(1.01 * ver[i][j][0], 1.01 * ver[i][j][1], 1.01 * ver[i][j][2]);
			
			glVertex3f(1.01 * ver[(i + 1) % N][j][0], 1.01 * ver[(i + 1) % N][j][1], 1.01 * ver[(i + 1) % N][j][2]);

			glVertex3f(1.01 * ver[(i + 1) % N][j + 1][0], 1.01 * ver[(i + 1) % N][j + 1][1], 1.01 * ver[(i + 1) % N][j + 1][2]);
			
			glVertex3f(1.01 * ver[i][j + 1][0], 1.01 * ver[i][j + 1][1], 1.01 * ver[i][j + 1][2]);
			glEnd();
		}
	}
}


void Sphere(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 0.3, 0.3);
			glBegin(GL_POLYGON);

			glNormal3fv(ver[i][j]);
			glVertex3fv(ver[i][j]);

			glNormal3fv(ver[i + 1][j]);
			glVertex3fv(ver[i + 1][j]);

			glNormal3fv(ver[i + 1][j + 1]);
			glVertex3fv(ver[i + 1][j + 1]);

			glNormal3fv(ver[i][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
}

void Sphere1(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(0.3, 1.0, 0.3);
			glBegin(GL_POLYGON);

			glNormal3fv(ver[i][j]);
			glVertex3fv(ver[i][j]);

			glNormal3fv(ver[i + 1][j]);
			glVertex3fv(ver[i + 1][j]);

			glNormal3fv(ver[i + 1][j + 1]);
			glVertex3fv(ver[i + 1][j + 1]);

			glNormal3fv(ver[i][j + 1]);
			glVertex3fv(ver[i][j + 1]);

			glEnd();
		}
	}
	Draw_Wire_Sphere();
}

void Sphere2(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(0.3, 0.3, 1.0);
			glBegin(GL_POLYGON);

			glNormal3fv(ver[i][j]);
			glVertex3fv(ver[i][j]);

			glNormal3fv(ver[(i + 1) % N][j]);
			glVertex3fv(ver[(i + 1) % N][j]);

			glNormal3fv(ver[(i + 1) % N][j + 1]);
			glVertex3fv(ver[(i + 1) % N][j + 1]);

			glNormal3fv(ver[i][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
	Draw_Wire_Sphere1();
}

void Sphere3(void) {
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(cos(exp(i + j) * sin(i + j)), sin(j * sin(i * j)), sin(i * j));
			glBegin(GL_POLYGON);

			glNormal3fv(ver[i][j]);
			glVertex3fv(ver[i][j]);

			glNormal3fv(ver[(i + 1) % N][j]);
			glVertex3fv(ver[(i + 1) % N][j]);

			glNormal3fv(ver[(i + 1) % N][j + 1]);
			glVertex3fv(ver[(i + 1) % N][j + 1]);

			glNormal3fv(ver[i][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
}


float   light0_position[] = { 2.8, 1.0, -1.5, 1.0 };
float   light0_ambient[] = { 2.0, 1.0, 1.5, 1.0 };	// 주변광
float   light0_diffuse[] = { 2.0, 1.0, 1.5, 1.0 };	// 분산광
float   light0_specular[] = { 2.0, 1.0, 1.5, 1.0 };	// 반사광


void init(void)
{
	glEnable(GL_DEPTH_TEST);
	Vertex_Generation();


	// 쉐이드 모델 설정 
	//glShadeModel(GL_FLAT); // 각 면이 확실히 구분되어 랜더링 됨
	glShadeModel(GL_SMOOTH); // 부드럽게 랜더링 됨

	// 조명 활성화
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// 커스텀 조명값 적용
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	// 주변광
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	// 분산광
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	// 반사광

	glMaterialfv(GL_FRONT, GL_SPECULAR, light0_specular);
	// 반사광에 대해 반짝거리는 정도를 지정한다. 0 ~128 사이의 범위를 지정할 수 있으며 디폴트는 0이다.
	// 면적 지정의 개념인데, 1~2 정도는 넓은 면적, 127~128은 좁은 면적을 뜻한다.
	glMateriali(GL_FRONT, GL_SHININESS, 50);
}

void swichingShade() {
	if (switching_shade % 2) {
		glShadeModel(GL_FLAT);
	}
	else {
		glShadeModel(GL_SMOOTH);;
	}
}

void swichingMaterial() {
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	// 주변광
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	// 분산광
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	// 반사광

	glMaterialfv(GL_FRONT, GL_SPECULAR, light0_specular);
	// 반사광에 대해 반짝거리는 정도를 지정한다. 0 ~128 사이의 범위를 지정할 수 있으며 디폴트는 0이다.
	// 면적 지정의 개념인데, 1~2 정도는 넓은 면적, 127~128은 좁은 면적을 뜻한다.
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	if (material_able % 2) {
		glEnable(GL_COLOR_MATERIAL);
	}
	else {
		glDisable(GL_COLOR_MATERIAL);
	}
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
void printText(float x, float y, float z, std::string output) {
	void* font = GLUT_BITMAP_9_BY_15;

	glRasterPos3f(x, y, z);
	for (auto& i : output) {
		char c = i;
		glColor3f(1.0, 0.0, 1.0);
		glutBitmapCharacter(font, c);
	}
}

// 글자 출력하기
void drawText() {
	std::string output;

	output = "< PRESS KEYWORD >";
	printText(1.0, -0.5, 1.4, output);


	std::string m = "Disable COLOR_MATERIAL", s = "GL_SMOOTH";
	
	if (switching_shade% 2) { s = "GL_FLAT"; }
	if (material_able % 2) { m = "Enable COLOR_MATERIAL"; }

	output = "s: " + s;
	printText(1.0, -1.0, 1.2, output);

	output = "m: " + m;
	printText(1.0, -1.0, 1.1, output);

	output = "0, 1, 2, 3 : Sphere Model";
	printText(1.0, -1.0, 1.0, output);

}

void display(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	swichingShade();	// 쉐이드 모델 변경
	swichingMaterial();	// 재질 표현 법 변경

	camera_setting();
	axis();

	drawText();


	switch (sphere_drawing_type) {
	case 0: Sphere(); break;
	case 1: Sphere1(); break;
	case 2: Sphere2(); break;
	case 3: Sphere3();break;
	default:break;
	}

	glMatrixMode(GL_PROJECTION);
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
	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case '[':	camera_radius += 0.1;		break;	// 축소
	case ']':	camera_radius -= 0.1;		break;	// 확대
	case 's':   switching_shade += 1;		break;	// 쉐이드 모델 설정
	case 'm':   material_able += 1;			break;	// 재질 모델 설정
	case '0':   sphere_drawing_type = 0;	break;	// 그려질 구 타입 : 잘려진 구  /          /  R
	case '1':   sphere_drawing_type = 1;	break;	// 그려질 구 타입 : 잘려진 구  /  와이어  /  G
	case '2':   sphere_drawing_type = 2;	break;	// 그려질 구 타입 : 완전한 구  /  와이어  /  B
	case '3':   sphere_drawing_type = 3;	break;	// 그려질 구 타입 : 완전한 구  /          /  위치 색상
	default: break;
	}
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 500, 500);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);


	glutCreateWindow("20193148_황진주");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	glutSpecialFunc(special_key);
	glutMainLoop();
}