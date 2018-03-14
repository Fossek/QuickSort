#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void Sortowanie_szybkie_rekursywne(string args[], int n)
{
	if (n <= 1) {
		return;
	}

	const int piwot_i = n - 1;
	int i = 0, j = 0;

	for(;i<n - 1;i++)
	{
		if (args[i] < args[piwot_i])
		{
			swap(args[i], args[j]);
			j++;
		}
	}
	swap(args[piwot_i], args[j]);
	Sortowanie_szybkie_rekursywne(args, j);
	Sortowanie_szybkie_rekursywne(args + j + 1, n - 1 - j);
}

void Sortowanie_szybkie_petla(string args_b[], int n_b)
{
	int index = -1;
	string **wskazniki = new string*[n_b];
	int *rozmiary=new int[n_b];

	// Pierwszy zasiêg (globalny)
	index++;
	wskazniki[index] = args_b;
	rozmiary[index] = n_b;

	while(index >= 0) // Ka¿de przebiegniêcie while jest równowa¿ne z pojedynczym wywo³aniem fukcji Sortowanie_szybkie_rekursywne.
	{				
		// Zbieranie argumentów do pojedynczego wywo³anie funkcji
		string *args = wskazniki[index];
		int n = rozmiary[index];
		--index;

		const int piwot_i = n - 1;
		int i = 0, j = 0;

		for (; i < n - 1; i++)
		{
			if (args[i] < args[piwot_i])
			{
				swap(args[i], args[j]);
				j++;
			}
		}
		swap(args[piwot_i], args[j]);

		// Wrzucanie nowych argumentów do wywo³ania funkcji /
		//   "lewy"  : Sortowanie_szybkie_rekursywne(args, j);
		if (j > 1) {
			index++;
			wskazniki[index] = args;
			rozmiary[index] = j;
		}
		//   "prawy" : Sortowanie_szybkie_rekursywne(args + j + 1, n - 1 - j);
		if (n - 1 - j > 1) {
			index++;
			wskazniki[index] = args + j + 1;
			rozmiary[index] = n - 1 - j;
		}
	}

	delete[] wskazniki;
	delete[] rozmiary;
}

int main()
{
	cout << "Wprowadz ciag znakow odzielone po przecinku" << endl; 
	string argumenty;
	cin >> argumenty;
	
	// petla licz¹ca jak duz¹ utworzyæ tablice
	int liczba_argumentow=0;
	for (int i = 0; i < argumenty.length(); i++)
	{ 
		if (argumenty[i] == ',')
			liczba_argumentow++;
	}
	liczba_argumentow++;
	
	// rozdzielenie argumentów do tablicy 
	string *tab= new string[liczba_argumentow];
	for (int i = 0, k = 0; i < argumenty.length(); i++)
	{
		if (argumenty[i] == ',')
		{
			++k;
		}
		else {
			tab[k] += argumenty[i];
		}
	}

	// kopiowanie tabeli dal drugiego sortowania
	string *tab2 = new string[liczba_argumentow];
	for (int i = 0; i < liczba_argumentow; ++i) {
		tab2[i] = tab[i];
	}
	//Sortowania
	//	Rekursywne
	Sortowanie_szybkie_rekursywne(tab, liczba_argumentow);
	for (int i = 0; i < liczba_argumentow; i++)
	{
		cout << tab[i] << " ";
	}
	cout << endl;
	//	Petla
	Sortowanie_szybkie_petla(tab2, liczba_argumentow);
	for (int i = 0; i < liczba_argumentow; i++)
	{
		cout << tab2[i] << " ";
	}
	cout << endl;

	system("pause");
	delete[] tab;
}
