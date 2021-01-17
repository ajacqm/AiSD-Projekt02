//Zadanie projektowe numer: 2
//Algorytmy i Struktury Danych
//Matuszko Jakub

//Tresc zadania: Zaimplementuj sortowanie przez wstawianie oraz sortowanie kubelkowe
//Cechy programu:
/*Program powinien miec mozliwosc odczytania danych wejsciowych z pliku tekstowego
i zapisu posortowanego ciagu wynikowego rowniez do pliku tekstowego*/
/*na potrzeby wykonywanych tekstow nalezy zaimplementowac funkcje generujaca losowe ciagu elementow (o zadaniej dlugosci)
 i zapisujaca je do pliku tekstowego*/
/*zalozyc, ze sortowanymi elementami sa liczby calkowite z przedzialu [0,N], gdzie N powinno byc "Odpowiednio du¿ym"
parametrem ustalonym wewnatrz programu*/
/*kod powinien byc opatrzony stosownymi komentarzami*/


#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <windows.h>

using namespace std;

bool show_op = true;						//Wyswietlanie wszystkich operacji w konsoli
string in_file_name = "input.txt";			//Nazwa pliku wejsciowego
string out_file_name = "output.txt";		//Nazwa pliku wyjsciowego
ofstream output(out_file_name.c_str());

void insertion_sort(vector <int> &numb);
void bucket_sort(vector <int> &list);
void dbl_vector(vector <int> numb,vector <int> &numb2);
void f_swap(int &a, int &b);
int f_maxmin(vector <int> numb, bool lookformax);
void display(vector <int> numb);
void printtofile(vector <int> numb);
void time_test();

int main()
{
	vector <int> numbers;								//Deklaracja wektora liczb
	vector <int> numbers2;
	vector <int> numbers3;
	ifstream input(in_file_name.c_str());				//Deklaracja pliku wejœciowego

	int f_read;

	if (!input.good())									//Sprawdzenie poprawnoœci otwarcia pliku:
	{													//Je¿eli b³¹d:
		cerr << "[ERROR] File error ";					//Wyœwietl komunikat o b³êdzie "File error"
		return 1;										//Zwróc wartoœæ 1
	}
	else												//W przeciwnym wypadku (gdy program poprawnie odczytal plik):
	{
		while (!input.eof())							//Petla wczytujaca liczby z pliku do wektora
		{
			input >> f_read;							//Przypisanie liczby z pliku do zmiennej f_read
			if (input.fail())							//Je¿eli przypisanie zwróci b³¹d to:
			{
				if (show_op) cout << "[WARNING] Input - one character was ommited" << endl;

				input.clear();							//Usuniecie flagi bledu z wejscia
				input.ignore();							//Zignorowanie znaku z pliku input.txt
			}
			else numbers.push_back(f_read);				//Gdy proces wska¿e brak b³êdów, liczba zostanie dopisana do koñca wektora
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
	printtofile(numbers2);
	/*End of part 01*/

	/*PART 02 - Bucket Sort*/
	bucket_sort(numbers3);
	if (show_op)
	{
		cout << "Sorted numbers by bucket sort: " << endl;
		display(numbers3);
	}
	printtofile(numbers3);
	/*End of part 02*/
	//time_test();
	return 0;
}

void time_test()
{
    ofstream testout("tests.txt");
    DWORD t1,t2;
    int z;
    vector <int> tab;
    vector <int> tab2;
    srand ((unsigned)time(NULL));
    int T[10] = {100,500,1000,2000,5000,10000,20000,50000,100000,200000};
    for(int i=0; i<10; i++)
    {
        testout << i << "; " << T[i] << "; ";
        for(int j=0; j<T[i]; j++)
        {
            z = rand() % 100;
            tab.push_back(z);
            tab2.push_back(z);
        }
        t1 = GetTickCount();
        insertion_sort(tab);
        t2 = GetTickCount() - t1;
        testout << t2 << "; ";
        cout << "Czas wykonania insertion sort: " << t2;
        cout << endl;
        t1 = GetTickCount();
        bucket_sort(tab2);
        t2 = GetTickCount() - t1;
        testout << t2 << "; " << endl;
        cout << "Czas wykonania bucket sort: " << t2;
        cout << endl;
        tab.clear();
        tab2.clear();
    }
}

void insertion_sort(vector <int> &numb)
{
	for (int i = 1; i < numb.size(); i++)
	{
		for (int j = i; j > 0; j--) if (numb[j - 1] > numb[j]) f_swap(numb[j - 1], numb[j]);
	}
}

void bucket_sort(vector <int>  &list)
{
    int sizeoflist = list.size();               //Zmienna zawierajaca informacje o ilosci elementow
    vector <vector <unsigned int> > bucket;     //Deklaracja wektora - wektorów
    for(int i=0; i < sizeoflist; i++)
    {
        bucket.push_back(vector<unsigned int>());   //Utworzenie kubelka dla kazdej liczby
    }
    unsigned int max = f_maxmin(list,true);         //Wyszukanie najwiekszej liczby w wektorze
    max++;
    for(int i = 0; i < sizeoflist; i++)
    {
        bucket[double(list[i])/double(max)*sizeoflist].push_back(list[i]);  //Wrzucenie liczby do odpowiedniego kubelka
    }
    for(int i = 0; i < sizeoflist; i++)
    {
        sort(bucket[i].begin(),bucket[i].end());    //Posortowanie wszystkich kubelkow algorytmem szybkim
    }
    list.clear();                                   //Wyczyszczenie wektora list
    for(int i = 0; i < sizeoflist; i++)
    {
        for(int j = 0; j < bucket[i].size(); j++)
        {
            list.push_back(bucket[i][j]);           //Zbieranie liczb z kubelkow i wstawianie do wektora list
        }
    }
}

void dbl_vector(vector <int> numb, vector <int>& numb2)     //Kopiowanie wektorow
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

int f_maxmin(vector <int> numb, bool lookformax)        //Wyszukiwanie najwiekszej liczby w wektorze (jezeli lookformax = false to wyszukuje minimalna)
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

void display(vector <int> numb)             //Wypisywanie wektora do konsoli
{
	for (int i = 0; i < numb.size(); i++) cout << numb[i] << " ";
	cout << endl;
}

void printtofile(vector <int> numb)         //Wypisywanie wektora do pliku
{
	for (int i = 0; i < numb.size(); i++) output << numb[i] << " ";
	output << endl;
}
