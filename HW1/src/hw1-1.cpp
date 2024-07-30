/*
41043244
賴明賢
*/
#include<iostream>
#include<math.h>
using namespace std;

int Ackermann(long long int m, long long int n) {
	if (m == 0)    // m = 0 時， n + 1   
		return n + 1;
	else if (n == 0) // n = 0 時， m - 1 以及 n + 1 
		return Ackermann(m - 1, 1);
	else
		return Ackermann(m - 1, Ackermann(m, n - 1)); //，套用 Ackermann 函數的規則 ，開始遞迴 	
}

int non_Ackermann(long long int m, long long int n) {
	long long num; // Ackermann函數的答案 
	if (m == 0) return num = n + 1;         // 透過Ackermann函數的建表，推斷 m 和 n 的關係式  
	if (m == 1) return num = n + 2;
	if (m == 2) return num = 2 * (n + 3) - 3;
	if (m == 3) return num = pow(2, (n + 3)) - 3; // pow(2,n) = 2 ^ n	 			
}

int main() {
	long long int m, n; //宣告變數 m 和 n 
	while (cout << "輸入 m 和 n: " && cin >> m >> n) { //輸入 m 和 n 
		cout << "遞迴: " << Ackermann(m, n) << " " << endl;
		cout << "非遞迴: " << non_Ackermann(m, n) << endl; // 輸出  
	}

}
