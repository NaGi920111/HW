#include<iostream>
#include<cmath>
#include<Windows.h>
using namespace std;
int counter = 0;
struct Term {
	int coef = -1;
	int exp = -1;
	Term set(int c, int e)
	{
		coef = c;
		exp = e;
		return *this;
	}
};

template<class T>
class LinkList;

template<class T>
class LinkNode {
	friend class LinkList<T>;
private:
	T data;
	LinkNode<T>* link;
public:
	LinkNode(const T& element = T(), LinkNode<T>* next = 0) {
		counter += 2;
		data = element;
		link = next;
	}
};

template<class T>
class LinkList {
private:
	LinkNode<T>* first;
	LinkNode<T>* last;
public:
	LinkList() {
		counter += 3;
		first = new LinkNode<T>;
		first->link = first;
		last = first;
	}
	~LinkList() {
		counter++;
		static LinkNode<T>* av;
		if (last) {
			counter += 4;
			LinkNode<T>* first = last->link;
			last->link = av;
			av = first;
			last = 0;
		}
	}

	void InsertBack(const T& e) {
		counter++;
		if (first) {
			counter += 3;
			last->link = new LinkNode<T>(e);
			last = last->link;
			last->link = first;
		}
		else {
			counter++;
			first = last = new LinkNode<T>(e);
		}
	}
	class iterator {
	public:
		iterator(LinkNode<T>* startNode = 0) {
			counter++;
			current = startNode;
		}

		T& operator*() const {
			counter++;
			return current->data;
		}
		T* operator->() const {
			counter++;
			return &current->data;
		}
		iterator& operator ++() {
			counter++;
			current = current->link;
			return *this;
		}
		iterator operator ++(int) {
			counter += 2;
			iterator old = *this;
			current = current->link;
			return *this;
		}
		bool operator!=(const iterator right) const {
			counter++;
			return current != right.current;
		}
		bool operator ==(const iterator right) const {
			counter++;
			return current == right.current;
		}
	private:
		LinkNode<T>* current;
	};
	iterator begin() const {
		counter++;
		return iterator(first->link);
	}
	iterator end() const {
		counter++;
		return iterator(first);
	}
};

class Polynomial {
private:
	LinkList<Term> poly;
public:
	Polynomial() {};
	Polynomial operator+(const Polynomial& b) {
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		counter += 3;
		while (1) {
			counter++;
			if (ai->exp == bi->exp) {
				counter++;
				if (ai->exp == -1) {
					counter++;
					return c;
				}

				int sum = ai->coef + bi->coef;
				counter++;
				if (sum) {
					counter += 3;
					c.poly.InsertBack(temp.set(sum, ai->exp));
					ai++; bi++;
				}
			}
			else if (ai->exp < bi->exp) {
				counter += 2;
				c.poly.InsertBack(temp.set(bi->coef, bi->exp));
				bi++;
			}
			else {
				counter += 2;
				c.poly.InsertBack(temp.set(ai->coef, ai->exp));
				ai++;
			}
		}
	}

	Polynomial operator-(const Polynomial& b) {
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		counter += 3;
		while (1) {
			counter++;
			if (ai->exp == bi->exp) {
				counter++;
				if (ai->exp == -1) {
					counter++;
					return c;
				}
				counter++;
				int sum = ai->coef - bi->coef;
				if (sum) {
					counter++;
					c.poly.InsertBack(temp.set(sum, ai->exp));
				}
				counter++;
				ai++; bi++;
			}
			else if (ai->exp < bi->exp) {
				counter += 2;
				c.poly.InsertBack(temp.set((-1) * (bi->coef), bi->exp));
				bi++;
			}
			else {
				counter += 2;
				c.poly.InsertBack(temp.set(ai->coef, ai->exp));
				ai++;
			}
		}
	}

