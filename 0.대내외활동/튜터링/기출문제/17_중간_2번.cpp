//#include <iostream>
//using namespace std;
//
//class Circle {
//	int x, y, r;
//public:
//	Circle(int xx, int yy, int zz);
//	int GetX();
//	int GetY();
//	int GetR();
//};
//
//class Ring {
//	Circle inCircle, outCircle;
//public:
//	Ring(int xx1, int yy1, int zz1, int xx2, int yy2, int zz2);
//	void ShowRing();
//};
//
//int main() {
//	// inCircle 인자 3개, outCircle 인자 3개
//	Ring r(10, 20, 5, 10, 20, 10);
//	r.ShowRing();
//	return 0;
//}
//
//
//// 각 4점
//Circle::Circle(int xx, int yy, int zz) : x(xx), y(yy), r(zz) {}
//
//int Circle::GetX() { return x; }
//int Circle::GetY() { return y; }
//int Circle::GetR() { return r; }
//
//// 각 12점
//Ring::Ring(int xx1, int yy1, int zz1, int xx2, int yy2, int zz2) : inCircle(xx1, yy1, zz1), outCircle(xx2, yy2, zz2) {}
//
//void Ring::ShowRing() {
//	cout << inCircle.GetX() << inCircle.GetY() << inCircle.GetR() << endl;
//	cout << outCircle.GetX() << outCircle.GetY() << outCircle.GetR() << endl;
//}
