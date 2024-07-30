#include <iostream>
using namespace std;

void Powerset(char* set, int size, int index, string current) {
    if (index == size) {
        cout << "{ " << current << "}" << endl;
        return;
    }

    // ���]�t��e�����ò��ʨ�U�@��
    Powerset(set, size, index + 1, current);

    // �]�t��e�����ò��ʨ�U�@��
    Powerset(set, size, index + 1, current + set[index] + " ");
}

int main() {
    int n = 0;
    while (true) {
        cout << "�п�Jset���X��elements:" << endl;
        cin >> n;
        if (n < 0) break;

        char* S = new char[n];
        cout << "�п�J����:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> S[i];
        }

        cout << "Powerset:" << endl;
        Powerset(S, n, 0, "");

        delete[] S;
    }

    return 0;
}
