//#include <windows.h>           
//#include <iostream>
//using namespace std;
//
//#include <gl/glut.h>
//#include <math.h>
//
//#define PI   3.1415926
//#define N    36    // Number of parameter “theta” 
//#define M    18    // Number of parameter “phi”  
//
//float theta, phi;
//float delta_theta, delta_phi;
//float start_theta, start_phi;
//
//float	radius;
//float	ver[N][M + 1][3], ver2[N][M + 1][3];
//
//int		camera_setting_flag = 0;
//int		light_type = 1; // right normal computation  
//
//typedef struct postion {
//	float	x;
//	float	y;
//	float	z;
//}position;
//
//
//position fixed_sphere, moving;
//
//// 광원 속성
//float light_position[] = { 0.0, 0.0, -7.0, 1.0 };
//float light_ambient[] = { 1.0, 0.0, 0.0, 0.0 };
//float light_diffuse[] = { 1.0, 1.0, 0.0, 0.0 };
//float light_specular[] = { 0.0, 0.0, 1.0, 0.0 };
//
//// 재질 1 : 반사율 
//float ambient0[] = { 1.0, 1.0, 1.0, 0.0 };
//float diffuse0[] = { 1.0, 1.0, 0.0, 0.0 };
//float specular0[] = { 1.0, 1.0, 1.0, 0.0 };
//
//// 재질 2 : 반사율
//float ambient1[] = { 0.0, 1.0, 1.0, 0.0 };
//float diffuse1[] = { 0.0, 1.0, 1.0, 0.0 };
//float specular1[] = { 0.0, 1.0, 1.0, 0.0 };
//
//
//void  VertexGeneration(void) {
//	start_theta = 0.0;
//	delta_theta = 2.0 * PI / N;
//	start_phi = -1.0 * PI / 2.0;
//	delta_phi = 1.0 * PI / M;
//
//	for (int j = 0; j <= M; j++) { // phi (위도)
//		for (int i = 0; i < N; i++) {  // theta (경도)
//			theta = start_theta + i * delta_theta;
//			phi = start_phi + j * delta_phi;
//			ver[i][j][0] = radius * cos(phi) * cos(theta);
//			ver[i][j][1] = radius * cos(phi) * sin(theta);
//			ver[i][j][2] = radius * sin(phi);
//		}
//
//	}
//	for (int j = 0; j <= M; j++) { // phi (위도)
//		for (int i = 0; i < N; i++) {  // theta (경도)
//			theta = start_theta + i * delta_theta;
//			phi = start_phi + j * delta_phi;
//			ver2[i][j][0] = ver[i][j][0] + moving.x;
//			ver2[i][j][1] = ver[i][j][1] + moving.y;
//			ver2[i][j][2] = ver[i][j][2] + moving.z;
//		}
//
//	}
//}
//
//
//
//void DrawSphere1(void) {
//	for (int j = 0; j < M; j++) {
//		for (int i = 0; i < N; i++) {
//			glBegin(GL_POLYGON);
//			glNormal3fv(ver[i][j]);
//			glVertex3fv(ver[i][j]);
//
//			glNormal3fv(ver[(i + 1) % N][j]);
//			glVertex3fv(ver[(i + 1) % N][j]);
//
//			glNormal3fv(ver[(i + 1) % N][j + 1]);
//			glVertex3fv(ver[(i + 1) % N][j + 1]);
//
//			glNormal3fv(ver[i][j + 1]);
//			glVertex3fv(ver[i][j + 1]);
//			glEnd();
//		}
//	}
//}
//
//void DrawSphere2(void) {
//	for (int j = 0; j <= M; j++) { // phi (위도)
//		for (int i = 0; i < N; i++) {  // theta (경도)
//			theta = start_theta + i * delta_theta;
//			phi = start_phi + j * delta_phi;
//			ver2[i][j][0] = ver[i][j][0] + moving.x;
//			ver2[i][j][1] = ver[i][j][1] + moving.y;
//			ver2[i][j][2] = ver[i][j][2] + moving.z;
//		}
//
//	}
//	if (light_type % 2) {
//		for (int j = 0; j < M; j++) {
//			for (int i = 0; i < N; i++) {
//				glBegin(GL_POLYGON);
//				glNormal3fv(ver[i][j]);
//				glVertex3fv(ver2[i][j]);
//
//				glNormal3fv(ver[(i + 1) % N][j]);
//				glVertex3fv(ver2[(i + 1) % N][j]);
//
//				glNormal3fv(ver[(i + 1) % N][j + 1]);
//				glVertex3fv(ver2[(i + 1) % N][j + 1]);
//
//				glNormal3fv(ver[i][j + 1]);
//				glVertex3fv(ver2[i][j + 1]);
//				glEnd();
//			}
//		}
//	}
//	else {
//		for (int j = 0; j < M; j++) {
//			for (int i = 0; i < N; i++) {
//				glBegin(GL_POLYGON);
//				glNormal3fv(ver2[i][j]);
//				glVertex3fv(ver2[i][j]);
//
//				glNormal3fv(ver2[(i + 1) % N][j]);
//				glVertex3fv(ver2[(i + 1) % N][j]);
//
//				glNormal3fv(ver2[(i + 1) % N][j + 1]);
//				glVertex3fv(ver2[(i + 1) % N][j + 1]);
//
//				glNormal3fv(ver2[i][j + 1]);
//				glVertex3fv(ver2[i][j + 1]);
//				glEnd();
//			}
//		}
//	}
//
//}
//
//
//void  init(void) {
//	radius = 1.0;
//	fixed_sphere.x = 0.0;
//	fixed_sphere.y = 0.0;
//	fixed_sphere.z = 0.0;
//
//	moving.x = 3.0;
//	moving.y = 0.0;
//	moving.z = 0.0;
//
//	glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_SMOOTH);   //glShadeModel(GL_FLAT);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	VertexGeneration();
//}
//
//
//void  reshape(int w, int h) {
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0, 1.0, 1.0, 1000);
//}
//
//void Draw_Axis(void) {
//
//	glLineWidth(3.0);
//	glBegin(GL_LINES);
//	glColor3f(1.0, 0.0, 0.0); // red color
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(100.0, 0.0, 0.0);
//
//	glColor3f(0.0, 1.0, 0.0); // green color
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(0.0, 100.0, 0.0);
//
//	glColor3f(0.0, 0.0, 1.0); // blue color
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(0.0, 0.0, 100.0);
//	glEnd();
//}
//
//void display(void)
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	if (camera_setting_flag % 2) {
//		glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // light position in camera coordinates system
//		gluLookAt(6.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//	}
//	else {
//		gluLookAt(6.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//		glLightfv(GL_LIGHT0, GL_POSITION, light_position); // light position in world coordinates
//	}
//
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse0); // Yellow Sphere
//	DrawSphere1();
//
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1); // Green Sphere
//	DrawSphere2();
//
//	glDisable(GL_LIGHTING);
//	Draw_Axis();
//	glEnable(GL_LIGHTING);
//
//	glFlush();
//}
//
//void my_keyboeard(unsigned char key, int x, int y) {
//	switch (key) {
//
//	case 'a':		light_position[2] += 0.1;
//		break;
//	case 'd':		light_position[2] -= 0.1;
//		break;
//	case 'l':		light_type++;
//		break;
//	case 'c':		camera_setting_flag++;
//		break;
//	default: break;
//	}
//	glutPostRedisplay();
//}
//
//void my_special(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_LEFT:		moving.x -= 0.1;
//		break;
//	case GLUT_KEY_RIGHT:	moving.x += 0.1;
//		break;
//	case GLUT_KEY_DOWN:		moving.y -= 0.1;
//		break;
//	case GLUT_KEY_UP:		moving.y += 0.1;
//		break;
//	default: break;
//	}
//	glutPostRedisplay();
//}
//
//
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Two Spheres under camera position change");
//	init();
//	glutDisplayFunc(display);
//	glutKeyboardFunc(my_keyboeard);
//	glutSpecialFunc(my_special);
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//}