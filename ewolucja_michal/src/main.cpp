#include "ewolucja.h"
#include <iostream>
#include <sstream>

//TODO
//pamietac o randomie przy wersji rownoleglej
//zrobic mutacje zalezna od najlepszego osobnika??
//chodzi o to, ze mutacja powyzej 1 wplywa na szybsze zbieganie w poczatkowych fazach
//ale gdy wymiary sa juz blisko zera, tak duza zmiana pogarsza wynik (niewazne czy + czy -)
//bo oddala rozwiazanie od 0, wtedy lepsza by byla zmiana na poziomie ulamkow

//auto dopasowanie
//stworzyc plik z wygenerowanymi chechami (dla n osobnikow i w wymiarow)
//i na tym samym zestawie przeprowadzic automatyczne testy zeby dobrac parametry
//takie jak szanse mutacji czy wartosci o jakie mutuja sie cechy


void start(int &m, int &l, int &w, int &i, bool &c);

int main()
{
	int m, l, w, i;
	bool czesciowe = false;
	start(m, l, w, i, czesciowe);

	Ewolucja ewo(m, l, w);
	for(; i > 0; i--)
	{
		ewo.ewoluuj();
		if(czesciowe && (! (i % 20)) )
			ewo.pokazNajlepszego();
	}
	//ewo.Wypisz();
	cout << endl << "Tadam! Oto wynik: " << endl;
	ewo.pokazNajlepszego();

	system("PAUSE");
	return 0;
}


void start(int &m, int &l, int &w, int &i, bool &c)
{
	string in;
	cout << "Algorytm ewolucyjny. Podaj wartosci parametrow." << endl;

	cout << "mi: " << endl;
	cin >> in;
	istringstream iss(in);
	iss >> m;

	cout << "lambda: " << endl;
	cin >> in;
	istringstream iss1(in);
	iss1 >> l;

	cout << "wymiar: " << endl;
	cin >> in;
	istringstream iss2(in);
	iss2 >> w;

	cout << "liczba iteracji: " << endl;
	cin >> in;
	istringstream iss3(in);
	iss3 >> i;

	cout << "czy drukowac wyniki czesciowe? (t/n): " << endl;
	cin >> in;
	if(in == "t")
		c = true;
	else 
		c = false;
}