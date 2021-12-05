#define _CRT_SECURE_NO_WARNINGS  //비쥬얼 스투디오 2015 이상의 버전에서 scanf같은 것을 쓰게 해주는 것

#include "dib.h"
#include "GL/glut.h"
#include "math.h"
#include "Camera.h"
#include "intro.h"
#include <stdio.h>
#include <time.h>

double jump = 0.0;
clock_t jumpStart, jumpIng;
double jumpTime = 0.0;
int isjump = 0;

Camera cam;
float h = 0.25; //점프를 위한 공용 변수
float a = 0.01f;//점프를 위한 공용 변수


float userT = 0; //유저 기본 속도 조절 변수
float userMove = 0; //유저 위치 변수
float userSpeed = 0; //유저 유동 속도 조절 변수

float enemyT1 = 0; //적1 기본 속도 조절 변수
float enemy1Speed = 0; //적 1 유동 속도 조절 변수

float enemyT2 = 0; //적2 속도 조절 변수
float enemy2Speed = 0; //적 2 유동 속도 조절 변수

float enemyT3 = 0; //적3 속도 조절 변수
float enemy3Speed = 0; //적 3 유동 속도 조절 변수

float enemyT4 = 0; //적4 속도 조절 변수
float enemy4Speed = 0; //적 4 유동 속도 조절 변수

GLUquadricObj* cyl;	//곡선이 들어간 오브젝트
GLUquadricObj* cylTree;	//곡선이 들어간 오브젝트

GLfloat eyeX = 0, eyeY = 0, eyeZ = 0; //카메라의 시점 변경을 위한 변수
GLfloat initX = 0, initY = 0;   //마우스 클릭 했을때의 초기 위치
GLfloat delta = 0.1;            //마우스 움직일시 시점 변경을 위한 변수
GLfloat zzz = 1;   //카메라 시점 변경을 위한 변수
GLfloat aaa = 0.1; //카메라 시점 변경을 위한 변수


void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);  //클릭한 점을 기준으로
void MyMouseMove(GLint X, GLint Y); //카메라의 위치를 변환 시킴
void InitLight(); //조명 
void MyIdle(); //아이들
void MyKeyboard(unsigned char KeyPressed, int X, int Y); //키보드
void MyDisplay();
void MySpecial(int key, int x, int y); //특수키 키보드
void MyInit(); //텍스쳐 사용 함수

void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed);
// 사람 만들어주는 함수,   a 위치 조정, rgb,  pibo 피부 색깔 조정, 각 케릭터마다 기본 속도 조절, 유동 속도 조절

void userSet(float a, float r, float g, float b); // 유저용
void enemySetSpeed(); //적들 속도 랜덤하게 부여
void finishLine();  //피니시 라인 달리기 끝에 줄
void board(); //바닥 판
void tree1(); //나무1
void tree2(); //나무2
void gameOverCheck(float lotate, char* player); //게임 오버 체크

int main(int argc, char** argv)
{
	intro_start();  //헤더파일 intro에 있는 게임 설명 cmd창을 보여주는 함수

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(800, 200);

	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//현재행렬 단위행렬로 초기화
	gluPerspective(20, 1, 0.1, 1000);

	//사용전에 카메라 초기화를 먼저 해줘야 함
	//gluLookAt
	cam.set(0, 8, 9,	//눈의 좌표
		0, 0, 0,	//바라보는 점
		0, 1, 0);	//업벡터 

	InitLight(); //조명 초기화
	MyInit();

	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutMainLoop();

	return 0;
}

/*
 * MyDisplay
 */
