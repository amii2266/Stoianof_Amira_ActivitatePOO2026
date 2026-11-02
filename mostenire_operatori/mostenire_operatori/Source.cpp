#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Cafenea {
private:
	char* nume;
	int nrProduse;
	float* preturiProduse;
	bool deschisa;
	const int id;
	static int contor;
public:
	friend class Client;
	//constructor fara parametri
	Cafenea() : id(contor++) {
		this->nume = new char[strlen("NA") + 1];
		strcpy(this->nume, "NA");
		this->nrProduse = 0;
		this->preturiProduse = NULL;//vectorul este gol
		this->deschisa = false;

	}
	//constructor cu parametri, dam ca parametri copii ale atributelor, la fel ca la fara parametri, dar initializam cu copiile 
	Cafenea(const char* numeInit, int nrProduseInit, const float* preturiProduseInit, bool deschisaInit) :id(contor++) {
		this->nume = new char[strlen(numeInit) + 1];
		strcpy(this->nume, numeInit);
		this->nrProduse = nrProduseInit;
		this->preturiProduse = new float[nrProduseInit];//initializam vectorul cu dimensiunea primita ca parametru
		for (int i = 0;i < nrProduseInit; i++) {
			this->preturiProduse[i] = preturiProduseInit[i];//copiem elementele din vectorul primit ca parametru in vectorul nostru
		}
		this->deschisa = deschisaInit;

	}
	//constructor de copiere, la fel ca la constructorul cu parametri, dar initializam cu c.
	Cafenea(const Cafenea& c) : id(contor++) {
		this->nume = new char[strlen(c.nume) + 1];
		strcpy(this->nume, c.nume);
		this->nrProduse = c.nrProduse;
		this->preturiProduse = new float[c.nrProduse];
		for (int i = 0;i < c.nrProduse;i++)
		{
			preturiProduse[i] = c.preturiProduse[i];
		}
		this->deschisa = c.deschisa;

	}
	//definim destructorul, care va dezaloca memoria alocata pentru nume si preturiProduse
	~Cafenea();
	//operatorul =, luam o parte din definitia constructorului de copiere, si dezalocam memoria alocata pentru nume si preturiProduse, apoi copiem valorile din obiectul c in obiectul curent
	Cafenea& operator=(const Cafenea& c) {
		if (this != &c) {//verificam daca obiectul curent nu este acelasi cu obiectul c, pentru a evita auto-asignarea
			if (this->nume != NULL) {
				delete[] this->nume;
			}
			if (this->preturiProduse != NULL) {
				delete[] this->preturiProduse;
			}
			this->nume = new char[strlen(c.nume) + 1];
			strcpy(this->nume, c.nume);
			this->nrProduse = c.nrProduse;
			this->preturiProduse = new float[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++) {
				this->preturiProduse[i] = c.preturiProduse[i];
			}
			this->deschisa = c.deschisa;
		}
		return *this;
	}

	//getter si setter 
	char* getNume() {
		char* copie = new char[strlen(this->nume) + 1];
		strcpy(copie, this->nume);
		return copie;
	}
	void setNume(char* nume) {
		//pas 1: dezalocam memoria alocata pentru nume
		if (this->nume != NULL) {
			delete[] this->nume;
		}
		//pas 2: alocam memoria pentru nume
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}
	float getPret(int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrProduse && this->preturiProduse != NULL) {
			return this->preturiProduse[pozitie];
		}
		return 0;
	}
	//setter pe vectorul de preturi, primeste ca parametru dimensiunea si vectorul de preturi
	void setPreturi(int nrProduseNoi, float* preturiProduseNoi) {
		//pas 1: dezalocam memoria alocata pentru preturiProduse
		if (this->preturiProduse != NULL) {
			delete[] this->preturiProduse;
		}
		this->nrProduse = nrProduseNoi;
		//pas 2: alocam memoria pentru preturiProdusenoi
		this->preturiProduse = new float[nrProduseNoi];
		for (int i = 0; i < nrProduseNoi;i++) {
			this->preturiProduse[i] = preturiProduseNoi[i];
		}

	}
	int getNrProduse() {
		return this->nrProduse;
	}
	static int getContor() {
		return contor;
	}
	//int getNrProduseIeftine(float val): câte produse costă mai puțin decât val
	int getNrProduseIeftine(float val) {
		int count = 0;
		for (int i = 0; i < this->nrProduse; i++) {
			if (this->preturiProduse[i] < val) {
				count++;
			}
		}
		return count;
	}
	//float pretMediu(): cu protecție la împărțirea cu 0
	float pretMediu() {
		if (this->nrProduse == 0) {
			return 0;
		}
		float suma = 0;
		for (int i = 0; i < this->nrProduse; i++) {
			suma += this->preturiProduse[i];
		}
		return suma / this->nrProduse;
	}
	//float pretMaxim()
	float pretMaxim() {
		if (this->nrProduse == 0) {
			return 0;
		}
		float max = this->preturiProduse[0];
		for (int i = 1; i < this->nrProduse; i++) {
			if (this->preturiProduse[i] > max) {
				max = this->preturiProduse[i];
			}
		}
		return max;
	}
	//operatorul << pentru afisare, accesam atributele private ale clasei, deci trebuie sa fie friend
	friend ostream& operator<<(ostream& out, Cafenea& c) {
		out << "Nume: " << c.nume << endl;
		out << "Numar produse: " << c.nrProduse << endl;
		out << "Preturi produse: ";
		for (int i = 0; i < c.nrProduse; i++) {
			out << c.preturiProduse[i] << " ";
		}
		out << endl;
		out << "Deschisa: " << c.deschisa << endl;
		out << "ID: " << c.id << endl;
		return out;
	}
	//operatorul >> pentru citire, accesam atributele private ale clasei, deci trebuie sa fie friend
	friend istream& operator>>(istream& in, Cafenea& c) {
		//buffer pentru citirea numelui
		char buffer[100];
		cout << "Introduceti numele cafenelei: ";
		in >> buffer;
		//pas 1: dezalocam memoria alocata pentru nume
		if (c.nume != NULL) {
			delete[] c.nume;
		}
		//pas2: alocam memoria pentru nume
		c.nume = new char[strlen(buffer) + 1];
		strcpy(c.nume, buffer);
		cout << "Introdu nr de produse ";
		in >> c.nrProduse;
		// pas 3: dezalocam memoria alocata pentru preturiProduse
		if (c.preturiProduse != NULL) {
			delete[] c.preturiProduse;
		}
		//pas 4: alocam memoria pentru preturiProduse
		c.preturiProduse = new float[c.nrProduse];
		for (int i = 0;i < c.nrProduse;i++) {
			cout << "Introduceti pretul produsului " << i + 1 << ": ";
			in >> c.preturiProduse[i];
		}
		cout << "Este deschisa? (1 pentru da, 0 pentru nu): ";
		in >> c.deschisa;
		return in;
	}
	//operatorul +, 
	Cafenea operator+(const Cafenea& c) {
		Cafenea rezultat = *this;
		delete[] rezultat.preturiProduse;
		rezultat.nrProduse = this->nrProduse + c.nrProduse;
		rezultat.preturiProduse = new float[rezultat.nrProduse];
		for (int i = 0; i < this->nrProduse; i++)//copiem din this in rezultat
		{
			rezultat.preturiProduse[i] = this->preturiProduse[i];
		}
		for (int i = 0; i < c.nrProduse; i++)//copiem din c in rezultat, incepand de la pozitia this->nrProduse, adica dupa ultimul element copiat din this/
		{
			rezultat.preturiProduse[this->nrProduse + i] = c.preturiProduse[i];
		}
		return rezultat;
	}

};
int Cafenea::contor = 0;
//destructorul:
Cafenea::~Cafenea() {
	delete[] this->nume;
	delete[] this->preturiProduse;
}
//float calculeazaPretTotal(Cafenea* v, int n) adună prețurile tuturor produselor din toate cafenelele.
// Fără acces la private, deci folosești getteri.
float calculeazaPretTotal(Cafenea* v, int n) {
	float suma = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v[i].getNrProduse(); j++) {
			suma += v[i].getPret(j);
		}
	}
	return suma;
}
//facem o clasa noua
class Client {
private:
	string nume;
	Cafenea cafenea;
	int nrVizite;
public:
	//constructor fara parametri
	Client() {
		this->nume = "NA";
		this->nrVizite = 0;
	}
	//CONSTR CU PARAMETRI
	Client(string numeInit, Cafenea cafeneaInit, int nrViziteInit) {
		this->nume = numeInit;
		this->cafenea = cafeneaInit;
		this->nrVizite = nrViziteInit;
	}
	//geter si setter pentru nume
	string getNume() {
		return this->nume;
	}
	void setNume(string nume) {
		this->nume = nume;
	}
	//getter si setter pentru cafenea
	Cafenea getCafenea() {
		return this->cafenea;
	}
	void setCafenea(Cafenea c) {
		this->cafenea = c;
	}
	//În Client scrie afiseazaComanda(), care afișează nume și this->cafenea.nume direct, fără getter.
	void afiseazaComanda() {
		cout << "Nume client: " << this->nume << endl;
		cout << "Nume cafenea: " << this->cafenea.nume << endl;
	}
	//operator << pentru afisare, afiseaza nume, cafenea.nume si nrVizite
	friend ostream& operator<<(ostream& out, Client& c) {
		out << "Nume client: " << c.nume << endl;
		char* numeCafenea = c.cafenea.getNume();   // getNume() returneaza o COPIE
		out << "Nume cafenea: " << numeCafenea << endl;
		delete[] numeCafenea;                      // dezalocam copia
		out << "Numar vizite: " << c.nrVizite << endl;
		return out;
	}
};
int main() {
	cout << "1. Constructor fara parametri  << endl;
		Cafenea c1;
	cout << c1 << endl;

	cout << "2. Constructor cu parametri " << endl;
	float preturi[] = { 10.5f, 12.0f, 8.0f, 15.5f };
	Cafenea c2("Starbucks", 4, preturi, true);
	cout << c2 << endl;

	cout << "3. Constructor de copiere " << endl;
	Cafenea c3 = c2;
	cout << c3 << endl;

	cout << " 4. Operator = " << endl;
	c1 = c3;
	cout << c1 << endl;
}