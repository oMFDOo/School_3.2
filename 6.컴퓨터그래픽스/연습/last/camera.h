#pragma once
#pragma once
/*
camera.h
���� ����, ī�޶� Ŭ������ �����ϴ� �ҽ�
*/

/*
�̰� �� �ۼ��� �ʿ� x
�׳� �⸻ ������Ʈ �� ���� ���� ��
*/

class Point3
{ //����Ŭ����
public:
	float x, y, z;//��ǥ
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//������ǥ����޼ҵ�
	void set(Point3& p) { x = p.x; y = p.y; z = p.z; }//������ǥ����޼ҵ�2 �ٸ����� ����
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }//������: �����ʱ�ȭ
	Point3() { x = y = z = 0; }//������: �ʱ�ȭ������ ����
};

class Vector3
{
public:
	float x, y, z;//���ͼ���
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//���ͻ����޼ҵ�
	void set(Vector3& v) { x = v.x; y = v.y; z = v.z; }//���ͻ����޼ҵ�
	void flip() { x = -x; y = -y; z = -z; } //�ݴ���⺤��
	void setDiff(Point3& a, Point3& b)//�κ�������
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	void normalize();//�������ͷ�
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; } //������
	Vector3(Vector3& v) { x = v.x; y = v.y; z = v.z; }
	Vector3() { x = y = z = 0.0; }
	Vector3 cross(Vector3 b);//����
	float dot(Vector3 b);//����
};

class Camera
{
public:
	Point3 eye;//������ǥ�����
	Vector3 u, v, n;//������ǥ�踦 �����ϴ� ������������
	float aspect, nearDist, farDist, viewAngle;//gluPerspective�� �Ķ���͵� ������ȯ�� �̿�
	void setModelViewMatrix();// ������ȯ�� ���� �𵨺��������
	Camera(void); // ������

	// ����ùķ������� ȸ�� ��ȯ�Լ��� roll pitch yaw
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	// �̵���ȯ
	void slide(double du, double dv, double dn);

	//ī�޶���ġ, ����,ī�޶������ ����
	void set(Point3 Eye, Point3 look, Vector3 up); // ���ͷ�
	void set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ); //������

	void setShape(float viewAngle, float aspect, float Near, float Far); //ȭ������
	void setAspect(float asp); // ��Ⱦ������
	void getShape(float& viewAngle, float& aspect, float& Near, float& Far); //ȭ�鱸��������
	void rotAxes(Vector3& a, Vector3& b, float angle);//������ǥ����ȸ��
	void setDefaultCamera();// ī�޶��ʱ⼳���Լ�
};
