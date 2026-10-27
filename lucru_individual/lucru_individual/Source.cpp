#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Magazin {
private:
	const int idMagazin; //nu este dat de nimeni, este generat din contor;
	char* nume;
	static int contor;
	int nrProduse;
	float* preturiProduse;
public:
	//constructor fara parametri
	Magazin():idMagazin(contor++) {
		this->nume = new char[strlen("NA") + 1];
		strcpy(this->nume, "NA");
		this->nrProduse=0;
		this->preturiProduse = NULL;
	}
	//constr cu parametri, aici se folosesc alte nume de variabile ca parametru
	Magazin(const char* numeInit, int nrInit, const float* preturiInit) :idMagazin(contor++) {
		this->nume = new char[strlen(numeInit) + 1];
		strcpy(this->nume, numeInit);
		this->nrProduse = nrInit;
		this->preturiProduse = new float[nrInit];
		//facem for pt ca este un vector dinamic
		for (int i = 0;i < nrInit;i++) {
			this->preturiProduse[i] = preturiInit[i];
		}
	}
	//constr de copiere
	Magazin(const Magazin& m) :idMagazin(contor++) {
		this->nume = new char[strlen(m.nume) + 1];
		strcpy(this->nume, m.nume);
		this->nrProduse = m.nrProduse;
		this->preturiProduse = new float[m.nrProduse];
		for (int i = 0;i <m.nrProduse;i++){
			this->preturiProduse[i] = m.preturiProduse[i];
		}

	}
	//destructor, il facem pt char* si float*
	~Magazin() {
		delete[] this->nume;
		delete[] this->preturiProduse;
	}
	//get si set 
	int getId() {
		return this->idMagazin;
	}
	int getNrProduse() {
		return this->nrProduse;
	}
	char* getNume() {
		char* copieNume = new char[strlen(this->nume) + 1];
		strcpy(copieNume, this->nume);
		return copieNume;
	}
	void setNume(char* nume) {
		//strg ce era inainte
		if (this->nume != nullptr)
		{
			delete[] this->nume;
		}
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}
	//setter pe tot vectorul(nr+vector)
	void setPreturiProduse(int nrNou, float* preturiNoi) {
		//stergem 
		if (this->preturiProduse != nullptr) {
			delete[]this->preturiProduse;
		}
		this->nrProduse = nrNou;
		this->preturiProduse = new float[nrNou];
		for (int i = 0;i < nrNou;i++)
		{
			this->preturiProduse[i] = preturiNoi[i];
		}
	}
	static int getContor() {
		return contor;
	}
	void afisare() {
		cout << "ID: " << this->idMagazin << endl;
		cout << "Nume: " << this->nume << endl;
		cout << "Nr produse: " << this->nrProduse << endl;
		cout << "Preturi: ";
		for (int i = 0;i < this->nrProduse;i++) {
			cout << this->preturiProduse[i] << " ";
		}
		cout << endl << endl;
	}
};
int Magazin::contor = 1;
int main() {
	float p[3] = { 10.5,25,40 };
	char nume1[] = "Mega Image";
	char nume2[] = "Profi";
	Magazin m1;//fara parametri
	Magazin m2(nume1, 3, p);//cu param
	Magazin m3(m2);//copiere
	cout << "m1,m2,m3" << endl;
	m1.afisare();
	m2.afisare();
	m3.afisare();
}