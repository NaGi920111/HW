#include <iostream>
#include <algorithm>
#include <cmath> 
using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
public:
	float coef;  // 係數
	int exp;     // 指數
};

class Polynomial {
	friend ostream& operator<<(ostream& o, const Polynomial& poly);

public:
	Polynomial(); // 建構子
	Polynomial(const Polynomial& poly); // 複製建構子
	~Polynomial(); // 解構子
	Polynomial add(const Polynomial& poly); // 加法運算
	Polynomial mult(const Polynomial& poly); // 乘法運算
	float Eval(float x); // 代入 x 計算多項式的值
	void NewTerm(float coef, int exp); // 新增項
private:
	void insertTerm(const Term& term); // 插入項至多項式
private:
	Term* termArray; // 用於存儲多項式項的陣列
	int capacity; // 陣列的目前容量
	int terms; // 多項式中目前的項數
};

Polynomial::Polynomial() {
	this->terms = 0;
	this->capacity = 10;
	termArray = new Term[this->capacity];
}

Polynomial::Polynomial(const Polynomial& b) {
	this->terms = b.terms;
	this->capacity = b.capacity;
	termArray = new Term[this->capacity];
	copy(b.termArray, b.termArray + b.terms, termArray);
}

Polynomial::~Polynomial() {
	delete[] termArray; // 釋放記憶體
}

Polynomial Polynomial::add(const Polynomial& b) {
	Polynomial c;
	int ac = 0;
	int bc = 0;
	while (ac < terms && bc < b.terms) {
		if (termArray[ac].exp == b.termArray[bc].exp) {
			float coef = termArray[ac].coef + b.termArray[bc].coef;
			if (coef != 0) c.NewTerm(coef, termArray[ac].exp);
			ac++; bc++;
		}
		else if (termArray[ac].exp < b.termArray[bc].exp) {
			c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);
			bc++;
		}
		else {
			c.NewTerm(termArray[ac].coef, termArray[ac].exp);
			ac++;
		}
	}
	while (ac < terms) {
		c.NewTerm(termArray[ac].coef, termArray[ac].exp);
		ac++;
	}
	while (bc < b.terms) {
		c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);
		bc++;
	}
	return c;
}

Polynomial Polynomial::mult(const Polynomial& b) {
	Polynomial c;
	for (int i = 0; i < terms; i++) {
		for (int j = 0; j < b.terms; j++) {
			float coef = termArray[i].coef * b.termArray[j].coef;
			int exp = termArray[i].exp + b.termArray[j].exp;
			c.NewTerm(coef, exp);
		}
	}
	return c;
}

void Polynomial::NewTerm(float coef, int exp) {
	if (terms == capacity) {
		capacity *= 2;
		Term* tmp = new Term[capacity];
		copy(termArray, termArray + terms, tmp);
		delete[] termArray;
		termArray = tmp;
	}
	Term ATerm;
	ATerm.coef = coef; 
	ATerm.exp = exp;
	insertTerm(ATerm);
}

void Polynomial::insertTerm(const Term& term) {
	int i;
	for (i = 0; i < terms && term.exp < termArray[i].exp; i++) {
	}
	if (i < terms && term.exp == termArray[i].exp) {
		termArray[i].coef += term.coef;
		if (termArray[i].coef == 0) {
			for (int j = i; j < terms - 1; j++) {
				termArray[j] = termArray[j + 1];
			}
			terms--;
		}
	} else {
		for (int j = terms; j > i; j--) {
			termArray[j] = termArray[j - 1];
		}
		termArray[i] = term;
		terms++;
	}
}

float Polynomial::Eval(float x) {
	float sum = 0;
	for (int i = 0; i < terms; i++) {
		sum += termArray[i].coef * pow(x, termArray[i].exp);
	}
	return sum;
}

ostream& operator<<(ostream& o, const Polynomial& poly) {
	for (int i = 0; i < poly.terms - 1; i++) {
		o << poly.termArray[i].coef << "x^" << poly.termArray[i].exp << " + ";
	}
	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].exp;
	return o;
}

int main() {
	Polynomial a;
	int coef;
	float exp;
	cout << "請輸入多項式a的係數與指數 (如 3 2 表示 3x^2，輸入 0 0 結束輸入): " << endl;
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		a.NewTerm(coef, exp);
		cin >> coef >> exp;
	}

	Polynomial b;
	cout << "請輸入多項式b的係數與指數 (如 3 2 表示 3x^2，輸入 0 0 結束輸入): " << endl;
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		b.NewTerm(coef, exp);
		cin >> coef >> exp;
	}

	cout << a << " + " << b << " = " << a.add(b) << endl;
	cout << a << " * " << b << " = " << a.mult(b) << endl;

	cout << "請輸入欲求值的x: " << endl;
	float x;
	cin >> x;
	cout << "在x=" << x << "時，a+b的值為: " << a.add(b).Eval(x) << endl;

	return 0;
}

