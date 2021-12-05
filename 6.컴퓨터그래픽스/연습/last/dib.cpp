#define _CRT_SECURE_NO_WARNINGS  //����� ������� 2015 �̻��� �������� scanf���� ���� ���� ���ִ� ��

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
float h = 0.25; //������ ���� ���� ����
float a = 0.01f;//������ ���� ���� ����


float userT = 0; //���� �⺻ �ӵ� ���� ����
float userMove = 0; //���� ��ġ ����
float userSpeed = 0; //���� ���� �ӵ� ���� ����

float enemyT1 = 0; //��1 �⺻ �ӵ� ���� ����
float enemy1Speed = 0; //�� 1 ���� �ӵ� ���� ����

float enemyT2 = 0; //��2 �ӵ� ���� ����
float enemy2Speed = 0; //�� 2 ���� �ӵ� ���� ����

float enemyT3 = 0; //��3 �ӵ� ���� ����
float enemy3Speed = 0; //�� 3 ���� �ӵ� ���� ����

float enemyT4 = 0; //��4 �ӵ� ���� ����
float enemy4Speed = 0; //�� 4 ���� �ӵ� ���� ����

GLUquadricObj* cyl;	//��� �� ������Ʈ
GLUquadricObj* cylTree;	//��� �� ������Ʈ

GLfloat eyeX = 0, eyeY = 0, eyeZ = 0; //ī�޶��� ���� ������ ���� ����
GLfloat initX = 0, initY = 0;   //���콺 Ŭ�� �������� �ʱ� ��ġ
GLfloat delta = 0.1;            //���콺 �����Ͻ� ���� ������ ���� ����
GLfloat zzz = 1;   //ī�޶� ���� ������ ���� ����
GLfloat aaa = 0.1; //ī�޶� ���� ������ ���� ����


void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);  //Ŭ���� ���� ��������
void MyMouseMove(GLint X, GLint Y); //ī�޶��� ��ġ�� ��ȯ ��Ŵ
void InitLight(); //���� 
void MyIdle(); //���̵�
void MyKeyboard(unsigned char KeyPressed, int X, int Y); //Ű����
void MyDisplay();
void MySpecial(int key, int x, int y); //Ư��Ű Ű����
void MyInit(); //�ؽ��� ��� �Լ�

void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed);
// ��� ������ִ� �Լ�,   a ��ġ ����, rgb,  pibo �Ǻ� ���� ����, �� �ɸ��͸��� �⺻ �ӵ� ����, ���� �ӵ� ����

void userSet(float a, float r, float g, float b); // ������
void enemySetSpeed(); //���� �ӵ� �����ϰ� �ο�
void finishLine();  //�ǴϽ� ���� �޸��� ���� ��
void board(); //�ٴ� ��
void tree1(); //����1
void tree2(); //����2
void gameOverCheck(float lotate, char* player); //���� ���� üũ

