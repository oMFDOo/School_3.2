#pragma once
#pragma once
/*
camera.h
점과 벡터, 카메라 클래스를 구성하는 소스
*/

/*
이걸 다 작성할 필요 x
그냥 기말 프로젝트 때 갖다 쓰면 됨
*/

class Point3
{ //정점클래스
public:
	float x, y, z;//좌표
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//정점좌표변경메소드
	void set(Point3& p) { x = p.x; y = p.y; z = p.z; }//정점좌표변경메소드2 다른정점 대입
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }//생성자: 정점초기화
	Point3() { x = y = z = 0; }//생성자: 초기화없을시 원점
};

class Vector3
{
public:
	float x, y, z;//벡터성분
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//벡터생성메소드
	void set(Vector3& v) { x = v.x; y = v.y; z = v.z; }//벡터생성메소드
	void flip() { x = -x; y = -y; z = -z; } //반대방향벡터
	void setDiff(Point3& a, Point3& b)//두벡터의차
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	void normalize();//단위벡터로
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; } //생성자
	Vector3(Vector3& v) { x = v.x; y = v.y; z = v.z; }
	Vector3() { x = y = z = 0.0; }
	Vector3 cross(Vector3 b);//외적
	float dot(Vector3 b);//내적
};

class Camera
{
public:
	Point3 eye;//시점좌표계원점
	Vector3 u, v, n;//시점좌표계를 구성하는 정규직교기저
	float aspect, nearDist, farDist, viewAngle;//gluPerspective의 파라미터들 시점변환후 이용
	void setModelViewMatrix();// 시점변환에 따라 모델뷰행렬조정
	Camera(void); // 생성자

	// 비행시뮬레이터의 회전 변환함수들 roll pitch yaw
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	// 이동변환
	void slide(double du, double dv, double dn);

	//카메라위치, 시점,카메라업벡터 지정
	void set(Point3 Eye, Point3 look, Vector3 up); // 벡터로
	void set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ); //점으로

	void setShape(float viewAngle, float aspect, float Near, float Far); //화면정의
	void setAspect(float asp); // 종횡비정의
	void getShape(float& viewAngle, float& aspect, float& Near, float& Far); //화면구성값보기
	void rotAxes(Vector3& a, Vector3& b, float angle);//시점좌표계축회전
	void setDefaultCamera();// 카메라초기설정함수
};
