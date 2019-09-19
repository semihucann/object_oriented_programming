#include <iostream>

using namespace std;

class vectors {
private:
	int size;
	int* list;
public:		
	//Constructor
	vectors(int* veclist, int vecsize);
	//Copy constructor
	vectors(const vectors &a);
	//Operator+ 
	vectors operator+(const vectors &a)const;
	//Operator* for dot product
	int operator*(const vectors &a)const;
	//Operator* for scalar multipication
	vectors operator*(int scaler);
	//Operator <<
	friend ostream& operator<< (ostream& stream, const vectors& a);
	//Getter Method
	int getSize() { return size; }
};
ostream& operator<<(ostream& stream, const vectors& a){			//Operator <<
	stream << "(";
	for (int i = 0; i < a.size; i++) {
		stream << a.list[i];
		if(i==a.size-1) stream << "";
		else stream << ", ";
	}
	stream << ")";
	return stream;
}
vectors::vectors(int* veclist, int vecsize) {					//Constructor
	size = vecsize;
	int* newList = new int[vecsize + 1];
	for (int i = 0; i < vecsize + 1; i++) {
		newList[i] = veclist[i];
	}
	list = newList;
}
vectors::vectors(const vectors &a){								//Copy constructor
	size = a.size;
	list = a.list;
}
vectors vectors::operator+(const vectors &a) const {
	int* re_list=new int[size];

	if (size == a.size) {										//If both of vectors are same size, adding 
		for (int i = 0; i < size; i++) {
			re_list[i] = 0;
			re_list[i] = list[i] + a.list[i];
		}
		int re_size = size;
		return vectors(re_list, re_size);
	}
	else {														//Boyutlar eþit deðilse
		int* empty = new int[0];
		return vectors(empty, 0);
	}
}
vectors vectors::operator*(int scaler) {						//Operator* for scalar multipication
	int* re_list = new int[size];

	for (int i = 0; i < size; i++) {
		re_list[i] = list[i] * scaler;
	}
	return vectors(re_list, size);
}
int vectors::operator*(const vectors &a) const {				//Operator* for dot product
	int result = 0;

	if (size == a.size) {
		for (int i = 0; i < size; i++) {
			result += (list[i] * a.list[i]);
		}	
	}
	
	return result;
}

