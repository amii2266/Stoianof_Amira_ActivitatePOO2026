#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Abonament {
private:
	static int nrAbonamente;
	const int id;
	string numeClient;
	float pretLunar;
	int* vizite;
	int nrLuni;
public:
	Abonament() :id(nrAbonamente++) {
		this->numeClient = "Anonim";
		this->pretLunar = 0;
		this->nrLuni = 0;
		this->vizite = NULL;

	}
	Abonament(string numeClient, float pretLunar, int nrLuni, int* vizite) :id(nrAbonamente++) {
		if (numeClient != " ") {
			this->numeClient = numeClient;
		}
		else {
			this->numeClient = "Anonim";
		}
		if (pretLunar > 0) {
			this->pretLunar = pretLunar;
		}
		else {
			this->pretLunar = 0;
		}
		if (nrLuni > 0 && vizite != NULL) {
			this->nrLuni = nrLuni;
			this->vizite = new int[nrLuni];
			for (int i = 0;i < nrLuni;i++) {
				this->vizite[i] = vizite[i];
			}
		}
		else {
			this->nrLuni = 0;
			this->vizite = NULL;
		}
	}
	Abonament(const Abonament& a) :id(nrAbonamente++) {
		this->numeClient = a.numeClient;
		this->pretLunar = a.pretLunar;
		if (a.nrLuni > 0 && a.vizite != NULL) {
			this->nrLuni = a.nrLuni;
			this->vizite = new int[a.nrLuni];
			for (int i = 0;i < a.nrLuni;i++) {
				this->vizite[i] = a.vizite[i];
			}
		}
		else {
			this->nrLuni = 0;
			this->vizite = NULL;
		}
	}

	~Abonament() {
		if (this->vizite != NULL) {
			delete[]this->vizite;
		}
	}
	//opretaor =
	Abonament& operator=(const Abonament& a) {
		if (this!=&a) {
			if (this->vizite != NULL) {
				delete[]this->vizite;
			}
		}
		this->numeClient = a.numeClient;
		this->pretLunar = a.pretLunar;
		if (a.nrLuni > 0 && a.vizite != NULL) {
			this->nrLuni = a.nrLuni;
			this->vizite = new int[a.nrLuni];
			for (int i = 0;i < a.nrLuni;i++) {
				this->vizite[i] = a.vizite[i];
			}
		}
		else {
			this->nrLuni = 0;
			this->vizite = NULL;
		}
		return *this;
	}
	//getteri
	static int getNumarAbonamente() { return nrAbonamente; }
	int getId() const { return this->id; }
	string getNumeClient() const { return this->numeClient; }
	float getPretLunar() const { return this->pretLunar; }
	int getNumarLuni() const { return this->nrLuni; }
	//setter pt nume 
	void setNumeClient(string numeClient) {
		if (numeClient != " ") {
			this->numeClient = numeClient;
		}
			
	}
	//op <<
	friend ostream& operator<<(ostream& out, const Abonament& a) {
		out << "Abonament #" << a.id << endl;
		out << "Client: " << a.numeClient << endl;
		out << "Pret lunar: " << a.pretLunar << " lei" << endl;
		out << "Numar luni: " << a.nrLuni << endl;
		out << "Vizite pe luna: ";
		if (a.vizite != NULL && a.nrLuni > 0) {
			for (int i = 0; i < a.nrLuni; i++) {
				out << a.vizite[i] << "; ";
			}
		}
		return out;
	}
	//op []
	int operator[](int index) {
		if (index >= 0 && index < this->nrAbonamente && this->vizite != NULL) {
			return this->vizite[index];
		}
		return -1;
	}
	//op += adauga o noua luna cu nr vizite
	Abonament& operator+=(int viz) {
		//vctr nou
		int* aux = new int[this->nrLuni + 1];
		//copiem
		for (int i = 0;i < this->nrLuni;i++) {
			aux[i] = this->vizite[i];
		}
		aux[this->nrLuni] = viz;
		//dezalocam
		if (this->vizite != NULL) {
			delete[]this->vizite;
		}
		this->vizite = aux;
		this->nrLuni++;
		return *this;

	}
	//op ==
	bool operator==(const Abonament& a) {
		if (this->numeClient != a.numeClient)
			return false;
		if (this->pretLunar != a.pretLunar)
			return false;
		if (this->nrLuni != a.nrLuni)
			return false;
		for (int i = 0;i < this->nrLuni;i++) {
			if (this->vizite[i] != a.vizite[i])
				return false;
		}
		return true;
	}
	//cast explicit la int cu nr total de vizite
	explicit operator int() {
		int s = 0;
		for (int i = 0;i < this->nrLuni;i++)
			s += this->vizite[i];
		return s;
	}
};
int Abonament::nrAbonamente = 0;
int main() {
	Abonament a1;
	cout << a1 <<endl;
	int viz[] = { 2,3,4 };
	Abonament a2("Andrei", 30, 3, viz);
	cout << a2 << endl;
	Abonament a4(a2);
	cout << "copie: " << endl << a4 << endl;
	//op =
	a1 = a2;
	cout <<"dupa op = "<<endl<< a1 << endl;
	//op []
	cout << a2[0] << endl;
	//op +=
	a2 += 30;
	cout << a2 << endl;
	//cast la int
	int s = (int)a2;
	cout << "total: " << s << endl;
	a2.setNumeClient("Ioana");
	cout << a2 << endl;

}