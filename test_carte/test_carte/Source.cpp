#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
class Carte {
private:
	static int numarCarti;
	const int idCarte;
	char* titlu;
	float pret;
	int* paginiPerCapitol;
	int numarCapitole;
public:
	//constr fara param
	Carte() :idCarte(numarCarti++) {
		this->titlu = new char[strlen("anonima") + 1];
		strcpy(this->titlu, "anonima");
		this->pret = 0;
		this->paginiPerCapitol = NULL;
		this->numarCapitole = 0;
	}
	//cnstr cu toti param cu validari
	Carte(const char* titlu, float pret, int* paginiPerCapitol, int numarCapitole) :idCarte(numarCarti++) {
		if (titlu != NULL && strlen(titlu) > 0) {
			this->titlu = new char[strlen(titlu) + 1];
			strcpy(this->titlu, titlu);
		}
		else {
			this->titlu = new char[strlen("anonima") + 1];
			strcpy(this->titlu, "anonima");
		}
		if (pret > 0) {
			this->pret = pret;
		}
		else { this->pret = 0; }
		if (numarCapitole > 0 && paginiPerCapitol != NULL) {
			this->numarCapitole = numarCapitole;
			this->paginiPerCapitol = new int[numarCapitole];
			for (int i = 0;i < numarCapitole;i++) {
				this->paginiPerCapitol[i] = paginiPerCapitol[i];
			}
		}
		else {
			this->paginiPerCapitol = NULL;
			this->numarCapitole = 0;
		}
	}
	//destructor
	~Carte() {
		if (this->titlu != NULL) {
			delete[] this->titlu;
		}
		if (this->paginiPerCapitol != NULL) {
			delete[] this->paginiPerCapitol;
		}
	}
	//constr de copiere
	Carte(const Carte& c) :idCarte(numarCarti++) {
		this->titlu = new char[strlen(c.titlu) + 1];
		strcpy(this->titlu, c.titlu);
		this->pret = c.pret;
		this->numarCapitole = c.numarCapitole;
		this->paginiPerCapitol = new int[c.numarCapitole];
		for (int i = 0;i < c.numarCapitole;i++) {
			this->paginiPerCapitol[i] = c.paginiPerCapitol[i];
		}

	}
	//operator =
	Carte& operator=(const Carte& c) {
		//dezalocam si verificam autoatribuirea
		if (this != &c) {
			if (this->titlu != NULL) {
				delete[] this->titlu;
			}
			if (this->paginiPerCapitol != NULL) {
				delete[] this->paginiPerCapitol;
			}
			this->titlu = new char[strlen(c.titlu) + 1];
			strcpy(this->titlu, c.titlu);
			this->pret = c.pret;
			this->numarCapitole = c.numarCapitole;
			this->paginiPerCapitol = new int[c.numarCapitole];
			for (int i = 0;i < c.numarCapitole;i++) {
				this->paginiPerCapitol[i] = c.paginiPerCapitol[i];
			}
		}
		return *this;

	}
	//operator[]
	int operator[](int index) {
		//verificam index>=0, index<nr, vectorul dif de null
		if (index >= 0 && index < numarCapitole && paginiPerCapitol != NULL) {
			return paginiPerCapitol[index];
		}
		return -1;
	}
	//operator de cast la int
	explicit operator int() {
		int s = 0;
		for (int i = 0;i < this->numarCapitole;i++)
		{
			s += paginiPerCapitol[i];
		}
		return s;
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const Carte& c) {
		out << "id carte: " << c.idCarte << endl;
		out << "titlu: " << c.titlu << endl;
		out << "pret: " << c.pret << endl;
		out << "numar capitole: " << c.numarCapitole << endl;
		for (int i = 0;i < c.numarCapitole;i++) {
			out << c.paginiPerCapitol[i] << " ";
		}
		out << endl;
		return out;
	}
	//operator>>
	friend istream& operator>>(istream& in, Carte& c) {
		//buffer pt nume
		char buffer[100];
		cout << "Introduceti titlul ";
		in >> buffer;
		//pas 1: dezalocare pt titlu
		if (c.titlu != NULL) {
			delete[]c.titlu;
		}
		//pas 2: alocare pt titlu
		c.titlu = new char[strlen(buffer) + 1];
		strcpy(c.titlu, buffer);
		cout << "Introduceti pretul: ";
		in >> c.pret;
		cout << "Introduceti nr de capitole ";
		in >> c.numarCapitole;
		//dezalocam memoria pt pagini
		if (c.paginiPerCapitol != NULL) {
			delete[]c.paginiPerCapitol;
		}
		//alocam memorie pt vector
		c.paginiPerCapitol = new int[c.numarCapitole];
		for (int i = 0;i < c.numarCapitole;i++) {
			in >> c.paginiPerCapitol[i];
		}
		return in;
	}
};
int Carte::numarCarti = 0;
int main() {
	//constr fara parametri
	Carte c1;
	cout << c1 << endl;
	//constr cu parametri
	int p[] = { 20,34,45,2 };
	Carte c2("Ion", 40, p, 4);
	//constr de copiere
	Carte c4(c2);
	cout << "Copie: " << endl << c4 << endl;
	//operator =
	c1 = c2;
	cout << "dupa atribuire: " << endl << c1 << endl;
	//operator []
	cout << c2[2] << endl;
	//operator de cast la int
	int total = (int)c2;
	cout << "total pagini c2: " << total << endl;
	//operator >>
	Carte c5;
	cin >> c5;
	cout << c5 << endl;
}