void MyDisplay()
{
	float mat_diffuse1[4] = { 0.1, 0.4, 0.6, 1 }; // 추가  사람 색깔
	float mat_diffuse2[4] = { 1.0, 1.0 ,0.7, 1 }; // 추가  옷 색깔


	// 점프 하기
	jumpIng = clock();
	// printf("%d\n", jumpIng - jumpStart);
	
	// 올라가기
	if (isjump && jumpIng - jumpStart < 1500) {
		jump += 0.002;
	}
	// 내려가기
	if (isjump && jumpIng - jumpStart >= 1500 && jumpIng - jumpStart < 3000) {
		if (jump - 0.002 > 0) {
			jump += -0.002;
		}
	}
	// 점프종료
	if (isjump && jumpIng - jumpStart >= 3000) {
		isjump = 0;
		jump = 0.0;
	}
	

	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);	//면으로 그려줘

	cylTree = gluNewQuadric();
	gluQuadricDrawStyle(cylTree, GLU_FILL);	//면으로 그려줘

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//finish line
	glDisable(GL_LIGHTING);	//조명 껏다가
	glPushMatrix();
	finishLine();
	glPopMatrix();
	glEnable(GL_LIGHTING); // 다시 킴

	//바닥	
	glDisable(GL_LIGHTING);	//조명 껏다가
	glPushMatrix();
	board();
	glPopMatrix();
	glEnable(GL_LIGHTING); // 다시 킴

	//나무 1
	glPushMatrix();
	tree1();
	glPopMatrix();
	//나무 2
	glPushMatrix();
	tree2();
	glPopMatrix();

	//user
	userSet(0, 0.1, 0.4, 0.6);
	enemySetSpeed();	//랜덤하게 각 적들 속도 조절
	//enemy 1
	enemySet(-0.7, 0.3, 0.3, 0, 0.5, enemyT1, enemy1Speed);
	//enemy 2
	enemySet(-1.4, 0, 0.3, 0.3, 0.5, enemyT2, enemy2Speed);
	//enemy 3
	enemySet(0.7, 0.3, 0, 0.3, 0.5, enemyT3, enemy3Speed);
	//enemy 4
	enemySet(1.4, 0.0, 0.0, 0.0, 0.5, enemyT4, enemy4Speed);

	glFlush();
	glutPostRedisplay();      //윈도우를 다시 그리도록 요청
}

/*
 * game configure
 */
