#define _CRT_SECURE_NO_WARNINGS
#include  <iostream>
using  namespace std;
class ContBancar {
private:
	static int numarConturi;
	const int idCont;
	string titularCont;
	double* istoricTranzactii;
	int numarTranzactii;
public:
	ContBancar():idCont(numarConturi++) {
		this->titularCont = "Necunoscut";
		this->numarTranzactii = 0;
		this->istoricTranzactii = NULL;

	}
	ContBancar(string titularCont, double* istoricTranzactii, int numarTranzactii) :idCont(numarConturi++) {
		if (this->titularCont != "") {
			this->titularCont = titularCont;
		}
		//la vector facem validari si pt nr
		if (this->numarTranzactii != 0 && this->istoricTranzactii != NULL) {
			this->numarTranzactii = numarTranzactii;
			this->istoricTranzactii = new double[numarTranzactii];
			for (int i = 0;i < numarTranzactii;i++) {
				this->istoricTranzactii[i] = istoricTranzactii[i];
			}
		}
		else {
			this->numarTranzactii = 0;
			this->istoricTranzactii = NULL;
		}
	}
	~ContBancar() {
		if (this->istoricTranzactii != NULL) {
			delete[] this->istoricTranzactii;
		}
	}
	ContBancar(const ContBancar& c):idCont(numarConturi++) {
		this->titularCont = c.titularCont;
		this->numarTranzactii = c.numarTranzactii;
		if (c.numarTranzactii != 0 && c.istoricTranzactii != NULL) {
			this->istoricTranzactii = new double[c.numarTranzactii];
			for (int i = 0;i < c.numarTranzactii;i++) {
				this->istoricTranzactii[i] = c.istoricTranzactii[i];
			}
		}
	}
	//getter si setter pt vector
	int getNumarTranzactii() {
		return this->numarTranzactii;
	}
	double* getIstoricTranzactii() {
		return this->istoricTranzactii;
	}
	void setIstoricTranzactii(int numarTranzactii, double* istoricTranzactii) {
		if (this->numarTranzactii > 0 && this->istoricTranzactii != NULL) {
			if (this->istoricTranzactii != NULL)
				delete[] this->istoricTranzactii;
			this->numarTranzactii = numarTranzactii;
			this->istoricTranzactii = new double[numarTranzactii];
			for (int i = 0;i <numarTranzactii;i++) {
				this->istoricTranzactii[i] = istoricTranzactii[i];
			}
		}
	}



	//operator =
	ContBancar& operator=(const ContBancar& c) {
		if (this != &c) {
			if (this->istoricTranzactii != NULL) {
				delete[] this->istoricTranzactii;
			}
			this->titularCont = c.titularCont;
			this->numarTranzactii = c.numarTranzactii;
			if (c.numarTranzactii != 0 && c.istoricTranzactii != NULL) {
				this->istoricTranzactii = new double[c.numarTranzactii];
				for (int i = 0;i < c.numarTranzactii;i++) {
					this->istoricTranzactii[i] = c.istoricTranzactii[i];
				}
			}

		}
		return *this;
	}
	//operator << 
	friend ostream& operator<<(ostream& out, const ContBancar& c) {
		out << "id cont: " << c.idCont << endl;
		out << "nume tiular: " << c.titularCont << endl;
		out << " numar tranzactii: " << c.numarTranzactii << endl;
		out << "tranzactii: ";
		for (int i = 0;i < c.numarTranzactii;i++) {
			out << c.istoricTranzactii[i]<<" ";
		}
		return out;
	}
	//operator>>
	
	//operator[]
	double operator[](int index) {
		if (index >= 0 && index < this->numarTranzactii && this->istoricTranzactii != NULL) {
			return this->istoricTranzactii[index];
		}
		return -1;
	}
	//operator de cast la double care calculeaza suma tuturor elementelor din vector
	explicit operator double() {
		double s = 0;
		for (int i = 0;i < this->numarTranzactii;i++) {
			s += this->istoricTranzactii[i];
		}
		return s;
	}
};
int ContBancar::numarConturi = 0;

int main() {
	// constructor fara parametri
	ContBancar c1;
	cout << c1 << endl;

	// constructor cu parametri (valori invalide tratate prin validari)
	double t[] = { 500, -120.5, 300, -80 };
	ContBancar c2("Popescu_Ion", t, 4);
	cout << c2 << endl;

	// constructor de copiere
	ContBancar c3(c2);
	cout << "Copie:" << endl << c3 << endl;

	// operator=
	c1 = c2;
	cout << "Dupa atribuire:" << endl << c1 << endl;

	// auto-atribuire
	c1 = c1;
	cout << "Dupa auto-atribuire:" << endl << c1 << endl;

	// operator[]
	cout << "Tranzactia 2: " << c2[1] << endl;
	cout << "Index invalid (10): " << c2[10] << endl;
	cout << "Index invalid (-1): " << c2[-1] << endl;

	// operator cast la double
	double sold = (double)c2;
	cout << "Sold c2: " << sold << endl;


}