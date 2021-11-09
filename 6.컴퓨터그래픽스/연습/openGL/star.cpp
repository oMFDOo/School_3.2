//#include <glut.h>
//#include <gl/gl.h>
//#include <stdio.h>
//#include <math.h>
//
//#define	PI	3.1415926
//
//// 경도, 위도를 나눌 점 n개 설정
//#define N 12
//#define M 6 
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
//float	ver[N][M + 1][3];
//float	sphere_radius = 1.0;
//
//// Camera variables//
//float	camera_theta, camera_phi, camera_radius;
//
//void Vertex_Generation(void) {
//	float	theta, phi;
//	float	delta_theta, delta_phi;
//	float	start_theta, start_phi;
//
//	start_theta = 0.0;
//	delta_theta = 2.0 * PI / N;
//
//	start_phi = -1.0 * PI / 2.0;
//	delta_phi = PI / M;
//
//	for (int j = 0; j <= M; j++) {
//		for (int i = 0; i < N; i++) {
//			theta = start_theta + i * delta_theta;
//			phi = start_phi + j * delta_phi;
//			ver[i][j][0] = sphere_radius * cos(phi) * cos(theta);
//			ver[i][j][1] = sphere_radius * cos(phi) * sin(theta);
//			ver[i][j][2] = sphere_radius * sin(phi);
//		}
//	}
//}
//
//void sphere(void) {
//
//	delta_theta = 2 * PI / N;	// 경도
//	delta_phi = PI / M;			// 위도
//
//	GLfloat ver[N][M + 1][3] = { 0 };
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
//			ver[j][i][0] = vertices[j][i].x;
//			ver[j][i][1] = vertices[j][i].y;
//			ver[j][i][2] = vertices[j][i].z;
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
//			GLfloat temp[1][1][3] = { 0, };
//			if ((vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 < 0) isplus = -1;
//			x = (vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 + 0.2 * isplus;
//			isplus = 1;
//			if ((vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 < 0) isplus = -1;
//			y = (vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 + 0.2 * isplus;
//			isplus = 1;
//			if ((vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 < 0) isplus = -1;
//			z = (vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 + 0.2 * isplus;
//			temp[0][0][0] = x;
//			temp[0][0][1] = y;
//			temp[0][0][2] = z;
//
//			// 각 정점값을 설정하여 그리기
//			glColor3f(1.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// glBegin(GL_LINE_STRIP); // 라인 그리기
//
//			// 구의 표면 사각형 그리기
//			// 좌하단
//			glVertex3fv(ver[j][i]);
//			glVertex3fv(ver[j][i]);
//			// 우하단
//			glVertex3fv(ver[(j + 1) % N][i]);
//			glVertex3fv(ver[(j + 1) % N][i]);
//			// 하단 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//
//			glEnd();
//
//			//glColor3f(0.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 우하단
//			glVertex3fv(ver[(j + 1) % N][i]);
//			glVertex3fv(ver[(j + 1) % N][i]);
//			// 우상단
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			// 우측 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//
//			//glColor3f(0.0, 0.0, 1.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌상단
//			glVertex3fv(ver[j][i + 1]);
//			glVertex3fv(ver[j][i + 1]);
//			// 우상단
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			// 상단 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//
//			//glColor3f(1.0, 0.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌하단
//			glVertex3fv(ver[j][i]);
//			glVertex3fv(ver[j][i]);
//			// 좌상단
//			glVertex3fv(ver[j][i + 1]);
//			glVertex3fv(ver[j][i + 1]);
//			// 좌측 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//		}
//	}
//}
//
//void sphereLine(void) {
//
//	delta_theta = 2 * PI / N;	// 경도
//	delta_phi = PI / M;			// 위도
//
//	GLfloat ver[N][M + 1][3] = { 0 };
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
//			ver[j][i][0] = vertices[j][i].x;
//			ver[j][i][1] = vertices[j][i].y;
//			ver[j][i][2] = vertices[j][i].z;
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
//			GLfloat temp[1][1][3] = { 0, };
//			if ((vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 < 0) isplus = -1;
//			x = (vertices[j][i].x + vertices[(j + 1) % N][i + 1].x) / 2.0 + 0.4 * isplus;
//			isplus = 1;
//			if ((vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 < 0) isplus = -1;
//			y = (vertices[j][i].y + vertices[(j + 1) % N][i + 1].y) / 2.0 + 0.4 * isplus;
//			isplus = 1;
//			if ((vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 < 0) isplus = -1;
//			z = (vertices[j][i].z + vertices[(j + 1) % N][i + 1].z) / 2.0 + 0.4 * isplus;
//			temp[0][0][0] = x;
//			temp[0][0][1] = y;
//			temp[0][0][2] = z;
//
//			// 각 정점값을 설정하여 그리기
//			glColor3f(1.0, 0.7, 0.0);
//			glBegin(GL_LINE_LOOP); // 면 그리기
//			// glBegin(GL_LINE_STRIP); // 라인 그리기
//
//			// 구의 표면 사각형 그리기
//			// 좌하단
//			glVertex3fv(ver[j][i]);
//			glVertex3fv(ver[j][i]);
//			// 우하단
//			glVertex3fv(ver[(j + 1) % N][i]);
//			glVertex3fv(ver[(j + 1) % N][i]);
//			// 하단 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//
//			glEnd();
//
//			//glColor3f(0.0, 1.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 우하단
//			glVertex3fv(ver[(j + 1) % N][i]);
//			glVertex3fv(ver[(j + 1) % N][i]);
//			// 우상단
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			// 우측 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//
//			//glColor3f(0.0, 0.0, 1.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌상단
//			glVertex3fv(ver[j][i + 1]);
//			glVertex3fv(ver[j][i + 1]);
//			// 우상단
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			glVertex3fv(ver[(j + 1) % N][i + 1]);
//			// 상단 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//
//			//glColor3f(1.0, 0.0, 0.0);
//			glBegin(GL_POLYGON); // 면 그리기
//			// 좌하단
//			glVertex3fv(ver[j][i]);
//			glVertex3fv(ver[j][i]);
//			// 좌상단
//			glVertex3fv(ver[j][i + 1]);
//			glVertex3fv(ver[j][i + 1]);
//			// 좌측 뿔
//			glVertex3fv(temp[0][0]);
//			glVertex3fv(temp[0][0]);
//			glEnd();
//		}
//	}
//}
//
//// 입체적으로로 보기위한 조명 처리
///* 왜 저는 교수님처럼 예쁜 조명이 안 될까요 */
//float   light0_position[] = { 1.0, 0.0, 1.0, 1.0 };
//float   light0_ambient[] = { 0.8, 0.0, 1.0, 1.0 };	// 주변광
//float   light0_diffuse[] = { 0.7, 0.7, 0.2, 1.0 };	// 분산광
//float   light0_specular[] = { 0.7, 0.5, 0.0, 1.0 };	// 반사광
//
//void light() {
//
//
//	// 쉐이드 모델 설정 
//	//glShadeModel(GL_FLAT);		// 각 면이 확실히 구분되어 랜더링 됨
//	glShadeModel(GL_SMOOTH); // 부드럽게 랜더링 됨
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
//
//	GLfloat arMat1[] = { 1.0, 1.0, 0.0, 1.0 };
//	glMaterialfv(GL_FRONT, GL_AMBIENT, arMat1);
//}
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
//	glClearColor(0.0, 0.0, 0.1, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void camera(void) {
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//}
//
//
//void display(void)
//{
//	frame_reset();
//
//	camera();
//	light(); 
//	sphere();
//
//	glFlush();
//	glutSwapBuffers();
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
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//	return 0;
//}