void gameOverCheck(float lotate, char* player)
{
	//z== -18
	if (lotate < -18)
	{
		system("cls");
		printf("@@@@@@@@@@@@@@@@@@@   %s가 승리하였습니다.  @@@@@@@@@@@@@@@@@@@@\n", player);
		exit(1);
	}
}
void enemySetSpeed()
{
	//적들의 속도를 랜덤하게 부여함
	srand((int)time(NULL));

	int k = (rand() % 15) + 1;
	float random = (rand() % 10) + 1;
	enemy1Speed = random * 0.00015 * k;

	k = (rand() % 20) + 1;
	random = (rand() % 10) + 1;
	enemy2Speed = random * 0.00015 * k;

	k = (rand() % 25) + 1;
	random = (rand() % 10) + 1;
	enemy3Speed = random * 0.00015 * k;

	k = (rand() % 10) + 1;
	random = (rand() % 10) + 1;
	enemy4Speed = random * 0.00015 * k;
}
void tree1()
{
	float mat_diffuse1[4] = { 0.8, 0.6, 0.2, 1 }; // 나무 몸통
	float mat_diffuse2[4] = { 0.1, 1.0, 0.1, 1 }; // 나뭇잎

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
	glTranslatef(-3, -0.5, -18);
	glRotatef(270, 1, 0, 0);
	gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
	glTranslatef(0.0, 0, 2.0);
	gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
}
void tree2()
{
	float mat_diffuse1[4] = { 0.8, 0.6, 0.2, 1 }; // 나무 몸통
	float mat_diffuse2[4] = { 0.1, 1.0, 0.1, 1 }; // 나뭇잎

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
	glTranslatef(3, -0.5, -18);
	glRotatef(270, 1, 0, 0);
	gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
	glTranslatef(0.0, 0, 2.0);
	gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
}
void finishLine()
{
	glTranslatef(0.0, 0.5, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//텍스쳐는 0에서 1까지
	//앞에것이 텍스쳐 좌표,  오른쪽이 gl의 물체 좌표
	//텍스쳐의 각각의 정점을 대응해서 물체에 붙임
	//1보다 큰 값을 줄 시 gl이 픽셀을 그냥 쭉 연장시킴
	//glColor3f(0.0, 0.0, 0.4);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -17.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -17.8);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -17.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, -17.8);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.4, 0.7);
	glVertex3f(-3, -0.2, -18.0);
	glVertex3f(3, -0.2, -18.0);
	glVertex3f(3, 0.2, -18.0);
	glVertex3f(-3, 0.2, -18.0);
	glEnd();
}


void board()
{
	glColor3f(0.3, 0.4, 0.0);
	glTranslatef(0.0, -0.9, -13.0);
	glScalef(5, 0.3, 15);	//scale로 넓혀서 바닥을 만들었음, 빨간게 정육면체인데 scale로 넓혀서 바닥모양처럼됨
	glutSolidCube(2.0);
}
void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed)
{


	float mat_diffuse1[4] = { r, g, b, 1 }; // 옷 색깔
	float mat_diffuse2[4] = { 1.0, 1.0, 0.7 + pibo, 1 }; // 사람 색깔은 고정

	//게임 오버 구현
	char temp[10] = { 0,};
	strcpy(temp, "Enemy 1");
	gameOverCheck(-0.1 * enemyT1 + enemy1Speed, temp);
	strcpy(temp, "Enemy 2");
	gameOverCheck(-0.1 * enemyT2 + enemy2Speed, temp);
	strcpy(temp, "Enemy 3");
	gameOverCheck(-0.1 * enemyT3 + enemy3Speed, temp);
	strcpy(temp, "Enemy 4");
	gameOverCheck(-0.1 * enemyT4 + enemy4Speed, temp);

	//Enemy
	glPushMatrix();
	glTranslatef(a, (sin(t * 00.1) + 1) / 6 + jump - 0.2, -0.1 * t + enemySpeed);
	// 1. 몸통
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.27, 0.1, 0.6, 20, 1);
	glRotatef(90, 1, 0, 0);
	// 1. 머리
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
	glTranslatef(0, 0.65, 0);
	glutSolidSphere(0.3, 20, 20);

	// 모자 챙
	glPushMatrix();
	glTranslatef(0.0, 0.10, 0.12);
	glRotatef(-50, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, 0.45, 0.01, 0.3, 20, 1);

	// 모자 뿔
	glPushMatrix();
	glutSolidCone(0.3, 0.7, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. 왼팔
	glPushMatrix();
	glTranslatef(-0.2, 0.35, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(t * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. 팔꿈치부터 안에 팔
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(t * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();

	// 1. 오른팔
	glPushMatrix();
	glTranslatef(0.2, 0.35, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-t * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. 팔꿈치부터 안에 팔
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-t * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. 다리, 엉덩이
	// 왼쪽 다리
	glPushMatrix();
	glTranslatef(-0.07, 0, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-t * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//왼쪽 발바닥
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// 오른쪽 다리
	glPushMatrix();
	glTranslatef(0.07, 0, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(t * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//오른쪽 발바닥
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//몸통 종료
	glPopMatrix();	//사람 종료
}
void userSet(float a, float r, float g, float b)
{
	float mat_diffuse1[4] = { r, g, b, 1 }; // 옷 색깔
	float mat_diffuse2[4] = { 1.0, 1.0, 0.7, 1 }; // 사람 색깔은 고정



	//게임 오버 체크!!
	char temp[5];
	strcpy(temp, "User");
	gameOverCheck(-0.1 + userMove, temp);

	glPushMatrix();
	glTranslatef(a, (sin(userT * 00.1) + 1) / 6, -0.1 + userMove);
	// 1. 몸통
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.17, 0.1, 0.5, 20, 1);
	glRotatef(90, 1, 0, 0);
	// 1. 머리
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
	glTranslatef(0, 0.65, 0);
	glutSolidSphere(0.2, 20, 20);

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. 왼팔
	glPushMatrix();
	glTranslatef(-0.15, 0.5, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. 팔꿈치부터 안에 팔
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();

	// 1. 오른팔
	glPushMatrix();
	glTranslatef(0.15, 0.5, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. 팔꿈치부터 안에 팔
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. 다리, 엉덩이
	// 왼쪽 다리
	glPushMatrix();
	glTranslatef(-0.07, 0, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//무릎
	glPushMatrix();
	glTranslatef(0, 0.0, 0.3);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 - 45, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.05, 0.3, 20, 1);
	//왼쪽 발바닥
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// 오른쪽 다리
	glPushMatrix();
	glTranslatef(0.07, 0, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//무릎
	glPushMatrix();
	glTranslatef(0, 0.0, 0.3);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 - 45, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.05, 0.3, 20, 1);
	//오른쪽 발바닥
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//몸통 종료
	glPopMatrix();	//사람 종료
}

/*
 * glutFunk
 */
void MyIdle()
{
	//각 케릭터의 속도 조절
	enemyT1 += 0.012f; //기본 속도
	enemyT1 += enemy1Speed; //추가 된 속도

	enemyT2 += 0.013f; //기본 속도
	enemyT2 += enemy2Speed; //추가 된 속도

	enemyT3 += 0.011f; //기본 속도
	enemyT3 += enemy3Speed; //추가 된 속도

	enemyT4 += 0.014f; //기본 속도
	enemyT4 += enemy4Speed; //추가 된 속도

	userT += 0.01f; //유저의 기본 속도
	userT += userSpeed; //추가 된 속도


	//게임의 재미를 위해 유저의 속도가 자동으로 어느정도 떨어지게 만듬
	userMove -= userSpeed * 0.1;
	//속도가 0보다 작을 수 없음
	if (userSpeed > 0)
	{
		userSpeed -= 0.00002;
	}


	//뛰어가는 모습을 자연스럽게 하기 위해서 뛰어가는 모습중 어느 정도 위아래로 움직이게 만듬
	if (h <= 0.25)
		a = +0.001f;
	if (h >= 0.75)
	{
		a = -0.001f;
	}
	h = h + a;
	
	//카메라도 어느정도 빠르게 자동으로 앞으로 가게 만듬
	aaa -= 0.002;
	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
		0, 0, 0 + aaa,	//바라보는 점
		0, 1, 0);	//업벡터 

	glutPostRedisplay();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{
	switch (KeyPressed)
	{
	case 'w': case 'W':  //y축 위로
		eyeY += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 's': case 'S':  //y축 밑으로
		eyeY += -0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 'a': case 'A': //z축 앞으로
		aaa -= 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 'd': case 'D': //z축 뒤로
		aaa += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;

	case 32:
		isjump = 1;
		jumpStart = clock(); // 시간 측정 시작
		break;
	}
	glutPostRedisplay();
}

int con = 1; //한키만 누르고 있으면 재미 없으니까 왔다갔다 하며 누르게 만듬
void MySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (con == 1)
		{
			userSpeed += 0.001;
			con = 0;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (con == 0)
		{
			userSpeed += 0.001;
			con = 1;
		}
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_UP:
		break;
	}
	

	glutPostRedisplay();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)  //클릭한 점을 기준으로
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		initX = X;
	}
}
void MyMouseMove(GLint X, GLint Y) //카메라의 위치를 변환 시킴
{
	if (X > initX)
	{
		eyeX -= delta;
		eyeZ -= delta * zzz;
	}
	if (X < initX)
	{
		eyeX += delta;
		eyeZ += delta * zzz;
	}
	if (eyeX > 12)
	{
		eyeX = 12;
	}
	if (eyeX < -10)
	{
		eyeX = -10;
	}
	if (eyeZ > 10)
	{
		eyeZ = 10;
	}
	if (eyeZ < -8)
	{
		eyeZ = -8;
	}

	if (eyeZ > 2)
	{
		zzz *= -1;
	}

	//printf("%lf, %lf, %lf\n", eyeX, eyeY, eyeZ);
	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
		0, 0, 0 + aaa,	//바라보는 점
		0, 1, 0);	//업벡터 

	glutPostRedisplay();
}


/*
 * light (조명)
 */
void InitLight()
{
	GLfloat mat_diffuse[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_specular[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	//0번 조명
	GLfloat light_specular[] = { 1.0, 0.2, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.4, 0.3, 0.3, 1.0 };

	GLfloat light_position[] = { -3, 10, 3.0, 0.0 };	//조명 위치 할당,  태양처럼 위에서 아래로 내려 쬠

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


/*
 * 텍스쳐
 */
void MyInit()
{
	MyDib dib; //  && 선언
	char filename[20] = { 0, };
	strcpy(filename, "choi.bmp");
	dib.ReadBMP(filename); // && 그림 파일 리드
	dib.m_lpImage; // &&  데이터의 시작 주소
	glTexImage2D(GL_TEXTURE_2D, 0, 3, dib.GetWidth(), dib.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, dib.m_lpImage);
	// && 텍스쳐 그림에 사용     이 세줄이 핵심!  -> 텍스쳐 사용법,  나머지는 좌표만 맞추면 됨

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dib.GetWidth(), dib.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, dib.m_lpImage); //mip map을 만들어줌

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // GL_REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // GL_REPEAT

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//확장관계일때 양방향 선형 보간
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //mip map을 사용하면 비용은 많이들지만 품질이 좋아짐
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//환경에 대한 설정,  텍스쳐가 지엘 덮었을때 원래 물체를 없앨건지?,  섞을건지,   modulate 섞어줌
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //GL_DECAL,GL_REPLACE, GL_MODULATE


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, 가로방향이 s,  텍스쳐가 만약 좌표가 짤려도 반복해서 갖다 붙임 = REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_REPEAT, 세로방향이 t,  텍스쳐가 만약 좌표가 짤려도 반복해서 갖다 붙임 = REPEAT
}

/*
 * capyright  1392056  kim jun hee
 */