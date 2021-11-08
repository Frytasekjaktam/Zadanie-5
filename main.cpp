#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int ile = 0;
const string fileName = "output.txt"; // nazwa pliku do odczytu, ktory wygeneruje program

//FUNKCJA TWORZACA I WYPELNIAJACA TABLICE
int *stworzTablice()
{
    cout <<"Podaj rozmiar tablicy: ";
     cin >> ile;
    while(cin.fail() || ile <= 1) //petla ktora sprawdza czy wprowadzone dane sa liczbami wiekszymi lub rownymi jeden
    {
       cout << "Niepoprawna wartosc " << endl;
        cin.clear(); // czysci flage bledu
        cin.ignore(100,'\n'); //ignoruje niepoprawne dane czyli max 100 znakow az do spotkanie nowej linii
        cin >> ile;
    }

    int* tab = new int[ile];

    for(int i = 0; i < ile; i++)
    {
        cout << "Podaj element nr." << i+1 << ": ";
         cin >> tab[i];
        while( cin.fail() )  // petla ktora rowniez sprawdza poprawnosc wprowadzonych danych (tylko czy jest liczba)
        {
            cout << "Wprowadz poprawna wartosc." << endl;
             cin.clear();
             cin.ignore(100,'\n');
             cin >> tab[i];
        }
    }

    sort( tab, tab + ile ); //sortuje wpraowadzone dane od najmniejszego do najwiekszego
    return tab;

}

//FUNKCJA OBLICZAJACA ILOCZYNY Z TABLICY
void calcProduct( int tab[], int ile )
{
    ofstream file; //zmienna plik
    file.open (fileName); //otwiera plik

    int  counter = 0;  //zmienna licznik ktora wykorzystana bedzie do petli sprawdzajacej i zamieniajacej wartosc maksymalna z tablicy 
    int* Iloczyny = new int [ile - 1]; //tworzymy tablice iloczynow
    Iloczyny[0] = tab[0] * tab[1];

    file << "\n\nIloczyny\n\n";

    for(int i=0; i<ile-1; i++) //petla wypisujaca iloczyny dwoch sasiednich liczb (wczesniej posortowanych)
    {
        Iloczyny[i] = tab[i] * tab[i+1];
           file << i+1 << ". " << Iloczyny[i] << endl;
        counter += 1;
    }
    
    int maks = Iloczyny[0];

for(int j=0; j<counter; j++) //petla przechodzaca przez kolejne iloczyny, jezeli napotka wiekszy iloczyn to zamienia go do zmiennej maks
    {
        if( Iloczyny[j+1] > Iloczyny[j] )
        {
            maks = Iloczyny[j+1];
        }
    }
    file << "\nNajwiekszy iloraz: " << maks << endl;
    file << "Czynniki generujace maksymalny iloczyn to pary: ";
    
    for( int i=0; i< ile - 1; i++ )  //petla wypisuje pary liczb
    {
        if( tab[i] * tab[i+1] == maks )
        {
            file << "[ " << tab[i] << ", " << tab[i+1] <<" ]  ";
        }
    }
    file << "\n";
}


// FUNKCJA GLOWNA
int main()
{
    int* tablica = stworzTablice(); // tworzymy tablice dynamiczna na podstawie wprowadzonych danych i przy okazji sortujemy je w kolejnosci rosnacej
    calcProduct( tablica, ile ); //odwolujemy sie do funkcji z dwoma argumentami
    delete [] tablica; //zwalniamy pamiec usuwajac tablice dynamiczna 

// WYPISYWANIE PLIKU NA EKRAN
    ifstream outcome(fileName); // wypisuje dane na ekran, jesli nastapi blad to wyswietli stosowny komunikat

    if ( outcome.is_open() )
    {
        cout << outcome.rdbuf();
        outcome.close();
    }
    else
    {
        cout << "Blad przy otwieraniu pliku: " << fileName;
    }

    return 0;
}
