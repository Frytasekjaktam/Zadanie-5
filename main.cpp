#include <iostream>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;
clock_t start, stop;
double czas;
int ile = 0;
const string fileName = "output.txt"; // nazwa pliku do odczytu, ktory wygeneruje program

//FUNKCJA TWORZACA I WYPELNIAJACA TABLICE
int *stworzTablice()
{
    cout <<"Podaj rozmiar tablicy: ";
     cin >> ile;
    while(cin.fail() || ile <= 1) //petla ktora sprawdza czy wprowadzone dane sa liczbami wiekszymi lub rownymi jeden
    {
       cout << "Niepoprawna wartosc: ";
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
            cout << "Wprowadz poprawna wartosc (liczbe calkowita): ";
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

    int* Iloczyny = new int [ile - 1]; //tworzymy tablice iloczynow
    // file << "\n\nIloczyny\n\n";

    for(int i=0; i<ile-1; i++) //petla wypisujaca iloczyny dwoch sasiednich liczb (wczesniej posortowanych)
    {
        Iloczyny[i] = tab[i] * tab[i+1];
     //      file << i+1 << ". " << Iloczyny[i] << endl;
    }

    int maks = Iloczyny[0];

for(int j=0; j<ile - 2; j++) //petla przechodzaca przez kolejne iloczyny, jezeli napotka wiekszy iloczyn to zamienia go do zmiennej maks
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
    file.close(); // zamykamy plik
}
//FUNKCJA KTORA TWORZY TABLICE O PODANYM ROZMIARZE I ELEMENTACH Z ZAKRESU -99 DO 99
int *randTab(){
    cout<< "Wygenerowane liczby beda z zakresu (-99, 99)\n";
    cout << "Podaj ile elementow ma zawierac tablica: ";
    cin >> ile;
        while( cin.fail() )
    {
        cout << "Wprowadz poprawna wartosc (liczbe calkowita): ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> ile;
    }
    cout << "Trwa obliczenie..." << endl;
    start = clock();
    int *tab = new int[ile];
    for(int i=0 ; i<ile ; i++){
        tab[i] = rand()%199-99;
    }
    sort(tab, tab + ile);
    return tab;
}

void printFile()
{
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
}

// FUNKCJA GLOWNA
int main()
{
    cout << "1. Wprowadz dane" << endl;
    cout << "2. Wylosuj dane"  << endl;
    int wybor;
    cin>>wybor;
    system("cls"); // wyczyszczenie ekranu
    srand(time(NULL)); //funkcja ktora ustawia losowy punkt generowania danych za pomoca funkcji time zwraca liczbe okreslajaca czas
    switch(wybor)
    {
        case 1:
            {
            int* tablica = stworzTablice(); // tworzymy tablice dynamiczna na podstawie wprowadzonych danych i przy okazji sortujemy je w kolejnosci rosnacej
            //for (int i=0; i<ile; i++)
            //  cout<<"1. "<<tablica[i]<<endl;

            calcProduct( tablica, ile ); //odwolujemy sie do funkcji z dwoma argumentami
            delete [] tablica; //zwalniamy pamiec usuwajac tablice dynamiczna
            printFile();
            break;
            }

        case 2:
            {
            int *tabs = randTab();
            calcProduct ( tabs, ile);
            // skomentowane zostalo wypisywanie wszystkich wygenerowanych liczb w kolejnosci rosnacej
            // for (int i=0; i<ile; i++)
            //    cout<<i+1<<". "<<tabs[i]<<endl;
            delete [] tabs;
            stop = clock();
            printFile();

            czas = (double)(stop - start) / CLOCKS_PER_SEC;
            cout << "\nCzas: " << czas << "s. ";
            break;
            }
        default:
            cout<<"Nieprawidlowy wybor!";
    }

    return 0;
}
