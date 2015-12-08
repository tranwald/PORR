#include "ewolucja.h"
#include <cmath>

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Ewolucja::Ewolucja(int mi, int lambda, int wymiar)
	:mi(mi)
	,lambda(lambda)
	,wymiar(wymiar)
{
	for(int i = 0; i < mi; i++)
	{
		PopulacjaP.push_back(osobnik(wymiar));
	}
	funkcjaPrzystosowania(&PopulacjaP);
}
Ewolucja::~Ewolucja()
{
	delete najlepszy;
}

void Ewolucja::ewoluuj()
{
	reprodukcja();
	krzyzowanie();
	mutacja();
	funkcjaPrzystosowania(&PopulacjaT);
	selekcja();
}

void Ewolucja::Wypisz()
{
	for(int i = 0; i < PopulacjaP.size(); i++)
	{
		cout << "Osobnik " << i << " puntky: ";
		for(int j = 0; j < PopulacjaP[i].punkty.size(); j++)
		{
			cout << PopulacjaP[i].punkty[j] << ", ";
		}
		cout << endl;
	}

	cout << "populacja potomkow" << endl;
	for(int i = 0; i < PopulacjaT.size(); i++)
	{
		cout << "Osobnik " << i << " puntky: ";
		for(int j = 0; j < PopulacjaT[i].punkty.size(); j++)
		{
			cout << PopulacjaT[i].punkty[j] << ", ";
		}
		cout << endl;
	}
}

void Ewolucja::funkcjaPrzystosowania(vector<osobnik>* osVec)
{
	vector<osobnik>::iterator it = osVec->begin();

	for(; it < osVec->end(); ++it)
	{
		//iloczyn inicjalizowany na 1, bo x * 1 = x, a x * 0 = 0 
		//we wzorze na iloczyn i+1, bo w zadaniu we wzorze jest dla i =1..n
		//a tu numerowane od 0, przez co wychodzi³o dzielenie przez 0 i nieokreslony wynik
		float suma = 0.0, iloczyn = 1.0;
		for(int i = 0; i < (*it).punkty.size(); i++)
		{
			suma += (*it).punkty[i] * (*it).punkty[i];
			//double c = (*it).punkty[i]/(i+1);
			//iloczyn *= float(cos(c));
			iloczyn *= static_cast<float>(std::cos((*it).punkty[i]/(i + 1)));
		}
		(*it).przystosowanie = (1.0/40.0) * (suma + 1 - iloczyn);
	}
}

void Ewolucja::reprodukcja()
{
	for(int i = 0; i < lambda; i++)
	{
		int ran = rand() % mi;
		PopulacjaT.push_back(PopulacjaP[ran]);
	}
}

void Ewolucja::krzyzowanie()
{
	int locus = wymiar/2;
	for(int i = 0; i < PopulacjaT.size(); i+=2)
	{
		//int locus = rand() % (wymiar - 1) + 1;

		vector<float>::iterator it1 = PopulacjaT[i].punkty.begin();
		vector<float>::iterator it2 = PopulacjaT[i+1].punkty.begin();
		vector<float> potomek1, potomek2;

		//krzyzowanie osobnikow
		potomek1.reserve(wymiar);
		potomek1.insert(potomek1.begin(), it1, it1 + locus);
		potomek1.insert(potomek1.begin() + locus, it2 + locus, it2 + wymiar);

		potomek2.reserve(wymiar);
		potomek2.insert(potomek2.begin(), it1 + locus, it1 + wymiar);
		potomek2.insert(potomek2.begin() + (wymiar - locus), it2, it2 + locus);

		PopulacjaT[i].punkty = potomek1;
		PopulacjaT[i+1].punkty = potomek2;
	}
}

void Ewolucja::mutacja()
{
	float szansa1, szansa2;
	vector<osobnik>::iterator os_vec = PopulacjaT.begin();
	for( ; os_vec < PopulacjaT.end(); ++os_vec)
	{
		szansa1 = randomFloat(0, 1);
		//czy mutowac osobnika ?
		if(szansa1 <= prawd_mutacji1)
		{
			//dla wszystkich cech wylosuj, czy dana ceche zmienic
			vector<float>::iterator cecha_vec = (*os_vec).punkty.begin();
			for( ; cecha_vec < os_vec->punkty.end(); ++cecha_vec)
			{
				szansa2 = randomFloat(0, 1);
				if(szansa2 <= prawd_mutacji2)
				{
					//float zmiana = randomFloat(mutacja_lowerb, mutacja_upperb);		//statyczne (zalezne od ustalonych wartosci)
					float zmiana = randomFloat((-(*cecha_vec))/5, (*cecha_vec)/5);		//dynamiczne (zalezne od rzedu danej cechy)
																						//wyglada na to ze dziala lepiej
					(*cecha_vec) += zmiana;
				}//if szansa2

			}//for kazda cecha

		}//if szansa1

	}//for kazdy osobnik

}

void Ewolucja::selekcja()
{
	//wrzuc wszystko do jednego wora
	PopulacjaR.reserve(mi + lambda);
	PopulacjaR.insert(PopulacjaR.begin(), PopulacjaP.begin(), PopulacjaP.end());
	PopulacjaR.insert(PopulacjaR.begin() + mi, PopulacjaT.begin(), PopulacjaT.end());

	//posortuj
	sort(PopulacjaR.begin(), PopulacjaR.end());
	najlepszy = new osobnik(PopulacjaR[0]);

	//wyczysc stare wektory
	PopulacjaP.clear();
	PopulacjaT.clear();

	//wrzuc najlepsze do populacji P
	PopulacjaP.reserve(mi);
	PopulacjaP.insert(PopulacjaP.begin(), PopulacjaR.begin(), PopulacjaR.begin() + mi);

	//wyczysc populacje R
	PopulacjaR.clear();
}

void Ewolucja::pokazNajlepszego()
{
	cout << "Najlepszy osobnik ma wartosc przystosowania = " << najlepszy->przystosowanie << endl;
	cout << "Wymiary: ";
	vector<float>::iterator it = najlepszy->punkty.begin();
	for( ; it < najlepszy->punkty.end(); ++it)
	{
		cout << (*it) << ", ";
	}
	cout << endl;
}