	Polynomial operator*(const Polynomial& b) {
		Term temp;
		LinkList<Term>::iterator ai = poly.begin(), bi = b.poly.begin();
		Polynomial c;
		counter += 3;
		while (1) {
			counter++;
			Polynomial c1;
			if (ai->exp < 0) {
				counter++;
				break;
			}
			while (1) {
				counter += 2;
				c1.poly.InsertBack(temp.set((ai->coef) * (bi->coef), bi->exp + ai->exp));
				bi++;
				if (bi->exp < 0)
				{
					counter += 2;
					bi = b.poly.begin();
					c = c + c1;
					break;
				}
			}
			counter++;
			ai++;
		}
		return c;
	}
	friend istream& operator>>(istream& in, Polynomial& a);
	friend ostream& operator<<(ostream& ot, Polynomial& a);
	Polynomial(const Polynomial& a) {
		counter++;
		poly = a.poly;
	}
	const Polynomial& operator=(const Polynomial& b) {
		counter++;
		this->poly = b.poly;

		return *this;
	}
	~Polynomial() { }

	float Evaluate(float x) const {
		counter += 2;
		LinkList<Term>::iterator ai = poly.begin();
		float sum = 0.0;

		while (1) {
			counter++;
			if (ai->exp == -1) {
				counter++;
				break;
			}
			counter += 2;
			sum += (ai->coef) * pow(x, ai->exp);
			ai++;
		}
		return sum;
	}
};

istream& operator>>(istream& op_in, Polynomial& a) {
	counter++;
	Term temp;
	int n, c, e;
	counter++;
	cout << "輸入項數:" << endl;
	cin >> n;
	cout << "輸入係數及次方 (ex:1 3 2 2 4 1)" << endl;
	while (n) {
		counter++;
		op_in >> c >> e;
		a.poly.InsertBack(temp.set(c, e));
		n--;
		counter++;
	}
	return op_in;
	counter++;
}
ostream& operator<<(ostream& op_out, Polynomial& a) {
	counter++;
	LinkList<Term>::iterator ai = a.poly.begin();
	while (1) {
		counter++;
		if (ai->exp == -1) {
			counter++;
			return op_out;
		}
		if (ai->exp == 0) {
			counter++;
			op_out << ai->coef;
		}
		else {
			counter++;
			op_out << ai->coef << "X^" << ai->exp;
		}
		ai++;
		counter++;
		if (ai->coef > 0 && ai->exp != -1) {
			counter++;
			op_out << "+";
		}
	}
}

int main() {
	LARGE_INTEGER start1, end1, start2, end2, fre, start3, end3, start4, end4;
	double times1, times2, times3, times4;

	Polynomial Polya, Polyb, Polyc, Polyd, Polye;

	cin >> Polya;
	cin >> Polyb;

	cout << "a=" << Polya << endl;
	cout << "b=" << Polyb << endl;

	QueryPerformanceFrequency(&fre);

	QueryPerformanceCounter(&start1);
	Polyc = Polya + Polyb;
	QueryPerformanceCounter(&end1);

	times1 = ((double)end1.QuadPart - (double)start1.QuadPart) / fre.QuadPart;

	cout << "a+b=" << Polyc;
	cout << endl;

	QueryPerformanceCounter(&start2);
	Polyd = Polya - Polyb;
	QueryPerformanceCounter(&end2);

	times2 = ((double)end2.QuadPart - (double)start2.QuadPart) / fre.QuadPart;

	cout << "a-b=" << Polyd;
	cout << endl;

	QueryPerformanceCounter(&start3);
	Polye = Polya * Polyb;
	QueryPerformanceCounter(&end3);
	times3 = ((double)end3.QuadPart - (double)start3.QuadPart) / fre.QuadPart;

	cout << "a*b=" << Polye;
	cout << endl;

	float x;
	cout << "輸入要代入的X值:" << endl;
	cin >> x;
	QueryPerformanceCounter(&start4);
	cout << "a=" << Polya.Evaluate(x);
	cout << endl;
	cout << "b=" << Polyb.Evaluate(x);
	cout << endl;
	cout << "a+b=" << Polyc.Evaluate(x);
	cout << endl;
	cout << "a-b=" << Polyd.Evaluate(x);
	cout << endl;
	cout << "a*b=" << Polye.Evaluate(x);
	cout << endl;
	QueryPerformanceCounter(&end4);

	times4 = ((double)end4.QuadPart - (double)start4.QuadPart) / fre.QuadPart;

	counter += 11;

	cout << "total_steps:" << counter << "\n";

	cout << "total_times：" << times1 + times2 + times3 + times4 << "秒" << endl;


}
