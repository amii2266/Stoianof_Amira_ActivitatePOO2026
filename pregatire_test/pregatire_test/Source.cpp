#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Vapor {
private:
	int capacitate;
	int nrPersoaneImbarcate;
	int* varstePasageri;
	char* nume;
	float pretBilet;
public:
	//constructor fara parametri
	Vapor() {
		this->capacitate = 100;
		this->nrPersoaneImbarcate = 0;
		this->varstePasageri = NULL;
		this->nume = new char[strlen("NA") + 1];
		strcpy(this->nume, "NA");
		this->pretBilet = 0;
	}
	
	//la validari, verificam
	//constructor cu parametri cu validari, nrPersoaneImbarcate nu poate fi mai mare decat capacitatea, pretBilet nu poate fi negativ, vectorul de varste nu poate fi NULL, numele nu poate fi NULL
	Vapor(int capacitateInit, int nrPersoaneImbarcateInit, int* varstePasageriInit, const char* numeInit, float pretBiletInit) {
		if (capacitateInit > 0) {
			this->capacitate = capacitateInit;
		}
		else {
			this->capacitate = 100;
		}
		if (nrPersoaneImbarcateInit > 0 && nrPersoaneImbarcateInit <= this->capacitate && varstePasageriInit != NULL) {
			this->nrPersoaneImbarcate = nrPersoaneImbarcateInit;
			this->varstePasageri = new int[nrPersoaneImbarcateInit];
			for (int i = 0; i < nrPersoaneImbarcateInit; i++) {
				this->varstePasageri[i] = varstePasageriInit[i];
			}
		}
		else {
			this->nrPersoaneImbarcate = 0;
			this->varstePasageri = NULL;
		}
		if (numeInit != NULL) {
			this->nume = new char[strlen(numeInit) + 1];
			strcpy(this->nume, numeInit);
		}
		else {
			this->nume = new char[strlen("NA") + 1];
			strcpy(this->nume, "NA");
		}
		if (pretBiletInit >= 0) {
			this->pretBilet = pretBiletInit;
		}
		else {
			this->pretBilet = 0;
		}
	}
	//constructorul de copiere 
	Vapor(const Vapor& v) {
		this->capacitate = v.capacitate;
		this->nrPersoaneImbarcate = v.nrPersoaneImbarcate;
		this->varstePasageri = new int[v.nrPersoaneImbarcate];
		for (int i = 0; i < v.nrPersoaneImbarcate; i++) {
			this->varstePasageri[i] = v.varstePasageri[i];
		}
		this->nume = new char[strlen(v.nume) + 1];
		strcpy(this->nume, v.nume);
		this->pretBilet = v.pretBilet;
	}
	//destructor
	~Vapor() {
		if (this->varstePasageri != NULL) {
			delete[] this->varstePasageri;
		}
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	//getter penntru nume
	char* getNume() {
		char* copieNume = new char[strlen(this->nume) + 1];
		strcpy(copieNume, this->nume);
		return copieNume;
	}
	//setter pt nume
	void setNume(const char* numeNou) {
		//pas 1 dezalocam memoria pentru nume
			if (this->nume != NULL) {
				delete[] this->nume;
		//pas 2 alocam memorie pentru numeNou si copiem valoarea
			this->nume = new char[strlen(numeNou) + 1];
			strcpy(this->nume, numeNou);
		}
	}
	//getter pentru pretBilet	
	float getPret() {
		return this->pretBilet;
	}
	//setter pt pret
	void setPret(float pretNou) {
		if (pretNou >= 0) {
			this->pretBilet = pretNou;
		}
	}
	//operatorul =
	Vapor& operator=(const Vapor& v) {
		//pas 1 verificam daca obiectul curent este diferit de obiectul care se copiaza
		if (this != &v) {
			this->capacitate = v.capacitate;
			this->nrPersoaneImbarcate = v.nrPersoaneImbarcate;
			if (this->varstePasageri != NULL) {
					delete[] this->varstePasageri;
			}
			this->varstePasageri = new int[v.nrPersoaneImbarcate];
			for (int i = 0; i < v.nrPersoaneImbarcate; i++) {
				this->varstePasageri[i] = v.varstePasageri[i];
			}
			if (this->nume != NULL) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(v.nume) + 1];
			strcpy(this->nume, v.nume);
			this->pretBilet = v.pretBilet;
		}
		return *this;
	}
	//operatorul << pentru afisare
	friend ostream& operator<<(ostream& out, const Vapor& v) {
		out << "Nume: " << v.nume << endl;
		out << "Capacitate: " << v.capacitate << endl;
		out << "Numar persoane imbarcate: " << v.nrPersoaneImbarcate << endl;
		out << "Varste pasageri: ";
		for (int i = 0; i < v.nrPersoaneImbarcate; i++) {
			out << v.varstePasageri[i] << " ";
		}
		out << endl;
		out << "Pret bilet: " << v.pretBilet << endl;
		return out;
	}
};