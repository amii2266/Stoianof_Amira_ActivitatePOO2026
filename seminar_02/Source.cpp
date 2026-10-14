#include <iostream>
using namespace std;
struct Ghiozdan
{
	float lungime;
	int nrbuzunare;
	bool laptop;
	char* producator;

};
Ghiozdan citireGhio()
{
	char numeproducator[10];
	Ghiozdan g;
	cout << "lungime= ";
	cin >> g.lungime;
	cout << "buzunare= ";
	cin >> g.nrbuzunare;
	cout << "Pt laptop? :(0/1) ";
	cin >> g.laptop;
	cout << "Producator= ";
	cin >> numeproducator;
	g.producator = new char[strlen(numeproducator) + 1];
	strcpy_s(g.producator, strlen(numeproducator) + 1, numeproducator);
	return g;

}
void afisareGhio(Ghiozdan g)
{
	cout << "lungime " << g.lungime << endl;
	cout << "buzunare " << g.nrbuzunare << endl;
	cout << "laptop " << g.laptop << endl;
	cout << "nume producator " << g.producator << endl;

}
void modificarelungime(Ghiozdan* g, float lungimenoua)
{
	(*g).lungime = lungimenoua;
}
int calculeazaSumaBuz(Ghiozdan* ghiozdane, int nrGhiozdane)
{
	for (int i = 0;i < nrGhiozdane;i++)
	{
		int suma += ghiozdane[i].nrbuzunare;
	}

}
void main() {
	/*Ghiozdan g = citireGhio();
	afisareGhio(g);
	modificarelungime(&g, 12);
	afisareGhio(g);*/

	int nrGhioz = 3;
	Ghiozdan* ghiozdane;
	ghiozdane = new Ghiozdan[3];
	for (int i = 0;i < nrGhioz;i++)
	{
		ghiozdane[i] = citireGhio();
	}
	for (int i = 0;i < nrGhioz;i++)
	{
		afisareGhio(ghiozdane[i]);
	}
	cout << "nr total de buzunare " << calculeazaSumaBuz(ghiozdane, nrGhioz);
}
