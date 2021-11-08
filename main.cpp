#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int ile = 0;
const string fileName = "output.txt";

int *stworzTablice()
{
    cout <<"Podaj rozmiar tablicy: ";
     cin >> ile;
    while(cin.fail() || ile <= 0)
    {
       cout << "Wprowadz poprawna wartosc." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> ile;
    }

    int* tab = new int[ile];

    for(int i = 0; i < ile; i++)
    {
        cout << "Podaj element nr." << i+1 << ": ";
         cin >> tab[i];
        while( cin.fail() )
        {
            cout << "Wprowadz poprawna wartosc." << endl;
             cin.clear();
             cin.ignore(256,'\n');
             cin >> tab[i];
        }
    }

    sort( tab, tab + ile );
    return tab;

}

void calcProduct( int tab[], int ile )
{
    int  counter = 0;
    int* Iloczyny = new int [ile - 1]; //tworzymy tablice iloczynow
    Iloczyny[0] = tab[0] * tab[1];

    cout<<"\n\nIloczyny\n\n";

    for(int i=0; i<ile-1; i++)
    {
        Iloczyny[i] = tab[i] * tab[i+1];
           cout << i+1 << ". " << Iloczyny[i] << endl;
        counter += 1;
    }
    
    int maks = Iloczyny[0];

for(int j=0; j<counter; j++)
    {
        if( Iloczyny[j+1] > Iloczyny[j] )
        {
            maks = Iloczyny[j+1];
        }
    }
    cout << "Najwiekszy iloraz: " << maks << endl;
    cout << "Czynniki generujace maksymalny iloczyn to pary: ";
    
    for( int i=0; i< ile - 1; i++ )
    {
        if( tab[i] * tab[i+1] == maks )
        {
            cout << "[ " << tab[i] << ", " << tab[i+1] <<" ]  ";
        }
    }
}
int main()
{
    int* tablica = stworzTablice();
    calcProduct( tablica, ile );
    delete [] tablica;
}