int main(int argc, char** argv)
{
	intro_start();  //������� intro�� �ִ� ���� ���� cmdâ�� �����ִ� �Լ�

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(800, 200);

	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//������� ������ķ� �ʱ�ȭ
	gluPerspective(20, 1, 0.1, 1000);

	//������� ī�޶� �ʱ�ȭ�� ���� ����� ��
	//gluLookAt
	cam.set(0, 8, 9,	//���� ��ǥ
		0, 0, 0,	//�ٶ󺸴� ��
		0, 1, 0);	//������ 

	InitLight(); //���� �ʱ�ȭ
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
	float mat_diffuse1[4] = { 0.1, 0.4, 0.6, 1 }; // �߰�  ��� ����
	float mat_diffuse2[4] = { 1.0, 1.0 ,0.7, 1 }; // �߰�  �� ����


	// ���� �ϱ�
	jumpIng = clock();
	// printf("%d\n", jumpIng - jumpStart);
	
	// �ö󰡱�
	if (isjump && jumpIng - jumpStart < 1500) {
		jump += 0.002;
	}
	// ��������
	if (isjump && jumpIng - jumpStart >= 1500 && jumpIng - jumpStart < 3000) {
		if (jump - 0.002 > 0) {
			jump += -0.002;
		}
	}
	// ��������
	if (isjump && jumpIng - jumpStart >= 3000) {
		isjump = 0;
		jump = 0.0;
	}
	

	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);	//������ �׷���

	cylTree = gluNewQuadric();
	gluQuadricDrawStyle(cylTree, GLU_FILL);	//������ �׷���

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//finish line
	glDisable(GL_LIGHTING);	//���� ���ٰ�
	glPushMatrix();
	finishLine();
	glPopMatrix();
	glEnable(GL_LIGHTING); // �ٽ� Ŵ

	//�ٴ�	
	glDisable(GL_LIGHTING);	//���� ���ٰ�
	glPushMatrix();
	board();
	glPopMatrix();
	glEnable(GL_LIGHTING); // �ٽ� Ŵ

	//���� 1
	glPushMatrix();
	tree1();
	glPopMatrix();
	//���� 2
	glPushMatrix();
	tree2();
	glPopMatrix();

	//user
	userSet(0, 0.1, 0.4, 0.6);
	enemySetSpeed();	//�����ϰ� �� ���� �ӵ� ����
	//enemy 1
	enemySet(-0.7, 0.3, 0.3, 0, 0.5, enemyT1, enemy1Speed);
	//enemy 2
	enemySet(-1.4, 0, 0.3, 0.3, 0.5, enemyT2, enemy2Speed);
	//enemy 3
	enemySet(0.7, 0.3, 0, 0.3, 0.5, enemyT3, enemy3Speed);
	//enemy 4
	enemySet(1.4, 0.0, 0.0, 0.0, 0.5, enemyT4, enemy4Speed);

	glFlush();
	glutPostRedisplay();      //�����츦 �ٽ� �׸����� ��û
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
		printf("@@@@@@@@@@@@@@@@@@@   %s�� �¸��Ͽ����ϴ�.  @@@@@@@@@@@@@@@@@@@@\n", player);
		exit(1);
	}
}
void enemySetSpeed()
{
	//������ �ӵ��� �����ϰ� �ο���
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
	float mat_diffuse1[4] = { 0.8, 0.6, 0.2, 1 }; // ���� ����
	float mat_diffuse2[4] = { 0.1, 1.0, 0.1, 1 }; // ������

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
	glTranslatef(-3, -0.5, -18);
	glRotatef(270, 1, 0, 0);
	gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
	glTranslatef(0.0, 0, 2.0);
	gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
}
void tree2()
{
	float mat_diffuse1[4] = { 0.8, 0.6, 0.2, 1 }; // ���� ����
	float mat_diffuse2[4] = { 0.1, 1.0, 0.1, 1 }; // ������

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
	glTranslatef(3, -0.5, -18);
	glRotatef(270, 1, 0, 0);
	gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
	glTranslatef(0.0, 0, 2.0);
	gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
}
void finishLine()
{
	glTranslatef(0.0, 0.5, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//�ؽ��Ĵ� 0���� 1����
	//�տ����� �ؽ��� ��ǥ,  �������� gl�� ��ü ��ǥ
	//�ؽ����� ������ ������ �����ؼ� ��ü�� ����
	//1���� ū ���� �� �� gl�� �ȼ��� �׳� �� �����Ŵ
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
	glScalef(5, 0.3, 15);	//scale�� ������ �ٴ��� �������, ������ ������ü�ε� scale�� ������ �ٴڸ��ó����
	glutSolidCube(2.0);
}
void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed)
{


	float mat_diffuse1[4] = { r, g, b, 1 }; // �� ����
	float mat_diffuse2[4] = { 1.0, 1.0, 0.7 + pibo, 1 }; // ��� ������ ����

	//���� ���� ����
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
	// 1. ����
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.27, 0.1, 0.6, 20, 1);
	glRotatef(90, 1, 0, 0);
	// 1. �Ӹ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
	glTranslatef(0, 0.65, 0);
	glutSolidSphere(0.3, 20, 20);

	// ���� ì
	glPushMatrix();
	glTranslatef(0.0, 0.10, 0.12);
	glRotatef(-50, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, 0.45, 0.01, 0.3, 20, 1);

	// ���� ��
	glPushMatrix();
	glutSolidCone(0.3, 0.7, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. ����
	glPushMatrix();
	glTranslatef(-0.2, 0.35, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(t * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. �Ȳ�ġ���� �ȿ� ��
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(t * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();

	// 1. ������
	glPushMatrix();
	glTranslatef(0.2, 0.35, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-t * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. �Ȳ�ġ���� �ȿ� ��
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-t * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. �ٸ�, ������
	// ���� �ٸ�
	glPushMatrix();
	glTranslatef(-0.07, 0, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-t * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//���� �߹ٴ�
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// ������ �ٸ�
	glPushMatrix();
	glTranslatef(0.07, 0, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(t * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//������ �߹ٴ�
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//���� ����
	glPopMatrix();	//��� ����
}
void userSet(float a, float r, float g, float b)
{
	float mat_diffuse1[4] = { r, g, b, 1 }; // �� ����
	float mat_diffuse2[4] = { 1.0, 1.0, 0.7, 1 }; // ��� ������ ����



	//���� ���� üũ!!
	char temp[5];
	strcpy(temp, "User");
	gameOverCheck(-0.1 + userMove, temp);

	glPushMatrix();
	glTranslatef(a, (sin(userT * 00.1) + 1) / 6, -0.1 + userMove);
	// 1. ����
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.17, 0.1, 0.5, 20, 1);
	glRotatef(90, 1, 0, 0);
	// 1. �Ӹ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
	glTranslatef(0, 0.65, 0);
	glutSolidSphere(0.2, 20, 20);

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. ����
	glPushMatrix();
	glTranslatef(-0.15, 0.5, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. �Ȳ�ġ���� �ȿ� ��
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();

	// 1. ������
	glPushMatrix();
	glTranslatef(0.15, 0.5, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//2. �Ȳ�ġ���� �ȿ� ��
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. �ٸ�, ������
	// ���� �ٸ�
	glPushMatrix();
	glTranslatef(-0.07, 0, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//����
	glPushMatrix();
	glTranslatef(0, 0.0, 0.3);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 - 45, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.05, 0.3, 20, 1);
	//���� �߹ٴ�
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// ������ �ٸ�
	glPushMatrix();
	glTranslatef(0.07, 0, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//����
	glPushMatrix();
	glTranslatef(0, 0.0, 0.3);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 - 45, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.05, 0.3, 20, 1);
	//������ �߹ٴ�
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(1, 2.3, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//���� ����
	glPopMatrix();	//��� ����
}

/*
 * glutFunk
 */
void MyIdle()
{
	//�� �ɸ����� �ӵ� ����
	enemyT1 += 0.012f; //�⺻ �ӵ�
	enemyT1 += enemy1Speed; //�߰� �� �ӵ�

	enemyT2 += 0.013f; //�⺻ �ӵ�
	enemyT2 += enemy2Speed; //�߰� �� �ӵ�

	enemyT3 += 0.011f; //�⺻ �ӵ�
	enemyT3 += enemy3Speed; //�߰� �� �ӵ�

	enemyT4 += 0.014f; //�⺻ �ӵ�
	enemyT4 += enemy4Speed; //�߰� �� �ӵ�

	userT += 0.01f; //������ �⺻ �ӵ�
	userT += userSpeed; //�߰� �� �ӵ�


	//������ ��̸� ���� ������ �ӵ��� �ڵ����� ������� �������� ����
	userMove -= userSpeed * 0.1;
	//�ӵ��� 0���� ���� �� ����
	if (userSpeed > 0)
	{
		userSpeed -= 0.00002;
	}


	//�پ�� ����� �ڿ������� �ϱ� ���ؼ� �پ�� ����� ��� ���� ���Ʒ��� �����̰� ����
	if (h <= 0.25)
		a = +0.001f;
	if (h >= 0.75)
	{
		a = -0.001f;
	}
	h = h + a;
	
	//ī�޶� ������� ������ �ڵ����� ������ ���� ����
	aaa -= 0.002;
	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
		0, 0, 0 + aaa,	//�ٶ󺸴� ��
		0, 1, 0);	//������ 

	glutPostRedisplay();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{
	switch (KeyPressed)
	{
	case 'w': case 'W':  //y�� ����
		eyeY += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 's': case 'S':  //y�� ������
		eyeY += -0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 'a': case 'A': //z�� ������
		aaa -= 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 'd': case 'D': //z�� �ڷ�
		aaa += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;

	case 32:
		isjump = 1;
		jumpStart = clock(); // �ð� ���� ����
		break;
	}
	glutPostRedisplay();
}

int con = 1; //��Ű�� ������ ������ ��� �����ϱ� �Դٰ��� �ϸ� ������ ����
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
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)  //Ŭ���� ���� ��������
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		initX = X;
	}
}
void MyMouseMove(GLint X, GLint Y) //ī�޶��� ��ġ�� ��ȯ ��Ŵ
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
	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
		0, 0, 0 + aaa,	//�ٶ󺸴� ��
		0, 1, 0);	//������ 

	glutPostRedisplay();
}


/*
 * light (����)
 */
void InitLight()
{
	GLfloat mat_diffuse[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_specular[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.1, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	//0�� ����
	GLfloat light_specular[] = { 1.0, 0.2, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.4, 0.3, 0.3, 1.0 };

	GLfloat light_position[] = { -3, 10, 3.0, 0.0 };	//���� ��ġ �Ҵ�,  �¾�ó�� ������ �Ʒ��� ���� ��

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
 * �ؽ���
 */
void MyInit()
{
	MyDib dib; //  && ����
	char filename[20] = { 0, };
	strcpy(filename, "choi.bmp");
	dib.ReadBMP(filename); // && �׸� ���� ����
	dib.m_lpImage; // &&  �������� ���� �ּ�
	glTexImage2D(GL_TEXTURE_2D, 0, 3, dib.GetWidth(), dib.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, dib.m_lpImage);
	// && �ؽ��� �׸��� ���     �� ������ �ٽ�!  -> �ؽ��� ����,  �������� ��ǥ�� ���߸� ��

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dib.GetWidth(), dib.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, dib.m_lpImage); //mip map�� �������

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // GL_REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // GL_REPEAT

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Ȯ������϶� ����� ���� ����
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //mip map�� ����ϸ� ����� ���̵����� ǰ���� ������
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//ȯ�濡 ���� ����,  �ؽ��İ� ���� �������� ���� ��ü�� ���ٰ���?,  ��������,   modulate ������
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //GL_DECAL,GL_REPLACE, GL_MODULATE


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, ���ι����� s,  �ؽ��İ� ���� ��ǥ�� ©���� �ݺ��ؼ� ���� ���� = REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_REPEAT, ���ι����� t,  �ؽ��İ� ���� ��ǥ�� ©���� �ݺ��ؼ� ���� ���� = REPEAT
}

/*
 * capyright  1392056  kim jun hee
 */