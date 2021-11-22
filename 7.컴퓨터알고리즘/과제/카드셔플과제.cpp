#include <iostream>
using namespace std;

/*
Testing for test suit 0
Input data:
2 1 2 2 3 4 3 1 2 4
Expected result:
TRUE TRUE TRUE
Your result:
TRUE TRUE TRUE
Pass the testing for test suit 0

Testing for test suit 1
Input data:
2 1 2 2 3 4 3 2 1 4
Expected result:
FALSE FALSE FALSE
Your result:
FALSE FALSE FALSE
Pass the testing for test suit 1

Testing for test suit 2
Input data:
3 1 1 1 3 1 1 2 1 1 2 1 1 1
Expected result:
TRUE TRUE TRUE
Your result:
TRUE TRUE TRUE
Pass the testing for test suit 2

Testing for test suit 3
Input data:
3 1 1 1 3 1 1 2 1 2 1 1 1 1
Expected result:
FALSE FALSE FALSE
Your result:
FALSE FALSE FALSE
Pass the testing for test suit 3

Congratulations... your program passed the test
*/


bool S[50][50] = { {0} }; // DP에 사용
int SS[50][50] = { {0} }; // MM에 사용
// 추가 전역변수 선언가능

int sizeN, sizeM;

void init(int n, int m) {
    sizeN = n;
    sizeM = m;
}

// 분할정복 : 재귀
bool shuffle_DC(int A[], int B[], int C[], int n, int m) {
    //cout << "n : " << n << "\t m : " << m << endl;
    //cout << "A[n] : " << A[n] << "\t B[m] : " << B[m] << "\t C[n+m] : " << C[n + m] << endl << endl;
    bool result = true;
    if (n == 0 && m == 0) { return true; }
    else if (A[n] == C[n + m] && 0 < n) {
        result = shuffle_DC(A, B, C, n - 1, m);
    }
    else if (B[m] == C[n + m] && 0 < m) {
        result = shuffle_DC(A, B, C, n, m - 1);
    }
    else return false;
    return result;
}

// 동적프로그래밍 : 반복문
bool shuffle_DP(int A[], int B[], int C[], int n, int m) {
    //cout << "n : " << n << "\t m : " << m << endl;
    //cout << "A[n] : " << A[n] << "\t B[m] : " << B[m] << "\t C[n+m] : " << C[n + m] << endl << endl;
    bool result = true;
    if (n == 0 && m == 0) { return true; }
    else if (S[n][m]) return true;
    else if (A[n] == C[n + m] && 0 < n) {
        S[n][m] = true;
        result = shuffle_DC(A, B, C, n - 1, m);
    }
    else if (B[m] == C[n + m] && 0 < m) {
        S[n][m] = true;
        result = shuffle_DC(A, B, C, n, m - 1);
    }
    else return  false;
    return result;
}

// 메모리제이션 : 재귀
bool shuffle_MM(int A[], int B[], int C[], int n, int m) {
    //cout << "n : " << n << "\t m : " << m << endl;
    //cout << "A[n] : " << A[n] << "\t B[m] : " << B[m] << "\t C[n+m] : " << C[n+m] << endl << endl;
    /*if (n == 0 && m == 0) { return true; }
    else if (SS[n][m] == 1) return SS[n][m];
    else if (n > 0 && shuffle_MM(A, B, C, n - 1, m) && C[n + m] == A[n]) {
        SS[n][m] = 1;
        SS[n-1][m] = 1;
    }
    else if (m > 0 && shuffle_MM(A, B, C, n, m - 1) && C[n + m] == B[m]) {
        SS[n][m] = 1;
        SS[n][m-1] = 1;
    }
    return SS[1][1];*/
    if (n == 0 && m == 0)  { return true; }
    else if (SS[n][m] != 0) return SS[n][m];
    else if (n > 0 && C[n + m] == A[n]) {
        if (shuffle_MM(A, B, C, n - 1, m)) SS[n][m] = 1;
        else SS[n][m] = -1;
    }
    else if (m > 0 && C[n + m] == B[m]) {
        if (shuffle_MM(A, B, C, n, m - 1)) SS[n][m] = 1;
        else SS[n][m] = -1;
    }
    else {
        SS[n][m] = -1;
        return SS[n][m] + 1;
    }
    return SS[n][m] + 1;
}

int main() {
    int A[50] = { 0 };
    int B[50] = { 0 };
    int C[100] = { 0 };
    int n, m, i, j, k;

    cin >> n;
    for (i = 1; i <= n; i++) cin >> A[i];
    cin >> m;
    for (j = 1; j <= m; j++) cin >> B[j];
    for (k = 1; k <= n + m; k++) cin >> C[k];
    init(n, m); //전역변수 초기화를 위해 사용가능

    if (shuffle_DC(A, B, C, n, m)) cout << "TRUE " << "\n\n";
    else cout << "FALSE " << "\n\n";
    if (shuffle_DP(A, B, C, n, m)) cout << "TRUE " << "\n\n";
    else cout << "FALSE " << "\n\n";
    if (shuffle_MM(A, B, C, n, m)) cout << "TRUE ";
    else cout << "FALSE ";

    return 0;
}