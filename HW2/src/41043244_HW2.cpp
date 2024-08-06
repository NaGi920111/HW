#include <iostream>
#include <algorithm>
#include <cmath> 
using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
public:
	float coef;  // �Y��
	int exp;     // ����
};

class Polynomial {
	friend ostream& operator<<(ostream& o, const Polynomial& poly);

public:
	Polynomial(); // �غc�l
	Polynomial(const Polynomial& poly); // �ƻs�غc�l
	~Polynomial(); // �Ѻc�l
	Polynomial add(const Polynomial& poly); // �[�k�B��
	Polynomial mult(const Polynomial& poly); // ���k�B��
	float Eval(float x); // �N�J x �p��h��������
	void NewTerm(float coef, int exp); // �s�W��
private:
	void insertTerm(const Term& term); // ���J���ܦh����
private:
	Term* termArray; // �Ω�s�x�h���������}�C
	int capacity; // �}�C���ثe�e�q
	int terms; // �h�������ثe������
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
	delete[] termArray; // ����O����
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
	cout << "�п�J�h����a���Y�ƻP���� (�p 3 2 ��� 3x^2�A��J 0 0 ������J): " << endl;
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		a.NewTerm(coef, exp);
		cin >> coef >> exp;
	}

	Polynomial b;
	cout << "�п�J�h����b���Y�ƻP���� (�p 3 2 ��� 3x^2�A��J 0 0 ������J): " << endl;
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		b.NewTerm(coef, exp);
		cin >> coef >> exp;
	}

	cout << a << " + " << b << " = " << a.add(b) << endl;
	cout << a << " * " << b << " = " << a.mult(b) << endl;

	cout << "�п�J���D�Ȫ�x: " << endl;
	float x;
	cin >> x;
	cout << "�bx=" << x << "�ɡAa+b���Ȭ�: " << a.add(b).Eval(x) << endl;

	return 0;
}

