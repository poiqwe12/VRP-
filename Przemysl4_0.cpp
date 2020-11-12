// Przemysl4_0.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>

#define ROZMIAR 50

using namespace std;
void WyswietlVector(vector<double> X);
double ObliczSumeDrog(vector<double> X);
void WyswietlVector(vector<int> X);
class Map
{
public:
	int liczbaMiast;
	char* jednostka;
	double tOdleglosci[ROZMIAR][ROZMIAR];
	string tNazwaMiast[ROZMIAR];
	vector<int> tPermutacje;
};

vector<double> A, A2;				// Zbiór dostępnych miast
vector<double> P;					// Permutacja


/*
ostream & operator<< (ostream &wyj, Map &zm)
{
		wyj << "  ";
		for (int j = 0; j < zm.liczbaMiast; ++j)
		{
			for (int i = 0; i < zm.liczbaMiast; ++i)
			{
				wyj << zm.tOdleglosci[j][i] << "\t";
			}
		}
	wyj << endl;
	
	
	return wyj;
}
*/

bool WczytajZPliku(string nazwaPliku, Map &F)
{
	fstream plik;
	plik.open(nazwaPliku, std::ios::in | std::ios::out);
	
	if (plik.good() == true)
	{
		string a;
		char znak;
		for (int i = 0; i < 2; ++i)
		{
			getline(plik, a);
		}

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				plik >> F.tOdleglosci[i][j]>>znak;
			}
		}
		for (int j = 0; j < 25; j++)
			{
				getline(plik, a,';');
				getline(plik, a, ';');
				F.tNazwaMiast[j] = a;
				getline(plik, a);
		}
		return true;
	}
	return false;
}

double Policzdroge(std::vector<int> perm, Map &M,int nrCentrali)
{	
	double suma = 0;
	for (int i = 0; i < perm.size(); ++i)
	{
		suma = suma + M.tOdleglosci[perm[i]][nrCentrali];
		cout << suma<<endl;
	}
	return suma;
}

double PoliczCmax(vector<int> perm,Map M)
{
	double suma=0;
	for (int i = 0; i < perm.size()-1; ++i)
	{
		suma = suma + M.tOdleglosci[perm[i]][perm[i+1]];
	}
	return suma;
}

void symulowaneWyzarzanie(vector<int> permutacjaStartowa ,int parm,Map &M)
{
	vector<int> permutacjaNowa;
	permutacjaNowa = permutacjaStartowa;
	int T, T0, i, j, rozmiar, r;
	double L, deltaCmax, nowyCmax, staryCmax, rozwiazanie;
	rozmiar = permutacjaStartowa.size();
	// wybór
	switch (parm)
	{
		case 0:
		T = 100;
		T0 = T;
		L = sqrt(rozmiar);
		break;
	default:
		break;
	}
	
	while (T0 > 0)
	{
		for (int k = 1; k < L; k++)
		{
			int zm;
			i = 1 + rand() % (rozmiar - 1);
			j = 1 + rand() % (rozmiar - 1);
			
			permutacjaNowa[i] = permutacjaStartowa[j];
			permutacjaNowa[j] = permutacjaStartowa[i];
			/*for (int z = 0; z < rozmiar; z++)
			{
				cout << tablicaSW[z]<<" ";
			}
			cout << endl;
			for (int z = 0; z < rozmiar; z++)
			{
				cout << tablicaNEW[z] << " ";
			}
			cout << endl;*/

			staryCmax = PoliczCmax(permutacjaStartowa, M);
			nowyCmax = PoliczCmax(permutacjaNowa, M);

			deltaCmax = nowyCmax - staryCmax;

			if (deltaCmax <= 0)
			{
				r = (double)rand() / RAND_MAX;
				if (r >= exp(deltaCmax / T0))
				{
					permutacjaNowa = permutacjaStartowa;
					rozwiazanie = staryCmax;
				}
			}
			 permutacjaStartowa = permutacjaNowa;
			 rozwiazanie = nowyCmax;

			if (deltaCmax > 0)
			{
				permutacjaNowa = permutacjaStartowa;
				rozwiazanie = staryCmax;
			}
			cout << "Wynik: " << rozwiazanie << endl;
		}

		T0--;

	}
}

