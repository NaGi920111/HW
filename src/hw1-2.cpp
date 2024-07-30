#include <iostream>
using namespace std;

void Powerset(char* set, int size, int index, string current) {
    if (index == size) {
        cout << "{ " << current << "}" << endl;
        return;
    }

    // 不包含當前元素並移動到下一個
    Powerset(set, size, index + 1, current);

    // 包含當前元素並移動到下一個
    Powerset(set, size, index + 1, current + set[index] + " ");
}

int main() {
    int n = 0;
    while (true) {
        cout << "請輸入set有幾個elements:" << endl;
        cin >> n;
        if (n < 0) break;

        char* S = new char[n];
        cout << "請輸入元素:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> S[i];
        }

        cout << "Powerset:" << endl;
        Powerset(S, n, 0, "");

        delete[] S;
    }

    return 0;
}
