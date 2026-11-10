#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Prajitura {
private:
	static int contor;
	const int id;
	char* denumire;
	float pret;
	string* ingrediente;
	int nrIngrediente;
public:
	Prajitura() :id(contor++) {
		this->denumire = new char[strlen("NA") + 1];
		strcpy(this->denumire, "NA");
		this->pret = 0;
		this->nrIngrediente = 0;
		this->ingrediente = NULL;
	}
	Prajitura(const char* denumire, float pret, string* ingrediente, int nrIngrediente) :id(contor++) {
		if (denumire != NULL) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else {
			this->denumire = new char[strlen("NA") + 1];
			strcpy(this->denumire, "NA");
		}
		if (pret >= 0) {
			this->pret = pret;
		}
		else {
			this->pret = 0;
		}
		if (nrIngrediente > 0 && ingrediente != NULL) {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new string[nrIngrediente];
			for (int i = 0;i < nrIngrediente;i++) {
				this->ingrediente[i] = ingrediente[i];
			}
		}
		else {
			this->nrIngrediente = 0;
			this->ingrediente = NULL;
		}
	}
	~Prajitura() {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		if (this->ingrediente != NULL) {
			delete[]this->ingrediente;
		}
	}
	Prajitura(const Prajitura& p) :id(contor++) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
		if (p.nrIngrediente > 0 && p.ingrediente != NULL) {
			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new string[p.nrIngrediente];
			for (int i = 0;i < p.nrIngrediente;i++) {
				this->ingrediente[i] = p.ingrediente[i];
			}
		}
		else {
			this->ingrediente = NULL;
		}
	}
	//op =
	Prajitura& operator=(const Prajitura& p) {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		if (this->ingrediente != NULL) {
			delete[]this->ingrediente;
		}
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
		if (p.nrIngrediente > 0 && p.ingrediente != NULL) {
			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new string[p.nrIngrediente];
			for (int i = 0;i < p.nrIngrediente;i++) {
				this->ingrediente[i] = p.ingrediente[i];
			}
		}
		else {
			this->ingrediente = NULL;
		}
		return *this;

	}
	//getteri
	static int getContor() {
		return contor;
	}
	int getId() {
		return this->id;
	}
	const char* getDenumire() {
		return this->denumire;
	}
	float getPret() {
		return this->pret;
	}
	int getNrIngrediente() {
		return this->nrIngrediente;
	}
	string* getIngrediente() {
		return this->ingrediente;
	}

	//setteri
	void setDenumire(const char* denumireNou) {
		//pas 1: dezaloc
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		//pas2:alocam memorie noua
		this->denumire = new char[strlen(denumireNou) + 1];
		strcpy(this->denumire, denumireNou);
	}
	void setPret(float pretNou) {
		this->pret = pretNou;
	}
	void setIngrediente(int nrIngrediente, string* ingrediente) {
		if (this->ingrediente != NULL) {
			delete[]this->ingrediente;
		}
		this->nrIngrediente = nrIngrediente;
		this->ingrediente = new string[nrIngrediente];
		for (int i = 0;i < nrIngrediente;i++) {
			this->ingrediente[i] = ingrediente[i];
		}
	}
	//operator + pe 2 obiecte, adunam tot ce este numeric, apel: Masina m3 = m1 + m2;
	Prajitura operator+(const Prajitura& p) {
		Prajitura temp = *this;
		temp.pret = this->pret + p.pret;
		return temp;
	}

	//op +, obiect+nr , apel: Prajitura p2=p1+500;
	Prajitura operator+(float adaos) {
		Prajitura temp = *this;
		temp.pret=temp.pret+ adaos;
		return temp;
	}
	//op+, nr+obiect, apel: Masina m2 = 500 + m1;
	friend Prajitura operator+(float adaos, Prajitura p) {
		Prajitura temp = p;
		temp.pret += adaos;
		return temp;
	}
	//operator []
	string& operator[](int index) {
		if (index >= 0 && index < this->nrIngrediente) {
			return this->ingrediente[index];
		}
	}
	//operator de cast la float
	explicit operator float() {
		return this->pret;
	}
	//operator<<
	friend ostream& operator<<(ostream& out, const Prajitura& p) {
		out << "id: " << p.id << endl;
		out << "denumire: " << p.denumire << endl;
		out << "pret: " << p.pret << endl;
		out << "nr ingrediente: " << p.nrIngrediente << endl;
		for (int i = 0;i < p.nrIngrediente;i++) {
			out << p.ingrediente[i] << " " << endl;
		}
		out << endl;
		return out;
	}
};
int Prajitura::contor = 0;

class Comanda {
private:
	string numeClient;
	Prajitura* prajituri;//  tratat ca orice vector, tipul este prajitura
	int nrPrajituri;
public:
	//constr cy parametri
	Comanda(string numeClient, Prajitura* prajituri, int nrPrajituri) {
		this->numeClient = numeClient;
		this->nrPrajituri = nrPrajituri;
		this->prajituri = new Prajitura[nrPrajituri];
		for (int i = 0;i < nrPrajituri;i++) {
			this->prajituri[i] = prajituri[i];
		}

	}
	//constr de copiere
	Comanda(const Comanda& c) {
		this->numeClient = c.numeClient;
		this->nrPrajituri = c.nrPrajituri;
		this->prajituri = new Prajitura[c.nrPrajituri];
		for (int i = 0;i < c.nrPrajituri;i++) {
			this->prajituri[i] = c.prajituri[i];
		}
	}
	~Comanda() {
		if (this->prajituri != NULL) {
			delete[] this->prajituri;
		}
	}
};
int main() {
	Prajitura p1;
	cout << p1 << endl;
	string ing[] = {"Lapte", "Faina","Cafea"};
	Prajitura p2("Tiramisu", 20, ing, 3);
	//constr de copiere
	Prajitura p4(p2);
	cout << p4 << endl;
	//op =
	p1 = p2;
	cout << p1 << endl;
	//getter si setter
	cout << "denumire: " << p2.getDenumire() << endl;
	p2.setDenumire("ecler");
	p2.setPret(15);
	string ingNoi[] = { "Frisca", "Ciocolata" };
	p2.setIngrediente(2, ingNoi);
	cout << p2 << endl;
	//op+ pt 2 ob
	Prajitura p5 = p1 + p2;
	cout << "dupa op +: " << p5 << endl;
}