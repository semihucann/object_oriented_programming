#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

/* @Author
* Student Name: AHMET SEMIH UCAN
* Student ID : 150160014
* Date: 7.05.2019 */

using namespace std;

class ingredients {		//Base class
protected:
	string name;
public:
	virtual float cost() const { return 0; };					//Virtual function			return de�eri kullan�lmayacak
};
class type1 : public ingredients {
	float pricepergrams;
	int weight;
public:
	void settype1(string ingredient, float per, int nweight) { name = ingredient; pricepergrams = per; weight = nweight; };
	float cost() const{ return pricepergrams * weight; };
};
class type2 : public ingredients {
	float priceperunit;
	int number;
public:
	void settype2(string ingredient, float per, int nnumber) { name = ingredient; priceperunit = per; number = nnumber; };
	float cost() const { return priceperunit * number; };
};
class type3 : public ingredients {
	float pricepermilliliter;
	int milliliter;
public:
	void settype3(string ingredient, float per, int nmilliliter) { name = ingredient; pricepermilliliter = per; milliliter = nmilliliter; };
	float cost() const { return pricepermilliliter * milliliter; };
};
float polymorphiccost(const ingredients & tp)
{
	return tp.cost();											//Polymorphic cost calculater
}
bool stockcontrol(int quantity, string name) {					//E�er stokta yeteri kadar varsa true d�nd�r�r
	bool result;
	ifstream stock;
	stock.open("stock.txt");

	int stype, scount;
	float sprice;
	string line;
	string sname;

	while (!stock.eof()) {
		getline(stock, line);
		istringstream buffer(line);

		getline(buffer, sname, '\t');
		buffer >> stype >> scount >> sprice ;

		if (name == sname) {
			break;
		}
	}
	
	if (quantity <= scount) {
		result = true;
	}
	else {
		result = false;
	}
	stock.close();
	return result;
} 
int findtype(string name) {				//Verilen malzemenin hangi type da oldu�unu belirliyor
	int result;
	ifstream stock;
	stock.open("stock.txt");

	int stype, scount;
	float sprice;
	string line;
	string sname;

	while (!stock.eof()) {
		getline(stock, line);
		istringstream buffer(line);

		getline(buffer, sname, '\t');
		buffer >> stype >> scount >> sprice;

		if (name == sname) {
			break;
		}
	}
	result = stype;
	stock.close();
	return result;
}
float findprice(string name) {		//Verilen malzemenin birim fiyat�n� float olarak d�nd�r�r
	float result;
	ifstream stock;
	stock.open("stock.txt");

	int stype, scount;
	float sprice;
	string line;
	string sname;

	while (!stock.eof()) {
		getline(stock, line);
		istringstream buffer(line);

		getline(buffer, sname, '\t');
		buffer >> stype >> scount >> sprice;

		if (name == sname) {
			break;
		}
	}
	result = sprice;
	stock.close();
	return result;
}
void stockdecrease(string name, int value) {		//name olarak Verilen �r�n� value de�eri kadar stocktan azalt�r
	int row;
	int i = 0;
	ifstream stock;
	stock.open("stock.txt");

	int stype, scount;
	float sprice;
	string line;
	string sname;

	int ftype, fcount;
	float fprice;

	vector<string> list;						//Stock dosyas�n� vectorde tutup d�zenlemelerden sonra yeniden yazd�rd�m

	while (!stock.eof()) {
		getline(stock, line);
		list.push_back(line);
		istringstream buffer(line);
		getline(buffer, sname, '\t');
		buffer >> stype >> scount >> sprice;

		if (name == sname) {
			row = i;
			ftype = stype;
			fcount = scount;
			fprice = sprice;
		}
		i++;
	}
	
	stock.close();

	fcount -= value;
	
	stringstream saa;
	saa << ftype;
	string st = saa.str();
	
	stringstream sbb;
	sbb << fcount;
	string sc = sbb.str();
	
	stringstream scc;
	scc << fprice;
	string sp = scc.str();
	

	string reline = "";
	reline.append(name);
	reline.append("\t");
	reline.append(st);
	reline.append("\t");
	reline.append(sc);
	reline.append("\t");
	reline.append(sp);
	list[row] = reline;

	ofstream stock2;
	stock2.open("stock.txt");
	for (int k = 0; k < i; k++) {
		stock2 << list[k] << "\n";
	}
	stock2.close();
}
/*Verilen menudeki urunleri mesela "massala chicken" menuden kontrol edip her bir �r�n� stockta kontrol edip varl���n� tesbit ediyor.

 */