void algorytm2(Map &M, int pCentralny, int iloscPojazdow)
{
	int rozmiar = 25;
	double zm, x1;
	int nrMax, nr2Min, x2;
	int k = 1;
	int xk[100];
	bool stop = 1;
	zm = 0;
	double cos = INT16_MAX;
	vector<int> odwiedzoneMiasta;
	/*             Wpisanie odleglosci miast z miejsca bazowego          */
	for (int i = 0; i < rozmiar; ++i)
	{
		A.push_back(M.tOdleglosci[pCentralny][i]);
	}
	/* Usuwam niepotrzebne zero z vector*/
	cout << A.size();
	A.erase(A.begin() + pCentralny);
	/* Dodaje do odwiedzonych miast miasto startowe*/
	odwiedzoneMiasta.push_back(pCentralny);
	int xsa = 1;
	while (A.size() && xsa <10)
	{
		A2.clear();
		/* Dodanie początku trasy/miejsca startowego*/
		P.push_back(M.tOdleglosci[pCentralny][pCentralny]);
		/*		Znalezienie maxa		            */
		for (int i = 0; i < A.size(); ++i)
		{
			if (A[i] > zm)
			{
				zm = A[i];
				nrMax = i;
			}
		}
		cout << "Najwieksza odleglosc: " << zm << endl;
		/* dodanie */
		P.push_back(zm);
	
		xk[k] = 1; // Pierwsze miasto dla pojazdu
		A.erase(A.begin() + nrMax);
	
		//WyswietlVector(P);
		//WyswietlVector(A);
		for (int i = 0; i < rozmiar; ++i)
		{
			A2.push_back(M.tOdleglosci[nrMax][i]);
		}
		odwiedzoneMiasta.push_back(nrMax);
		//WyswietlVector(A2);
		for (int i = 0; i < odwiedzoneMiasta.size(); i++)
		{
			A2.erase(A2.begin() + odwiedzoneMiasta[i]);
		}
		cout << "----------------------Pozostale miasta do obsłuzenia ----------------------" << endl;
		WyswietlVector(A2);
		while (stop)
		{
			if (!A2.size())
			{
				stop = false;
				break;
			}
			for (int j = 0; j < A2.size(); ++j)
			{
				//cout << A2.size() << endl;
				if ((A2[j] < zm) && (A2[j] > 0))
				{
					if ((A2[j] != cos))
					{
						cos = A2[j];
						nr2Min = j; // pozycja najmniejszego elementu w kolejnym wierszu 
					}
				}
			}
			cout << "Minimalna odl: " << cos << endl;
			if (xk[k] + 1 < rozmiar / iloscPojazdow)
			{
				odwiedzoneMiasta.push_back(nr2Min);
				P.push_back(cos);
				A2.erase(A2.begin() + nr2Min);
				A.erase(A.begin() + nr2Min);
				xk[k]++; // ilosc miast dla jednego samoochodu
				cos = INT16_MAX;
			}
			else
				stop = false;
		}
		stop = true;
		k++;
		zm = 0;
		WyswietlVector(P);
	}
	cout << "Suma drog wynosi: " << ObliczSumeDrog(P) << endl;
	cout << "----------------------Odwiedzone miasta ------ ----------------------" << endl;
	WyswietlVector(odwiedzoneMiasta);
}



void WyswietlVector(vector<double> X)
{
	
	for (int i = 0; i < X.size(); ++i)
	{
		cout << X[i] << "  ";
	}
	cout << endl;
}
void WyswietlVector(vector<int> X)
{

	for (int i = 0; i < X.size(); ++i)
	{
		cout << X[i] << "  ";
	}
	cout << endl;
}
double ObliczSumeDrog(vector<double> X)
{
	double suma=0;
	for (int i = 0; i < X.size(); i++)
	{
		suma += X[i];
	}

	return suma;
}

int main()
{
	Map m;
	WczytajZPliku("PL.csv", m);
	std::vector<int> v = { 1, 2, 0, 3,1 };
	algorytm2(m, 0, 2);
	vector<int> start;
	for (int i = 0; i < 25; ++i)
	{
		start.push_back(i);
	}
	start.push_back(0);

	symulowaneWyzarzanie(start, 0, m);
	return 0;
}
