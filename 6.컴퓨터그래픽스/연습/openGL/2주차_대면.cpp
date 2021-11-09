//#include <glut.h>
//#include <gl/gl.h>
//#include <stdio.h>
//#include <math.h>
//
//#define	PI	3.1415926
//
//// 경도, 위도를 나눌 점 n개 설정
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
//double theta;				// 경도
//double phi;					// 위도
//double delta_theta;			// 경도를 n개로 분할함
//double delta_phi;			// 위도를 n개로 분할함
//Point3D vertices[N][M + 1];	// 정점 저장
//
//// Camera variables//
//float	camera_theta, camera_phi, camera_radius;
//
//void sphere(void) {
//
//	delta_theta = 2 * PI / N;	// 경도
//	delta_phi = PI / M;			// 위도
//
//	// 각 정점 값 설정 : 위도 기준으로 모든 경도의 값을 설정
//	// ()의 형태로 각 점의 위치를 저장한다.
//	// 이 때 종료점 표현을 위해 'j는 위도의 값이 일치할 때까지'로 설정한다.
//	for (int i = 0; i <= M; i++) {
//		for (int j = 0; j < N; j++) {
//			// 각 위/경도에 따른 델타, 파이값 설정
//			theta = j * delta_theta;
//			phi = i * delta_phi - (PI / 2.0);
//
//			// 삼각함수에 따른 각 점의 위치 구하기
//			vertices[j][i].x = R * cos(theta) * cos(phi);
//			vertices[j][i].y = R * sin(theta) * cos(phi);
//			vertices[j][i].z = R * sin(phi);
//		}
//	}
//
//	for (int i = 0; i < M; i++) {
//		for (int j = 0; j < N; j++) {
//			// 각 위/경도에 맞는 델타, 파이값 설정
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
//			// 각 정점값을 설정하여 그리기
//			glColor3f(1.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//		    // glBegin(GL_LINE_STRIP); // 라인 그리기
//
//		    // 구의 표면 사각형 그리기
//		    // 좌하단
//			glVertex3f(vertices[j][i].x, vertices[j][i].y, vertices[j][i].z);
//			// 우하단
//			glVertex3f(vertices[(j + 1) % N][i].x, vertices[(j + 1) % N][i].y, vertices[(j + 1) % N][i].z);
//			// 하단 뿔
//			glVertex3f(x, y, z);
//
//			glEnd();
//
//			glColor3f(0.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 우하단
//			glVertex3f(vertices[(j + 1) % N][i].x, vertices[(j + 1) % N][i].y, vertices[(j + 1) % N][i].z);
//			// 우상단
//			glVertex3f(vertices[(j + 1) % N][i + 1].x, vertices[(j + 1) % N][i + 1].y, vertices[(j + 1) % N][i + 1].z);
//
//			// 우측 뿔
//			glVertex3f(x, y, z);
//
//			glEnd();
//			glColor3f(0.0, 0.0, 1.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌상단
//			glVertex3f(vertices[j][i + 1].x, vertices[j][i + 1].y, vertices[j][i + 1].z);
//			// 우상단
//			glVertex3f(vertices[(j + 1) % N][i + 1].x, vertices[(j + 1) % N][i + 1].y, vertices[(j + 1) % N][i + 1].z);
//
//			// 상단 뿔
//			glVertex3f(x, y, z);
//
//			glEnd();
//
//			glColor3f(1.0, 0.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌하단
//			glVertex3f(vertices[j][i].x, vertices[j][i].y, vertices[j][i].z);
//			// 좌상단
//			glVertex3f(vertices[j][i + 1].x, vertices[j][i + 1].y, vertices[j][i + 1].z);
//			
//			// 좌측 뿔
//			glVertex3f(x, y, z);
//			glEnd();
//		}
//	}
//}
//
//
//// 입체적으로로 보기위한 조명 처리
///* 왜 저는 교수님처럼 예쁜 조명이 안 될까요 */
//float   light0_position[] = { 2.8, 1.0, -1.5, 1.0 };
//float   light0_ambient[] = { 2.0, 1.0, 1.5, 1.0 };	// 주변광
//float   light0_diffuse[] = { 2.0, 1.0, 1.5, 1.0 };	// 분산광
//float   light0_specular[] = { 2.0, 1.0, 1.5, 1.0 };	// 반사광
//
//void init(void) {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//
//	camera_theta = 0.0;
//	camera_phi = 0.0;
//	camera_radius = 3.2;
//
//	// 깊이 테스트 실행
//	glEnable(GL_DEPTH_TEST);
//
//	// 쉐이드 모델 설정 
//	glShadeModel(GL_FLAT);		// 각 면이 확실히 구분되어 랜더링 됨
//	// glShadeModel(GL_SMOOTH); // 부드럽게 랜더링 됨
//	
//	glEnable(GL_COLOR_MATERIAL);
//
//	// 깊이 테스트 실행 및 조명 활성화
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	// 커스텀 조명값 적용
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
//	glColor3f(1.0, 0.0, 0.0); // x축 
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(100.0, 0.0, 0.0);
//
//	glColor3f(0.0, 1.0, 0.0); // y축 
//	glLineWidth(8.0);
//	glVertex3f(0.0, 0.0, 0.0);
//	glVertex3f(0.0, 100.0, 0.0);
//
//	glColor3f(0.0, 0.0, 1.0); // z축 
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
//	// 줌을 이렇게 하는 거였구나...
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
//	glutCreateWindow("draw sphere 20193148-황진주");
//	init();
//	glutDisplayFunc(display);
//	glutSpecialFunc(special_key);
//	glutKeyboardFunc(my_key);
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//	return 0;
//}
