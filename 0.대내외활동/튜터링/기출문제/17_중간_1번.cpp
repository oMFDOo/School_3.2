//#include <iostream>
//using namespace std;
//
//class Box {
//	int W, H;
//public:
//	Box() { H = 2; W = 2; }
//	Box(int hh, int ww) : H(hh), W(ww) { }
//	void isBig(Box& x);
//	int Area() { return W * H; }
//};
//
//void Box::isBig(Box& x) {
//	if (Area() > x.Area())
//		cout << W << " * " << H << " is (1) " << endl;
//	else
//		cout << x.W << " * " << x.H << " is (2) " << endl;
//}
//
//int main() {
//	Box a, b(3, 4);
//	a.isBig(b);
//	b.isBig(a);
//}