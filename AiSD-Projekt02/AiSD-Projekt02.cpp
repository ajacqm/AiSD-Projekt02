//Zadanie projektowe numer: 2
//Algorytmy i Struktury Danych
//Matuszko Jakub

//Tresc zadania: Zaimplementuj sortowanie przez wstawianie oraz sortowanie kubelkowe
//Cechy programu:
/*Program powinien miec mozliwosc odczytania danych wejsciowych z pliku tekstowego
i zapisu posortowanego ciagu wynikowego rowniez do pliku tekstowego*/
/*na potrzeby wykonywanych tekstow nalezy zaimplementowac funkcje generujaca losowe ciagu elementow (o zadaniej dlugosci)
 i zapisujaca je do pliku tekstowego*/
/*zalozyc, ze sortowanymi elementami sa liczby calkowite z przedzialu [0,N], gdzie N powinno byc "Odpowiednio dużym"
parametrem ustalonym wewnatrz programu*/
/*kod powinien byc opatrzony stosownymi komentarzami*/


#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool show_op = true;		//Wyswietlanie wszystkich operacji w konsoli

void insertion_sort(vector <int> &numb);
void bucket_sort(vector <int> &numb);
void dbl_vector(vector <int> numb,vector <int> &numb2);
void f_swap(int &a, int &b);
int f_maxmin(vector <int> numb, bool lookformax);
void display(vector <int> numb);

int main()
{
	vector <int> numbers;								//Deklaracja wektora liczb
	vector <int> numbers2;
	vector <int> numbers3;
	ifstream input("input.txt");						//Deklaracja pliku wejściowego
	ofstream output("output.txt");						//Deklaracja pliku wyjściowego
	
	int f_read;

	if (!input.good())									//Sprawdzenie poprawności otwarcia pliku:
	{													//Jeżeli błąd:
		cerr << "[ERROR] File error ";					//Wyświetl komunikat o błędzie "File error"
		return 1;										//Zwróc wartość 1
	}
	else												//W przeciwnym wypadku (gdy program poprawnie odczytal plik):
	{
		while (!input.eof())							//Petla wczytujaca liczby z pliku do wektora
		{
			input >> f_read;							//Przypisanie liczby z pliku do zmiennej f_read
			if (input.fail())							//Jeżeli przypisanie zwróci błąd to:
			{
				if (show_op) cout << "[WARNING] Input - one character was ommited" << endl;

				input.clear();							//Usuniecie flagi bledu z wejscia
				input.ignore();							//Zignorowanie znaku z pliku input.txt
			}							
			else numbers.push_back(f_read);				//Gdy proces wskaże brak błędów, liczba zostanie dopisana do końca wektora
		}
	}

	if (show_op)										//Wyswietlenie wczytanej tablicy liczb do konsoli
	{
		cout << "Numbers from file: ";
		display(numbers);
	}

	dbl_vector(numbers, numbers2);
	dbl_vector(numbers, numbers3);

	/*PART 01 - Insertion Sort*/
	insertion_sort(numbers2);
	if (show_op)
	{
		cout << "Sorted numbers by insertion sort: " << endl;
		display(numbers2);
	}
	/*End of part 01*/

	/*PART 02 - Bucket Sort*/
	bucket_sort(numbers3);
	if (show_op)
	{
		cout << "Sorted numbers by bucket sort: " << endl;
		display(numbers3);
	}
	/*End of part 02*/
	return 0;
}

void insertion_sort(vector <int> &numb)
{
	for (int i = 1; i < numb.size(); i++)
	{
		for (int j = i; j > 0; j--) if (numb[j - 1] > numb[j]) f_swap(numb[j - 1], numb[j]);
	}
}

void bucket_sort(vector <int> &numb)
{

}

void dbl_vector(vector <int> numb, vector <int>& numb2)
{
	for (int i = 0; i < numb.size(); i++)
	{
		numb2.push_back(numb[i]);
	}
	if (show_op) cout << "Vector sucessfully doubled" << endl;
}

void f_swap(int &a, int &b)  //Funkcja zmieniajaca miejscami dwie liczby (poprzez podanie adresu liczby)
{
	int temp = a;           //Zmienna temp - przechowuje tymczasowa wartosc liczby a;
	a = b;                  //Przypisanie zmiennej a watrosci z liczby b
	b = temp;               //Przypisanie zmiennej b wartosci tymczasowej
}

int f_maxmin(vector <int> numb, bool lookformax)
{
	int temp_maxmin = numb[0];
	if (!lookformax)
	{
		for (int i = 0; i < numb.size(); i++)
		{
			if (numb[i] < temp_maxmin) temp_maxmin = numb[i];
		}
	}
	else
	{
		for (int i = 0; i < numb.size(); i++)
		{
			if (numb[i] > temp_maxmin) temp_maxmin = numb[i];
		}
	}
	return temp_maxmin;
}

void display(vector <int> numb)
{
	for (int i = 0; i < numb.size(); i++) cout << numb[i] << " ";
	cout << endl;
}