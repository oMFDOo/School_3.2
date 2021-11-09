#include <glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

// �浵, ������ ���� �� n�� ����
#define N 12
#define M 6 
#define R 1

struct Point3D {
	double x;
	double y;
	double z;
};

double theta;				// �浵
double phi;					// ����
double delta_theta;			// �浵�� n���� ������
double delta_phi;			// ������ n���� ������
Point3D vertices[N][M + 1];	// ���� ����

float	ver[N][M + 1][3];
float	sphere_radius = 1.0;

// Camera variables//
float	camera_theta, camera_phi, camera_radius;

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

void sphere(int* p) {

	delta_theta = 2 * PI / N;	// �浵
	delta_phi = PI / M;			// ����

	GLfloat ver[N][M+1][3] = { 0 };
	// �� ���� �� ���� : ���� �������� ��� �浵�� ���� ����
	// ()�� ���·� �� ���� ��ġ�� �����Ѵ�.
	// �� �� ������ ǥ���� ���� 'j�� ������ ���� ��ġ�� ������'�� �����Ѵ�.
	for (int i = 0; i <= M; i++) {
		for (int j = 0; j < N; j++) {
			// �� ��/�浵�� ���� ��Ÿ, ���̰� ����
			theta = j * delta_theta;
			phi = i * delta_phi - (PI / 2.0);

			// �ﰢ�Լ��� ���� �� ���� ��ġ ���ϱ�
			vertices[j][i].x = R * cos(theta) * cos(phi) + p[0];
			vertices[j][i].y = R * sin(theta) * cos(phi) + p[1];
			vertices[j][i].z = R * sin(phi) + p[2];
			ver[j][i][0] = vertices[j][i].x;
			ver[j][i][1] = vertices[j][i].y;
			ver[j][i][2] = vertices[j][i].z;
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			// �� ��/�浵�� �´� ��Ÿ, ���̰� ����
			theta = j * delta_theta;
			phi = i * delta_phi - (PI / 2);


			double x, y, z;
			int isplus = 1;
			GLfloat temp[1][1][3] = { 0, };
			if ((vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 < 0) isplus = -1;
			x = (vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 + 0.2 * isplus;
			isplus = 1;
			if ((vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 < 0) isplus = -1;
			y = (vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 + 0.2 * isplus;
			isplus = 1;
			if ((vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 < 0) isplus = -1;
			z = (vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 + 0.2 * isplus;
			temp[0][0][0] = x;
			temp[0][0][1] = y;
			temp[0][0][2] = z;

			// �� �������� �����Ͽ� �׸���
			glColor4f(1.0, 1.0, 0.0, 0.5);
			glBegin(GL_POLYGON); // �� �׸���
			// glBegin(GL_LINE_STRIP); // ���� �׸���

			// ���� ǥ�� �簢�� �׸���
			// ���ϴ�
			glNormal3fv(ver[j][i]);
			glVertex3fv(ver[j][i]);
			// ���ϴ�
			glNormal3fv(ver[(j+1)%N][i]);
			glVertex3fv(ver[(j+1)%N][i]);
			// �ϴ� ��
			glNormal3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);

			glEnd();

			glColor3f(1.0, 1.0, 0.4);
			glBegin(GL_POLYGON); // �� �׸���
			// ���ϴ�
			glNormal3fv(ver[(j + 1) % N][i]);
			glVertex3fv(ver[(j + 1) % N][i]);
			// ����
			glNormal3fv(ver[(j + 1) % N][i+1]);
			glVertex3fv(ver[(j + 1) % N][i+1]);
			// ���� ��
			glNormal3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();

			glColor3f(1.0, 1.0, 0.2);
			glBegin(GL_POLYGON); // �� �׸���
			// �»��
			glNormal3fv(ver[j][i+1]);
			glVertex3fv(ver[j][i+1]);
			// ����
			glNormal3fv(ver[(j + 1) % N][i + 1]);
			glVertex3fv(ver[(j + 1) % N][i + 1]);
			// ��� ��
			glNormal3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();

			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_POLYGON); // �� �׸���
			// ���ϴ�
			glNormal3fv(ver[j][i]);
			glVertex3fv(ver[j][i]);
			// �»��
			glNormal3fv(ver[j][i + 1]);
			glVertex3fv(ver[j][i + 1]);
			// ���� ��
			glNormal3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();
		}
	}
}

void sphereLine(void) {

	delta_theta = 2 * PI / N;	// �浵
	delta_phi = PI / M;			// ����

	GLfloat ver[N][M + 1][3] = { 0 };
	// �� ���� �� ���� : ���� �������� ��� �浵�� ���� ����
	// ()�� ���·� �� ���� ��ġ�� �����Ѵ�.
	// �� �� ������ ǥ���� ���� 'j�� ������ ���� ��ġ�� ������'�� �����Ѵ�.
	for (int i = 0; i <= M; i++) {
		for (int j = 0; j < N; j++) {
			// �� ��/�浵�� ���� ��Ÿ, ���̰� ����
			theta = j * delta_theta;
			phi = i * delta_phi - (PI / 2.0);

			// �ﰢ�Լ��� ���� �� ���� ��ġ ���ϱ�
			vertices[j][i].x = R * cos(theta) * cos(phi);
			vertices[j][i].y = R * sin(theta) * cos(phi);
			vertices[j][i].z = R * sin(phi);
			ver[j][i][0] = vertices[j][i].x;
			ver[j][i][1] = vertices[j][i].y;
			ver[j][i][2] = vertices[j][i].z;
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			// �� ��/�浵�� �´� ��Ÿ, ���̰� ����
			theta = j * delta_theta;
			phi = i * delta_phi - (PI / 2);


			double x, y, z;
			int isplus = 1;
			GLfloat temp[1][1][3] = { 0, };
			if ((vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 < 0) isplus = -1;
			x = (vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 + 0.2 * isplus;
			isplus = 1;
			if ((vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 < 0) isplus = -1;
			y = (vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 + 0.2 * isplus;
			isplus = 1;
			if ((vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 < 0) isplus = -1;
			z = (vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 + 0.2 * isplus;
			temp[0][0][0] = x;
			temp[0][0][1] = y;
			temp[0][0][2] = z;

			// �� �������� �����Ͽ� �׸���
			glColor3f(1.0, 0.7, 0.0);
			glBegin(GL_LINE_LOOP); // �� �׸���
			// glBegin(GL_LINE_STRIP); // ���� �׸���

			// ���� ǥ�� �簢�� �׸���
			// ���ϴ�
			glVertex3fv(ver[j][i]);
			glVertex3fv(ver[j][i]);
			// ���ϴ�
			glVertex3fv(ver[(j + 1) % N][i]);
			glVertex3fv(ver[(j + 1) % N][i]);
			// �ϴ� ��
			glVertex3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);

			glEnd();

			//glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON); // �� �׸���
			// ���ϴ�
			glVertex3fv(ver[(j + 1) % N][i]);
			glVertex3fv(ver[(j + 1) % N][i]);
			// ����
			glVertex3fv(ver[(j + 1) % N][i + 1]);
			glVertex3fv(ver[(j + 1) % N][i + 1]);
			// ���� ��
			glVertex3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();

			//glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON); // �� �׸���
			// �»��
			glVertex3fv(ver[j][i + 1]);
			glVertex3fv(ver[j][i + 1]);
			// ����
			glVertex3fv(ver[(j + 1) % N][i + 1]);
			glVertex3fv(ver[(j + 1) % N][i + 1]);
			// ��� ��
			glVertex3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();

			//glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); // �� �׸���
			// ���ϴ�
			glVertex3fv(ver[j][i]);
			glVertex3fv(ver[j][i]);
			// �»��
			glVertex3fv(ver[j][i + 1]);
			glVertex3fv(ver[j][i + 1]);
			// ���� ��
			glVertex3fv(temp[0][0]);
			glVertex3fv(temp[0][0]);
			glEnd();
		}
	}
}

// ��ü�����η� �������� ���� ó��
/* �� ���� ������ó�� ���� ������ �� �ɱ�� */
float   light0_position[] = { 5.0, 2.0, 2.0, 1.0 };
float   light0_ambient[] = { 0.7, 0.2, 0.8, 1.0 };	// �ֺ���
float   light0_diffuse[] = { 0.2, 0.8, 0.8, 1.0 };	// �л걤
float   light0_specular[] = { 1.0, 1.0, 1.0, 8.0 };	// �ݻ籤

void light() {


	// ���̵� �� ���� 
	//glShadeModel(GL_FLAT);		// �� ���� Ȯ���� ���еǾ� ������ ��
	glShadeModel(GL_SMOOTH); // �ε巴�� ������ ��

	glEnable(GL_COLOR_MATERIAL);

	// ���� �׽�Ʈ ���� �� ���� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Ŀ���� ���� ����
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	GLfloat arMat1[] = { 1.0, 1.0, 0.0, 0.7 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, arMat1);
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	camera_theta = 0.0;
	camera_phi = 0.0;
	camera_radius = 3.2;

	// ���� �׽�Ʈ ����
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {

	glLineWidth(7.0);
	glBegin(GL_LINES);
	
	glColor3f(1.0, 0.0, 0.0); // x�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y�� 
	glLineWidth(8.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z�� 
	glLineWidth(8.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
}

void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(int* p) {
	float	camera_x, camera_y, camera_z;

	camera_x = camera_radius * cos(camera_phi) * cos(camera_theta) + p[0];
	camera_y = camera_radius * cos(camera_phi) * sin(camera_theta) + p[1];
	camera_z = camera_radius * sin(camera_phi) + p[2];

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}


void display(void)
{
	frame_reset();

	int a[] = { 6, 0, 0 };
	camera(a);
	a[0] = 3;
	//sphere(a);
	light();
	//axis();
	int b[] = { 0, 0, 0 };
	sphere(b);
	//sphereLine();

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
	// ���� �̷��� �ϴ� �ſ�����...
	switch (key) {
	case 'a':		camera_radius += 0.01;		break;
	case 's':		camera_radius -= 0.01;		break;
	default: break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("draw sphere 20193148-Ȳ����");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(special_key);
	glutKeyboardFunc(my_key);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
