//#include <windows.h>           
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <gl/glut.h>   
//#include <math.h>
//#include <iostream>
//using namespace std;
//
//#define	PI	3.1415926
//#define	N	50
//#define M	50 
//
//int		draw_type = GL_POLYGON;
//int		light_camera_type = 0;
//
//float	Radius;
//
//float	camera_distance;
//float	camera_theta, camera_phi;
//
//float	last_x, last_y;
//float	light_position_x, light_position_y;
//
//float	diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//float	specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
////float	lightPositionR[] = { 0.0f, 0.0f, -3.5f, 1.0f };
//float	lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };
//
//struct  vector3d {
//	float		x;
//	float		y;
//	float		z;
//};
//
//float	ver[N][M + 1][3];
//float	normal[N][M + 1][3];
//
//int		v_count = 0;
//int		f_count = 0;
//
//void	Vertex_Generation(void) {
//	float	theta, phi;
//	float	delta_theta, delta_phi;
//	float	start_theta, start_phi;
//
//	start_theta = 0.0;
//	delta_theta = 2 * PI / N;
//
//	start_phi = -PI / 2.0;
//	delta_phi = PI / (M - 1);
//
//	for (int j = 0; j <= M; j++) {
//		for (int i = 0; i < N; i++) {
//			theta = start_theta + i * delta_theta;
//			phi = start_phi + j * delta_phi;
//			ver[i][j][0] = Radius * cos(phi) * cos(theta);
//			ver[i][j][1] = Radius * cos(phi) * sin(theta);
//			ver[i][j][2] = Radius * sin(phi);
//			v_count++;
//		}
//	}
//}
//
//void Modify_Vertex(void) {
//	float	length;
//	for (int j = 0; j < M; j++) {
//		for (int i = 0; i < N; i++) {
//			if (fabs(ver[i][j][2]) < 0.5) {
//				length = (4.0 * sqrt(3.0) - 1.0) / 2.0 * fabs(ver[i][j][2])
//					* fabs(ver[i][j][2]) + 1 / 8.0;
//				ver[i][j][0] *= length;
//				ver[i][j][1] *= length;
//			}
//		}
//	}
//}
//
//
//vector3d	Normalization(vector3d U) {
//	float		distance;
//	vector3d	Unit_vector;
//
//	distance = sqrt(U.x * U.x + U.y * U.y + U.z * U.z);
//
//	Unit_vector.x = 1 / distance * U.x;
//	Unit_vector.y = 1 / distance * U.y;
//	Unit_vector.z = 1 / distance * U.z;
//
//	return Unit_vector;
//}
//
//vector3d Cross_Product(vector3d U, vector3d V) {
//	vector3d cross_vector;
//
//	cross_vector.x = U.y * V.z - U.z * V.y;
//	cross_vector.y = -1.0 * (U.x * V.z - U.z * V.x);
//	cross_vector.z = U.x * V.y - U.y * V.x;
//
//	return cross_vector;
//}
//
//
//vector3d Face_Normal_Vector(int a, int b, int c, int d, int e, int f) {
//	vector3d U, V;
//
//	U.x = ver[c][d][0] - ver[a][b][0];
//	U.y = ver[c][d][1] - ver[a][b][1];
//	U.z = ver[c][d][2] - ver[a][b][2];
//
//	V.x = ver[e][f][0] - ver[a][b][0];
//	V.y = ver[e][f][1] - ver[a][b][1];
//	V.z = ver[e][f][2] - ver[a][b][2];
//
//	return (Normalization(Cross_Product(U, V)));
//}
//
//void Vertex_Normal_Computation(void) {
//	vector3d S, normal1, normal2, normal3, normal4, temp_vector;
//
//	S.x = 0.0;
//	S.y = 0.0;
//	S.z = 0.0;
//	for (int i = 0; i < N; i++) {
//		normal1 = Face_Normal_Vector(i, 0, (i + 1) % N, 1, i, 1);
//		S.x += normal1.x;
//		S.y += normal1.y;
//		S.z += normal1.z;
//	}
//	S = Normalization(S);
//
//	for (int i = 0; i < N; i++) {
//		normal[i][0][0] = S.x;
//		normal[i][0][1] = S.y;
//		normal[i][0][2] = S.z;
//	}
//
//	for (int j = 1; j < M; j++) {
//		for (int i = 0; i < N; i++) {
//			normal1 = Face_Normal_Vector(i, j, (i + 1) % N, j, i, j + 1);
//			normal2 = Face_Normal_Vector(i, j, i, j + 1, (i - 1 + N) % N, j);
//			normal3 = Face_Normal_Vector(i, j, (i - 1 + N) % N, j, i, j - 1);
//			normal4 = Face_Normal_Vector(i, j, i, j - 1, (i + 1) % N, j);
//			temp_vector.x = (normal1.x + normal2.x + normal3.x + normal4.x) / 4.0;
//			temp_vector.y = (normal1.y + normal2.y + normal3.y + normal4.y) / 4.0;
//			temp_vector.z = (normal1.z + normal2.z + normal3.z + normal4.z) / 4.0;
//
//			temp_vector = Normalization(temp_vector);
//			normal[i][j][0] = temp_vector.x;
//			normal[i][j][1] = temp_vector.y;
//			normal[i][j][2] = temp_vector.z;
//		}
//	}
//
//	S.x = 0.0;
//	S.y = 0.0;
//	S.z = 0.0;
//	for (int i = 0; i < N; i++) {
//		normal1 = Face_Normal_Vector(i, M, i, M - 1, (i + 1) % N, M - 1);
//		S.x += normal1.x;
//		S.y += normal1.y;
//		S.z += normal1.z;
//	}
//	S = Normalization(S);
//	for (int i = 0; i < N; i++) {
//		normal[i][M][0] = S.x;
//		normal[i][M][1] = S.y;
//		normal[i][M][2] = S.z;
//	}
//}
//
//
//
//void init(void)
//{
//	glShadeModel(GL_SMOOTH);
//	//glShadeModel(GL_FLAT);
//
//	glEnable(GL_DEPTH_TEST);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT1);
//
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
//	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);
//
//	Radius = 1.0;
//	camera_phi = PI / 6.0;
//	//camera_theta = PI / 4.0;
//	camera_theta = 0.0;
//	camera_distance = 4.0 * Radius;
//
//	Vertex_Generation();
//
//	// 아래 함수 Modify_Vertex()를 풀어 적용시켜 봅니다. 
//	Modify_Vertex();
//
//	Vertex_Normal_Computation();
//}
//
//
//
//
//void Draw_Sphere(void) {
//	for (int j = 0; j < M; j++) {
//		for (int i = 0; i < N; i++) {
//			if (draw_type == GL_POLYGON)
//				glBegin(GL_POLYGON);
//			else
//				glBegin(GL_LINE_LOOP);
//
//			glNormal3fv(normal[i][j]);
//			glVertex3fv(ver[i][j]);
//
//			glNormal3fv(normal[(i + 1) % N][j]);
//			glVertex3fv(ver[(i + 1) % N][j]);
//
//			glNormal3fv(normal[(i + 1) % N][j + 1]);
//			glVertex3fv(ver[(i + 1) % N][j + 1]);
//
//			glNormal3fv(normal[i][j + 1]);
//			glVertex3fv(ver[i][j + 1]);
//			glEnd();
//		}
//	}
//}
//
//
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0, 1.0, 1.0, 1000);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void display(void)
//{
//	float	x, y, z;
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//
//	// Camera Position 
//	x = camera_distance * cos(camera_phi) * cos(camera_theta);
//	y = camera_distance * cos(camera_phi) * sin(camera_theta);
//	z = camera_distance * sin(camera_phi);
//
//	/*
//	x = 5.0;
//	y = 0.0;
//	z = 0.0;
//	*/
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	lightPositionR[0] = light_position_x;
//	lightPositionR[1] = light_position_y;
//
//	if (light_camera_type % 2 == 1) {
//		// 카메라 좌표계
//		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR); // (lightPositionR[0], lightPositionR[1], lightPositionR[2]) in Camera Coordinates
//		gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//	}
//	else {
//		// 월드 좌표계
//		gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR); // (lightPositionR[0], lightPositionR[1], lightPositionR[2]) in World Coordinates
//	}
//
//	Draw_Sphere();
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//
//void myMotion(int x, int y)
//{
//	light_position_y += (float)(x - last_x);
//	light_position_x += (float)(y - last_y);
//
//	last_x = x;
//	last_y = y;
//
//	glutPostRedisplay();
//}
//
//
//void myMouse(int button, int button_state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
//		last_x = x;
//		last_y = y;
//	}
//}
//
//void SpecialKey(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_LEFT:		camera_theta -= 0.1;
//		break;
//	case GLUT_KEY_RIGHT:	camera_theta += 0.1;
//		break;
//	case GLUT_KEY_UP:		camera_phi += 0.1;
//		break;
//	case GLUT_KEY_DOWN:		camera_phi -= 0.1;
//		break;
//	default:				break;
//	}
//	if (camera_theta > 2.0 * PI)
//		camera_theta -= (2.0 * PI);
//	else if (camera_theta < 0.0)
//		camera_theta += (2.0 * PI);
//
//}
//
//void MyKey(unsigned char key, int x, int y) {
//	switch (key) {
//	case 'l': 	draw_type = GL_LINE_LOOP;
//		break;
//	case 'p':	draw_type = GL_POLYGON;
//		break;
//
//	case 'a': 	camera_distance += 0.1;
//		break;
//	case 's':	camera_distance -= 0.1;
//		break;
//
//	case '1':	Vertex_Generation();
//		Vertex_Normal_Computation();
//		break;
//	case '2':	
//		// 원만들기
//		Vertex_Generation();
//		// 모양 변형
//		Modify_Vertex();
//		// 법선벡터 구하기
//		Vertex_Normal_Computation();
//		break;
//	case '3':	
//		// 카메라를 월드 or 카메라 좌표계 중 어느것을 쓸것인가?
//		light_camera_type++;
//		break;
//	default:	break;
//	}
//	glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Modified Sphere");
//	glutDisplayFunc(display);
//	glutMouseFunc(myMouse);
//	glutMotionFunc(myMotion);
//	glutSpecialFunc(SpecialKey);
//	glutKeyboardFunc(MyKey);
//	glutReshapeFunc(reshape);
//	glutIdleFunc(display);
//	init();
//	glutMainLoop();
//	return 0;
//}