float menucost(string menuname, int count, int control) {
	int totalcost = 0;
	ifstream menu;
	menu.open("menu.txt");
	string line, name, tmp1, tmp2;
	string ingredients;
	menu >> tmp1 >> tmp2;				//Dosyan�n ba��ndaki ba�l�klar� tmpe ald�m
	/*name: Yeme�in ad� 
	ingredients: i�indeki �r�nlerin s�rayla ge�ti�i string*/

	//Polymorphism
	bool noerror=true;
	bool complex=false;
	
	while (!menu.eof()) {
		getline(menu, line);
		istringstream buffer(line);
		getline(buffer, name, '\t');
					
		string lastingredient;
		if (name == menuname) {
			//cout << name << endl;
			while (1) {
				lastingredient = ingredients;
				getline(buffer, ingredients, ',');

                if(ingredients[ingredients.length()-1]=='\r'){
                    ingredients.pop_back();
                }
				
				//POLYMORPHISM ==> polymorphiccost fonksiyonuna type1,2,3 objelerini gonderdigimde her birisi icin farkl� islemler yapt�rabiliyor
				
				if (ingredients == "N/A") {										//Tek icerigi olan urunler
					//cout << "Paket urunler" <<endl;
					//cout << "Stock: " << stockcontrol(count, name) << endl;	//Stockta var mi
					if (stockcontrol(count, name) == 1) {						//icerisinde var
						if (findtype(name) == 1) {
							type1 product;
							product.settype1(name,findprice(name), count);
							totalcost = polymorphiccost(product);
						}else if (findtype(name) == 2) {
							type2 product;
							product.settype2(name, findprice(name), count);
							totalcost = polymorphiccost(product);
						}
						else if (findtype(name) == 3) {
							type3 product;
							product.settype3(name, findprice(name), count);
							totalcost = polymorphiccost(product);					
						}
						if (control == 0) {
							stockdecrease(name, count);		//stoktan dusurme islemi yap�lacak
						}				
					}
					break;
				}
				else if (ingredients == lastingredient) {						//satir sonu korumasi
					break;
				}
				else {
					complex = true;
					//��indekilerin s�rayla akt��� scope
					//cout << ingredients << endl;
					int currentcount;
					string currentper, currentname,currentname2;
					istringstream parser(ingredients);
					parser >> currentcount >> currentper;
					if (currentper == "gram" || currentper == "ml") {
						parser >> currentname;
						if (currentname == "olive" || currentname == "green" || currentname == "brown" ) {
							parser >> currentname2;
							currentname.append(" ");
							currentname.append(currentname2);
						}						
					}
					else if (currentper == "red") {
						parser >> currentname2;
						currentname = currentper;
						currentname.append(" ");
						currentname.append(currentname2);
					}
					else {
						currentname = currentper;
					}
					//currentcount: i�indekilerin miktar� currentname: i�indekilerin ad�
					//cout << count*currentcount << "," << currentname <<"=" <<stockcontrol(count*currentcount,currentname) << endl;
					if (stockcontrol(count*currentcount, currentname) == false) {
						noerror = false;
						break;
					}
					
				}
			}
		}
	}

	menu.close();
	
	menu.open("menu.txt");

	if (complex && noerror) {				//E�er menuden secilen �r�n complex:(icerisinde birden fazla malzeme var noerror:stokta yeterince varsa stoktan dusmesi icin)
		while (!menu.eof()) {
			getline(menu, line);
			istringstream buffer(line);
			getline(buffer, name, '\t');

			string lastingredient;
			if (name == menuname) {
				while (1) {
					lastingredient = ingredients;
					getline(buffer, ingredients, ',');	
					
					//Sonradan ekledim kontrol etmen gerek
					if(ingredients[ingredients.length()-1]=='\r'){
                    	ingredients.pop_back();
                	}
														
					if (ingredients == lastingredient) {						//Sat�r sonu korumas�
						break;
					}
					else {
						int currentcount;
						string currentper, currentname, currentname2;
						istringstream parser(ingredients);
						parser >> currentcount >> currentper;
						if (currentper == "gram" || currentper == "ml") {
							parser >> currentname;
							if (currentname == "olive" || currentname == "green" || currentname == "brown") {
								parser >> currentname2;
								currentname.append(" ");
								currentname.append(currentname2);
							}
						}
						else if (currentper == "red") {
							parser >> currentname2;
							currentname = currentper;
							currentname.append(" ");
							currentname.append(currentname2);
						}
						else {
							currentname = currentper;
						}
						//currentcount: i�indekilerin miktar� currentname: i�indekilerin ad�
						//cout << count * currentcount << "," << currentname << "=" << stockcontrol(count*currentcount, currentname) << endl;
						if (findtype(currentname) == 1) {
							type1 product;
							product.settype1(currentname, findprice(currentname), count*currentcount);
							totalcost += polymorphiccost(product);
						}else if (findtype(currentname) == 2) {
							type2 product;
							product.settype2(currentname, findprice(currentname), count*currentcount);
							totalcost += polymorphiccost(product);
						}
						else if (findtype(currentname) == 3) {
							type3 product;
							product.settype3(currentname, findprice(currentname), count*currentcount);
							totalcost += polymorphiccost(product);
						}
						if (control == 0) {
							stockdecrease(currentname, count*currentcount);		//D�KKAT STOCKTAN D��ME ��LEM� BURDA YAPILACAK
						}
					}
				}
			}
		}
	}
	menu.close();
	return totalcost;
}
int main() {
	ifstream order;
	order.open("order.txt");
	string line;
	int count,linenumber; string name,table;
	
	while (!order.eof()) {
		order >> table;
		order >> linenumber;

		cout << table << " ordered:" << endl;						//Hangi masa oldu�unu
		
		float tip = 0, totalcost = 0;							//Her masa i�in s�f�rlay�caz tip ve total costu

		for (int i = 0; i < linenumber; i++) {
			order >> count;
			getline(order, line);
			istringstream buffer(line);
			getline(buffer, name, '\t');
			name.erase(name.begin());						//Name'lerin ba��nda bo�luk oldu�u i�in yanl�� �al���yordu ilk karakteri sildim				 		  
			
            if(name[name.length()-1]=='\r'){
                    name.pop_back();
                }
            												//Kontrol edicez e�er yeterli yoksa yoktur yaz�cak	
			if (menucost(name, count,1) == 0) {
				cout << "We don't have enough " << name << endl ;
			}
			else {
				int tc = menucost(name, count, 0);
				cout << count << " " << name << " cost: " << tc;
				cout << endl;
				totalcost += tc;
			}
		}
		tip = totalcost * 0.15;
		float tax= totalcost * 0.08;
		totalcost += tip + tax ;

		cout << "Tip is " << tip << endl ;
		cout << "Total cost: " << totalcost << " TL" << endl ;
		cout << "**************************" << endl ;
	}
			
	order.close();
	return 0;
}
