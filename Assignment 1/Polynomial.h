#include <iostream>

using namespace std;

class Polynomial {
private:
	int degree;
	int* list;
public:	
	//Constructor
	Polynomial(int* pollist, int poldegree);
	//Copy Constructor
	Polynomial(const Polynomial &a);
	//Operator+ 
	Polynomial operator+(const Polynomial& a)const;
	//Operator*
	Polynomial operator*(const Polynomial& a)const;
	//Operator <<
	friend ostream& operator<< (ostream& stream, const Polynomial& a);
};

ostream& operator<<(ostream& stream, const Polynomial& a) {
	/*Polinomlarý kolay iþlem yapabilmek için 0.dereceden baþlayarak listede tuttum 
	ekrana en büyük dereceden baþlayarak bastýrmak için ters çeviriyorum.*/
	for (int i = a.degree; i >= 0; i--) {
		if (i == 0) {
			//0.derece
			stream << a.list[i] ;
			if (i == 0) stream << "";
			else stream << " + ";
		}else if (i == 1) {
			//1.derece
			stream << a.list[i] << "x";
			if (i == 0) stream << "";
			else stream << " + ";
		}
		else {
			if (a.list[i] == 0) {
				//Katsayýsý sýfýrsa
			}
			else if (a.list[i] == 1) {
				//Katsayýsý 1 ise
				stream << "x^" << i;
				if (i == 0) stream << "";
				else stream << " + ";
			}
			else {
				stream << a.list[i] << "x^" << i;
				if (i == 0) stream << "";
				else stream << " + ";
			}
		}		
	}
	
	return stream;
}

Polynomial::Polynomial(int* pollist, int poldegree) {					//Constructor
	degree = poldegree;
	int* arrayPol = new int[poldegree +1];
	for (int i = 0; i < degree + 1; i++) {
		arrayPol[i] = pollist[i];
	}
	list = arrayPol;
}
Polynomial::Polynomial(const Polynomial &a) {							//Copy Constructor
	degree = a.degree;
	list = a.list;
}
Polynomial Polynomial::operator+(const Polynomial& a)const {			//Operator +
	int re_degree;
	if (degree < a.degree) {
		re_degree = a.degree;
	}
	else {
		re_degree = degree;
	}

	int* newArray = new int[re_degree+1];

	for (int i = 0; i < re_degree + 1; i++) {
		newArray[i] = 0;
		if (degree >= i) {
			newArray[i] += list[i];
		}
		if (a.degree >= i) {
			newArray[i] += a.list[i];
		}
	}
	return Polynomial(newArray, re_degree);
}
Polynomial Polynomial::operator*(const Polynomial &a)const {			//Operator *
	int re_degree = degree + a.degree;

	int* re_list = new int[re_degree + 1];

	for (int i = 0; i <= re_degree; i++) {
		re_list[i] = 0;
	}

	for (int i = 0; i <= degree; i++) {
		for (int j = 0; j <= a.degree; j++) {
			re_list[i + j] += list[i] * a.list[j];
		}
	}

	return Polynomial(re_list, re_degree);
}