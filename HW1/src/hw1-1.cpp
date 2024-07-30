/*
41043244
�����
*/
#include<iostream>
#include<math.h>
using namespace std;

int Ackermann(long long int m, long long int n) {
	if (m == 0)    // m = 0 �ɡA n + 1   
		return n + 1;
	else if (n == 0) // n = 0 �ɡA m - 1 �H�� n + 1 
		return Ackermann(m - 1, 1);
	else
		return Ackermann(m - 1, Ackermann(m, n - 1)); //�A�M�� Ackermann ��ƪ��W�h �A�}�l���j 	
}

int non_Ackermann(long long int m, long long int n) {
	long long num; // Ackermann��ƪ����� 
	if (m == 0) return num = n + 1;         // �z�LAckermann��ƪ��ت�A���_ m �M n �����Y��  
	if (m == 1) return num = n + 2;
	if (m == 2) return num = 2 * (n + 3) - 3;
	if (m == 3) return num = pow(2, (n + 3)) - 3; // pow(2,n) = 2 ^ n	 			
}

int main() {
	long long int m, n; //�ŧi�ܼ� m �M n 
	while (cout << "��J m �M n: " && cin >> m >> n) { //��J m �M n 
		cout << "���j: " << Ackermann(m, n) << " " << endl;
		cout << "�D���j: " << non_Ackermann(m, n) << endl; // ��X  
	}

}
