#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

class Prajitura {
private:
	char* denumire;
	float pret;
	int cantitate;
	bool dePost;
	int nrIngrediente;
	string* ingrediente;
	const int id;
	static int contor;
public:
	friend class Student;
	Prajitura() :id(contor++) {
		this->denumire = new char[strlen("Tiramisu") + 1];
		strcpy(denumire, "Tiramisu");
		this->pret = 15;
		this->cantitate = 250;
		this->dePost = true;
		this->nrIngrediente = 3;
		this->ingrediente = new string[this->nrIngrediente];
		this->ingrediente[0] = "piscoturi";
		this->ingrediente[1] = "vanilie";
		this->ingrediente[2] = "cafea";
	}
	Prajitura(const char* denumire, float pret) :id(contor++) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
		this->cantitate = 250;
		this->dePost = true;
		this->nrIngrediente = 3;
		this->ingrediente = new string[this->nrIngrediente];
		this->ingrediente[0] = "piscoturi";
		this->ingrediente[1] = "vanilie";
		this->ingrediente[2] = "cafea";
	}


	Prajitura(const Prajitura& p) :id(contor++) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
		this->cantitate = p.cantitate;
		this->dePost = p.dePost;
		this->nrIngrediente = p.nrIngrediente;

		this->ingrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente;i++)
		{
			this->ingrediente[i] = p.ingrediente[i];
		}

	}
	~Prajitura();//declarare destructor
	//operatorul egal
	Prajitura& operator=(const Prajitura& p1) {
		if (this != &p1) {

			this->cantitate = p1.cantitate;
			if (this->denumire) {
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(p1.denumire) + 1];
			strcpy(this->denumire, p1.denumire);
			this->dePost = p1.dePost;
			this->pret = p1.pret;
			this->nrIngrediente = p1.nrIngrediente;
			if (this->ingrediente) {
				delete[] this->ingrediente;
			}
			this->ingrediente = new string[this->nrIngrediente];
			for (int i = 0;i < p1.nrIngrediente;i++) {
				this->ingrediente[i] = p1.ingrediente[i];
			}
		}
		return *this;//adica returnez obiectul

	}
	//facem getter pt ca acum cantitate este in private si are nevoie de getter ca sa fie accesat
	int getCantitate() {
		return this->cantitate;
	}
	int getNrIngrediente() {
		return this->nrIngrediente;

	}
	float getPret() {
		return this->pret;
	}
	static int getContor() {
		return contor;
	}
	//op +, param prin referinta pt evitarea apelarii constr de copiere 
	Prajitura operator+(const Prajitura& p) {
		Prajitura result = *this;//am apelat constr de copiere a.i sa creeze prajitura result din this
		result.pret = this->pret + p.pret;
		result.cantitate = this->cantitate + p.cantitate;
		return result;
	}
	void afisare()
	{
		cout << "Denumire: " << this->denumire << endl;
		cout << "Pret: " << this->pret << endl;
		cout << "Cantitate: " << this->cantitate << endl;
		cout << "De Post: " << (this->dePost ? "DA" : "NU") << endl;
		cout << "Nr ingrediente: " << this->nrIngrediente << endl;
		cout << "Ingredientele sunt: ";
		for (int i = 0;i < this->nrIngrediente;i++)
		{
			cout << this->ingrediente[i] << "; ";
		}
		cout << endl;

	}
	float costMediuGram() {
		if (this->cantitate == 0) {
			return 0;
		}
		else {
			return this->pret / this->cantitate;
		}
	}

	void modificaDenumire(const char* denumire) {
		delete this->denumire;

		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}


};
int Prajitura::contor = 100; //:: este operator de rezolutie
//destructor 


Prajitura::~Prajitura() {
	delete[] this->denumire;
	delete[] this->ingrediente;
}
float calculeazaCantitateTotala(Prajitura* prajituri, int nr_prajituri) {
	float greutate = 0;

	for (int p = 0; p < nr_prajituri; p++)
		greutate += prajituri[p].getCantitate();

	return greutate;
}

float calculeazaPretPerIngredient(Prajitura p) {
	if (p.getNrIngrediente() != 0)
	{
		return p.getPret() / p.getNrIngrediente();
	}

}
//facem o noua casa
class Student {
private:
	string nume;
	Prajitura prajitura;
	int nrTotal;
public:
	Student() {
		this->nume = "Andrei";
	}
	Student(string nume, Prajitura p) {
		this->nume = nume;
		this->prajitura = p;
	}
	//getter si setter
	string getNume() {
		return this->nume;
	}
	Prajitura getPrajitura() {
		return this->prajitura;
	}
	void setNume(string nume) {
		this->nume = nume;
	}
	void setPrajitura(Prajitura p) {
		this->prajitura = p;

	}

	//vom primica parametru cate calorii avem per gram
	//calculeaza nr total calorii
	float calculeazaNrTotalCalorii(float caloriiPerGram) {
		float nrTotal = caloriiPerGram * this->prajitura.getCantitate();
		return nrTotal;
	}
	void afiseazaMasa() {
		cout << this->nume << " mananca prajitura: " << this->prajitura.denumire << endl;
	}
};
void main() {

	/*Prajitura p2("Amandina",40);
	p2.afisare();
	Prajitura p;
	p.afisare();
	cout<<p.costMediuGram();
	Prajitura* prajituri;
	prajituri = new Prajitura[3];
	prajituri[2].afisare();
	prajituri[1].pret = 50;
	prajituri[2].cantitate = 70;

	prajituri[0].modificaDenumire("tort");
	prajituri[1].modificaDenumire("ecler");

	for (int i = 0;i < 3;i++) {
		cout << prajituri[i].denumire << ' ' << prajituri[i].costMediuGram() << endl;
	}


	float greutate_totala = calculeazaCantitateTotala(prajituri, 3);
	cout << "Total: " << greutate_totala << endl;*/

	Prajitura p;
	p.afisare();
	Prajitura::getContor();
	Prajitura p1("Tiramisu", 22);
	Student s1("Cristi", p1);
	cout << s1.calculeazaNrTotalCalorii(0.5) << endl;
	s1.afiseazaMasa();
	cout << endl;
	p = p1;
	p1 = p1;


	cout << calculeazaPretPerIngredient(p);
}