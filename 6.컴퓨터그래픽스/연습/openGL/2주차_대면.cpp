//#include <glut.h>
//#include <gl/gl.h>
//#include <stdio.h>
//#include <math.h>
//
//#define	PI	3.1415926
//
//// �浵, ������ ���� �� n�� ����
//#define N 6
//#define M 4 
//#define R 1
//
//struct Point3D {
//	double x;
//	double y;
//	double z;
//};
//
//double theta;				// �浵
//double phi;					// ����
//double delta_theta;			// �浵�� n���� ������
//double delta_phi;			// ������ n���� ������
//Point3D vertices[N][M + 1];	// ���� ����
//
//// Camera variables//
//float	camera_theta, camera_phi, camera_radius;
//
//void sphere(void) {
//
//	delta_theta = 2 * PI / N;	// �浵
//	delta_phi = PI / M;			// ����
//
//	// �� ���� �� ���� : ���� �������� ��� �浵�� ���� ����
//	// ()�� ���·� �� ���� ��ġ�� �����Ѵ�.
//	// �� �� ������ ǥ���� ���� 'j�� ������ ���� ��ġ�� ������'�� �����Ѵ�.
//	for (int i = 0; i <= M; i++) {
//		for (int j = 0; j < N; j++) {
//			// �� ��/�浵�� ���� ��Ÿ, ���̰� ����
//			theta = j * delta_theta;
//			phi = i * delta_phi - (PI / 2.0);
//
//			// �ﰢ�Լ��� ���� �� ���� ��ġ ���ϱ�
//			vertices[j][i].x = R * cos(theta) * cos(phi);
//			vertices[j][i].y = R * sin(theta) * cos(phi);
//			vertices[j][i].z = R * sin(phi);
//		}
//	}
//
//	for (int i = 0; i < M; i++) {
//		for (int j = 0; j < N; j++) {
//			// �� ��/�浵�� �´� ��Ÿ, ���̰� ����
//			theta = j * delta_theta;
//			phi = i * delta_phi - (PI / 2);
//
//
//			double x, y, z;
//			int isplus = 1;
//			x = (vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 + abs(i-M) * 0.1;
//			y = (vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 + abs(i - M) * 0.1;
//			z = (vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 + abs(i - M) * 0.1;
//
//			// �� �������� �����Ͽ� �׸���
//			glColor3f(1.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // �� �׸���
//		    // glBegin(GL_LINE_STRIP); // ���� �׸���
//
//		    // ���� ǥ�� �簢�� �׸���
//		    // ���ϴ�
//			glVertex3f(vertices[j][i].x, vertices[j][i].y, vertices[j][i].z);
//			// ���ϴ�
//			glVertex3f(vertices[(j + 1) % N][i].x, vertices[(j + 1) % N][i].y, vertices[(j + 1) % N][i].z);
//			// �ϴ� ��
//			glVertex3f(x, y, z);
//
//			glEnd();
//
//			glColor3f(0.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // �� �׸���
//			// ���ϴ�
//			glVertex3f(vertices[(j + 1) % N][i].x, vertices[(j + 1) % N][i].y, vertices[(j + 1) % N][i].z);
//			// ����
//			glVertex3f(vertices[(j + 1) % N][i + 1].x, vertices[(j + 1) % N][i + 1].y, vertices[(j + 1) % N][i + 1].z);
//
//			// ���� ��
//			glVertex3f(x, y, z);
//
//			glEnd();
//			glColor3f(0.0, 0.0, 1.0);
//			glBegin(GL_POLYGON); // �� �׸���
//			// �»��
//			glVertex3f(vertices[j][i + 1].x, vertices[j][i + 1].y, vertices[j][i + 1].z);
//			// ����
//			glVertex3f(vertices[(j + 1) % N][i + 1].x, vertices[(j + 1) % N][i + 1].y, vertices[(j + 1) % N][i + 1].z);
//
//			// ��� ��
//			glVertex3f(x, y, z);
//
//			glEnd();
//
//			glColor3f(1.0, 0.0, 0.0);
//			glBegin(GL_POLYGON); // �� �׸���
//			// ���ϴ�
//			glVertex3f(vertices[j][i].x, vertices[j][i].y, vertices[j][i].z);
//			// �»��
//			glVertex3f(vertices[j][i + 1].x, vertices[j][i + 1].y, vertices[j][i + 1].z);
//			
//			// ���� ��
//			glVertex3f(x, y, z);
//			glEnd();
//		}
//	}
//}
//
//
//// ��ü�����η� �������� ���� ó��
///* �� ���� ������ó�� ���� ������ �� �ɱ�� */
//float   light0_position[] = { 2.8, 1.0, -1.5, 1.0 };
//float   light0_ambient[] = { 2.0, 1.0, 1.5, 1.0 };	// �ֺ���
//float   light0_diffuse[] = { 2.0, 1.0, 1.5, 1.0 };	// �л걤
//float   light0_specular[] = { 2.0, 1.0, 1.5, 1.0 };	// �ݻ籤
//
//void init(void) {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//
//	camera_theta = 0.0;
//	camera_phi = 0.0;
//	camera_radius = 3.2;
//
//	// ���� �׽�Ʈ ����
//	glEnable(GL_DEPTH_TEST);
//
//	// ���̵� �� ���� 
//	glShadeModel(GL_FLAT);		// �� ���� Ȯ���� ���еǾ� ������ ��
//	// glShadeModel(GL_SMOOTH); // �ε巴�� ������ ��
//	
//	glEnable(GL_COLOR_MATERIAL);
//
//	// ���� �׽�Ʈ ���� �� ���� Ȱ��ȭ
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	// Ŀ���� ���� ����
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
//}
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
//	gluPerspective(60.0, 1.0, 1.0, 20.0);
//}
//
//void axis(void) {
//
//	glLineWidth(7.0);
//	glBegin(GL_LINES);
//	glColor3f(1.0, 0.0, 0.0); // x�� 
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(100.0, 0.0, 0.0);
//
//	glColor3f(0.0, 1.0, 0.0); // y�� 
//	glLineWidth(8.0);
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(0.0, 100.0, 0.0);
//
//	glColor3f(0.0, 0.0, 1.0); // z�� 
//	glLineWidth(8.0);
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(0.0, 0.0, 100.0);
//	glEnd();
//}
//
//void frame_reset(void) {
//	glClearColor(0.6, 0.6, 0.6, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void camera(void) {
//	float	camera_x, camera_y, camera_z;
//
//	camera_x = camera_radius * cos(camera_phi) * cos(camera_theta);
//	camera_y = camera_radius * cos(camera_phi) * sin(camera_theta);
//	camera_z = camera_radius * sin(camera_phi);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//}
//
//
//void display(void)
//{
//	frame_reset();
//
//	camera();
//	axis();
//	sphere();
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//void special_key(int key, int x, int y)
//{
//	switch (key) {
//	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
//	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
//	case GLUT_KEY_LEFT:		camera_theta -= 0.01;	break;
//	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
//	default: break;
//	}
//	glutPostRedisplay();
//}
//
//
//void my_key(unsigned char key, int x, int y)
//{
//	// ���� �̷��� �ϴ� �ſ�����...
//	switch (key) {
//	case 'a':		camera_radius += 0.01;		break;
//	case 's':		camera_radius -= 0.01;		break;
//	default: break;
//	}
//	glutPostRedisplay();
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("draw sphere 20193148-Ȳ����");
//	init();
//	glutDisplayFunc(display);
//	glutSpecialFunc(special_key);
//	glutKeyboardFunc(my_key);
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//	return 0;
//}
