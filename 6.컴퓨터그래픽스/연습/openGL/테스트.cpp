//#include <iostream>
//using namespace std;
//
//int makeOne(int num) {
//	int turn = 0;
//	if (num == 1) {
//		cout << "-------------------\n";
//		cout << "동작 : 종료";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//		return turn + 1;
//	}
//	else if ((num - 1) % 3 == 0) {
//		cout << "-------------------\n";
//		cout << "동작 : (num - 1) ÷ 3";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//
//		if ((num - 1) / 3 != 1) { turn += 2; }
//		turn += makeOne((num-1) / 3);
//	}
//	else if (num % 3 == 0) {
//		cout << "-------------------\n";
//		cout << "동작 : num ÷ 3";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//		
//		if (num/3 != 1) { turn++; }
//		turn += makeOne(num / 3);
//	}
//	else if ((num - 1) % 3 == 0) {
//		cout << "-------------------\n";
//		cout << "동작 : num ÷ 3";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//
//		if ((num - 1) / 3 != 1) { turn += 2; }
//		turn += makeOne((num - 1) / 3);
//	}
//	else if (num % 2 == 0) {
//		cout << "-------------------\n";
//		cout << "동작 : num ÷ 2";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//
//		if (num/2 != 1) { turn++; }
//		turn += makeOne(num / 2);
//	}
//	else {
//		cout << "-------------------\n";
//		cout << "동작 : num - 1";
//		cout << "num 값 : 1 \n";
//		cout << "turn 값 : " << turn << endl;
//		cout << "-------------------\n\n";
//
//		if (num-1 != 1) { turn++; }
//		turn += makeOne(num - 1);
//	}
//}
//
//int main() {
//	while (777) {
//		int num, turn; 
//		cin >> num;
//		turn = makeOne(num);
//		cout << "함수 동작 끝. turn 값 : " << turn << endl << endl;
//	}
//}