#include <iostream>
#include <fstream>		
#include <vector>
#include "Polynomial.h"					//Adding headers
#include "Vector.h"						//Adding headers

/*  Author:
	Name_Surname	: Ahmet Semih Uçan
	Number			: 150160014
	Date			: 25.03.2019
*/


using namespace std;

int main() {

	vector <Polynomial> pollist;
	//////Polynomial File Reading and Creating Objects/////////////
	ifstream polyfile;
	polyfile.open("Polynomial.txt");
	int row;
	polyfile >> row;

	int* list;
	for (int i = 0; i < row; i++) {
		int degree;
		polyfile >> degree;
		list = new int[degree+1];
		for (int j = 0; j < degree + 1; j++) {
			//Dereceler ile indexler ayný duruma gelmesi için 
			polyfile >> list[degree-j];
		}		
		Polynomial tmp(list,degree);
		pollist.push_back(tmp);
	}	

	//////Vector File Reading and Creating Objects/////////////
	vector <vectors>vectorlist;
	ifstream vecfile;
	vecfile.open("Vector.txt");
	int row_vec;
	vecfile >> row_vec;
	int* veclist;
	for (int i = 0; i < row_vec; i++) {
		int vec_degree;
		vecfile >> vec_degree;
		veclist = new int[vec_degree + 1];
		for (int j = 0; j < vec_degree ; j++) {
			vecfile >> veclist[j];
		}
		vectors b(veclist, vec_degree);
		vectorlist.push_back(b);
	}

	///////////////////////User Inteface ////////////////////////
	int state=4;							//Default print all possibilities
	int first_order, second_order;			//Index to do operations
	char operation_type;					//Operation type
	while (state != 0) {
		if (state == 1) {
			//Print all
			//Vector Ekrana basma/////////////////////////////////////
			cout << endl;
			cout << "Vectors:" << endl;
			for (int i = 0; i < row_vec ; i++) {
				cout << i + 1 << ". " << vectorlist[i] << endl;
			}
			cout << endl;
			//Polinomu Ekrana basma/////////////////////////////////////
			cout << "Polynomials: " << endl;
			for (int i = 0; i < row ; i++) {
				cout << i + 1 << ". " << pollist[i] << endl;
			}
		}		
		else if (state == 2) {
			cout << "Which polynomial operation would you like to do?(+:addition, *:multiplication):" << endl;
			cin >> first_order >> operation_type >> second_order;
			if (operation_type == '+') {
				cout <<"(" << pollist[first_order - 1] << ")"<< " + " << "(" << pollist[second_order - 1] << ")" << " = ";
				cout << pollist[first_order - 1] + pollist[second_order - 1];
				cout << endl;
			}
			else if (operation_type == '*') {
				cout <<"("<< pollist[first_order - 1] <<")"<< " * " <<"(" << pollist[second_order - 1] << ")" << " = ";
				cout << pollist[first_order - 1] * pollist[second_order - 1];
				cout << endl;
			}
		}
		else if (state == 3) {
			cout << "Which vector operation would you like to do?(+:addition, *:scalar multiplication, .:dot product):" << endl;
			cin >> first_order >> operation_type >> second_order;
			if (operation_type == '+') {
				cout << vectorlist[first_order - 1]  << " + " << vectorlist[second_order - 1] << " = ";
				cout << vectorlist[first_order - 1] + vectorlist[second_order - 1];
				if (vectorlist[first_order - 1].getSize() != vectorlist[second_order - 1].getSize()) {
					cout << endl << "Sizes of vectors are different!";
				}
				cout << endl;
			}else if (operation_type == '*') {
				cout << vectorlist[first_order - 1] << " * " << second_order << " = ";
				cout << vectorlist[first_order - 1] * second_order ;
				cout << endl;
			}
			else if (operation_type == '.') {
				cout << vectorlist[first_order - 1] << " . " << vectorlist[second_order - 1] << " = ";
				cout << vectorlist[first_order - 1] * vectorlist[second_order - 1];
				if (vectorlist[first_order - 1].getSize() != vectorlist[second_order - 1].getSize()) {
					cout << endl << "Sizes of vectors are different!";
				}
				cout << endl;
			}
		}
		else if (state == 4) {
			//Yeterli bilgi verilmemiþ
			cout << endl << "Polynomial and Vector List Program!" << endl;
			cout << "Polynomial and Vector are read from text files!" << endl << endl;
			cout << "Posssible Actions:" << endl;
			cout << "1. Print Polynomial and Vector lists" << endl;
			cout << "2. Do a polynomial operation" << endl;
			cout << "3. Do a vector operation" << endl;
			cout << "4. Help: Print possible actions" << endl;
			cout << "0. Exit the program" << endl << endl;
		}
		cout << endl;	
		cout << "Enter an option: ";
		cin >> state;
	}

	
	vecfile.close();						//File closing	
	polyfile.close();						//File closing	
	return 0;
}
