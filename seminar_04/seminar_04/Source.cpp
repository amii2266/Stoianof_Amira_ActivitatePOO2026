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
	~Prajitura(); //declarare destructor 
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


	cout << calculeazaPretPerIngredient(p);
}