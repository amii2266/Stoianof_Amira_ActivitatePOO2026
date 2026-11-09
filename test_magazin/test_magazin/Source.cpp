#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class Produs {
private:
	static int contor;
	const int codProdus;
	string denumire;
	double pret;
	int* noteRecenzii;
	int nrRecenzii;
public:
	//constr fara param
	Produs() :codProdus(contor++) {
		this->denumire = "NA";
		this->pret = 0;
		this->noteRecenzii = NULL;
		this->nrRecenzii = 0;
	}
	//constr cu toti parametrii si validari
	Produs(string denumire, double pret, int* noteRecenzii, int nrRecenzii) :codProdus(contor++) {
		if (this->denumire != " ")
			this->denumire = denumire;
		else {
			this->denumire = "NA";
		}
		if (this->pret >= 0)
			this->pret = pret;
		else {
			this->pret = 0;
		}
		if (nrRecenzii >= 0 && noteRecenzii != NULL) {
			this->nrRecenzii = nrRecenzii;
			this->noteRecenzii = new int[nrRecenzii];
			for (int i = 0;i < nrRecenzii;i++) {
				this->noteRecenzii[i] = noteRecenzii[i];
			}
		}
		else {
			this->nrRecenzii = 0;
			this->noteRecenzii = NULL;
		}
	}
	//destructor
	~Produs() {
		if (this->noteRecenzii != NULL) {
			delete[]this->noteRecenzii;
		}
	}
	//constr de copiere
	Produs(const Produs& p) :codProdus(contor++) {
		this->denumire = p.denumire;
		this->pret = p.pret;
		this->nrRecenzii = p.nrRecenzii;
		if (p.nrRecenzii > 0 && p.noteRecenzii != NULL) {
			this->noteRecenzii = new int[p.nrRecenzii];
			for (int i = 0;i < p.nrRecenzii;i++) {
				this->noteRecenzii[i] = p.noteRecenzii[i];
			}
		}
		else {
			this->noteRecenzii = NULL;
		}
	}
	//operator =, jumate detsructor, jumate copiere, nu se copiaza cod prod
	Produs& operator=(const Produs& p) {
		if (this != &p) {
			if (this->noteRecenzii != NULL) {
				delete[]this->noteRecenzii;
			}
			this->denumire = p.denumire;
			this->pret = p.pret;
			this->nrRecenzii = p.nrRecenzii;
			if (p.nrRecenzii > 0 && p.noteRecenzii != NULL) {
				this->noteRecenzii = new int[p.nrRecenzii];
				for (int i = 0;i < p.nrRecenzii;i++) {
					this->noteRecenzii[i] = p.noteRecenzii[i];
				}
			}
			else {
				this->noteRecenzii = NULL;
			}
		}
		return *this;
	}
	//operator +=
	Produs& operator+=(int nota)//declaram cu tipul vectorului
	{
		//pas 1: realocam vectorul 
		int* aux = new int[this->nrRecenzii + 1];
		//pas2: copiem ce era inainte cu for
		for (int i = 0;i < this->nrRecenzii;i++) {
			aux[i] = this->noteRecenzii[i];
		}
		aux[this->nrRecenzii] = nota;
		//pas 3:dezalocam
		if (this->noteRecenzii != NULL) {
			delete[]this->noteRecenzii;
		}
		this->noteRecenzii = aux;
		this->nrRecenzii++;
		return *this;
	}
	//operator -=, SCADE O VALOARE DATA
	Produs& operator-=(double val) {
		if (this->pret > val) {
			this->pret -= val;
		}
		else {
			this->pret = 0;
		}
		return *this;
	}
	//operator -=, SCADE PRETUL ALTUI OBIECT, in loc de val, p.pret
	Produs& operator-=(const Produs& p) {
		if (this->pret > p.pret) {
			this->pret -= p.pret;
		}
		else {
			this->pret = 0;
		}
		return *this;
	}
	//operator ==, compara denumire,pret,nr recenzii
	bool operator==(const Produs& p) const {
		if (this->denumire != p.denumire) {
			return false;
		}
		//daca denumire era char, if (strcmp(this->denumire, p.denumire) != 0)
		if (this->pret != p.pret) {
			return false;
		}
		if (this->nrRecenzii != p.nrRecenzii) {
			return false;
		}
		return true;

	}
	//operator () fara paramtrii, media notelor
	double operator()() {
		double s=0;
		for (int i = 0;i < this->nrRecenzii;i++) {
			s += this->noteRecenzii[i];
		}
		return s / this->nrRecenzii;
	}
	//operator () cu parametru: pret dupa discount
	double operator()(double discount) {
		return this->pret - (discount / 100.0) * this->pret;
	}
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "----------------------" << endl;
		out << "Cod produs: " << p.codProdus << endl;
		out << "Denumire: " << p.denumire << endl;
		out << "Pret: " << p.pret << endl;
		out << "Numar recenzii: " << p.nrRecenzii << endl;
		out << "Note: ";
		for (int i = 0; i < p.nrRecenzii; i++) {
			out << p.noteRecenzii[i] << " ";
		}
		out << endl;
		out << "----------------------" << endl;
		return out;
	}
};
int Produs::contor = 0;
int main() {
	Produs p1;
	cout << p1 << endl;
	int note[] = { 5,4,3,2 };
	Produs p2("Laptop", 3000, note,4);
	cout << p2 << endl;
	Produs p4(p2);
	cout << "copie" << endl << p4 << endl;
	p1 = p2;
	cout << "dupa atribuire: " << endl << p1<<endl;
	//op +=
	p2 += 2;
	cout << "dupa +=" << endl << p2 << endl;
	//op -=
	p2 -= 500;
	cout << "pret dupa -= " << endl << p2 << endl;
	//op ==
	if (p1 == p4) {
		cout << "p1 este egal cu p4" << endl;
	}
	else {
		cout << "p1 diferit de p4 " << endl;
	}
	//op ()
	cout << "media notelor p4: " << p4() << endl;
	cout << "pret p4 cu discount 10% " << p4(10.0) << endl;
}