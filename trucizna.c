#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct {
        char wartosc; 
        char kolor; 
        char lokalizacja;       //numer miejsca gdzie się znajduje karta
        unsigned char kolejnosc;        //index karty w abstrakcyjnej tablicy kart, ktore maja te sama lokalizacje
}karta;
int n, k; //liczba graczy, liczba (kolorow odjac zielony)=liczba kociolkow
int g, gv; //ilosc zielonych kart, wartosc zielonych kart
int o, s; // liczba kart kazdego koloru (oprocz zielonego), suma wszystkich kart
int e, active; //granica eksplozji,numer aktywnego gracza
void ZnajdzKolor(int* kolejnosc, char* poczatek_lini, char* pierwszy, char* drugi, char lok, karta* karty) {
        char* szukany = strstr(pierwszy, drugi);        //sprawdza czy znalazl dany kolor
        if (szukany != NULL) {
                char* iterator = szukany - 2;
                int n10 = 1;
                char liczba = 0;
                while(true)
                {
                        if ((*iterator) >= '0' && (*iterator) <= '9')   //czyta wartosc tej karty
                        {
                                liczba += ((*iterator) - '0') * n10;
                                n10 *= 10;
                                iterator--;
                        }
                        else 
                        {
                                break;
                        }
                }
                kolejnosc[s] =  (szukany - poczatek_lini);      //zapisuje kolejnosc karty do tablicow intow, bo wartosci w teorii moga byc za duze dla char'a
                karty[s].wartosc = liczba;              //zapisujemy wartosc karty
                karty[s].lokalizacja = lok;             //zapisujemy lokalizacje karty
                if (drugi[0] == 'b'&&drugi[2] == 'a') {
                        karty[s].kolor = 'l';
                }
                else if (drugi[0] == 'b'&&drugi[2] == 'u') {
                        karty[s].kolor = 'b';
                }
                else {
                        karty[s].kolor = drugi[0];
                }
                s++;
                szukany++;
                ZnajdzKolor(kolejnosc, poczatek_lini,szukany, drugi, lok, karty); //i szukamy dalej tego koloru w wym wierszu
        }
}
void WczytajKarty(int* kolejnosc, char* pierwszy, char lok, karta* karty) {
        char green[] = "green";
        char blue[] = "blue";
        char red[] = "red";
        char violet[] = "violet";
        char yellow[] = "yellow";
        char white[] = "white";
        char black[] = "black";
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, green, lok, karty); //wczytujemy karty dla 
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, blue, lok, karty);   // danych kolorow
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, red, lok, karty);
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, violet, lok, karty);
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, yellow, lok, karty);
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, white, lok, karty);
        ZnajdzKolor(kolejnosc, pierwszy, pierwszy, black, lok, karty);
}
karta* WczytajTalie(karta* talia) {
        char wiersz[300];
        cin.getline(wiersz, 20);
        active = wiersz[16] - '0'; //wczytuje aktywnego gracza 
        cin.getline(wiersz, 20);
        n = wiersz[17] - '0';   //wczytuje liczbe graczy
        cin.getline(wiersz, 30);
        char* iterator = wiersz + 22;
        while (true)
        {                                // wczytuje liczbe eksplozji
                if ((*iterator) >= '0' && (*iterator) <= '9')
                {
                        e = e * 10 + (*iterator) - '0';
                        iterator++;
                }
                else
                {
                        break;
                }
        }
        karta karty[129];       //tworze tymczasowa tablice na czytanie kart
        for (int i = 0; i < 129; i++) {  //zeruje tablice na wypadek
                karty[i].kolor = 0;
                karty[i].wartosc = 0;
                karty[i].lokalizacja = 0;
                karty[i].kolejnosc = 0;
        }
        s = 0;
        int kolejnosc[129];                     //wyczytuje karty do lokalizacji graczy (w dloni nieparzyste)
        for (int i = 0; i < 2 * n; i++) { // na stole parzyste
                cin.getline(wiersz, 300);
                WczytajKarty(kolejnosc, wiersz, i + 1, karty);
        }
        k = 0;  //od tego miejsca liczymy k
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'b') {
                        k++;
                        break;
                }
        }
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'r') {
                        k++;
                        break;
                }
        }
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'v') {
                        k++;
                        break;
                }
        }
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'y') {
                        k++;
                        break;
                }
        }
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'w') {
                        k++;
                        break;
                }
        }
        for (int i = 0; i < s; i++) {
                if (karty[i].kolor == 'l') {
                        k++;
                        break;
                }
        }       //do tego miejsca
        for (int i = 0; i < k; i++) {
                cin.getline(wiersz, 300);
                WczytajKarty(kolejnosc, wiersz, i + 13, karty);
        }
        for (int i = 0; i < 2 * n; i++) {                //(kolejnosc) zmieniam tablice intow na chary,
                int NajmniejszaKolejnosc = 10000;       //wkladajac je do tablicy karty
                int IloscKart = 0;                                      //tu jest dla lokalizacji od 1 do 12
                int obecnyNajwiekszy = 0;
                int index = -1;
                for (int j = 0; j < s; j++) {
                        if (karty[j].lokalizacja == i + 1) {
                                IloscKart++;
                        }
                }
                for (int x = 0; x < IloscKart; x++) {
                        for (int j = 0; j < s; j++) {
                                if (karty[j].lokalizacja==i+1) {
                                        if (NajmniejszaKolejnosc > kolejnosc[j] && kolejnosc[j] > obecnyNajwiekszy) {
                                                NajmniejszaKolejnosc = kolejnosc[j];
                                                index = j;
                                        }
                                }
                        }
                        NajmniejszaKolejnosc = 10000;
                        kolejnosc[index] = ++obecnyNajwiekszy;
                        karty[index].kolejnosc = obecnyNajwiekszy;
                }
        }
        for (int i = 0; i < k; i++) {            //tu jest dla lokalizacji od 13 do 18
                int NajmniejszaKolejnosc = 10000;       //lokalizacja kociolkow
                int IloscKart = 0;
                int obecnyNajwiekszy = 0;
                int index = -1;
                for (int j = 0; j < s; j++) {
                        if (karty[j].lokalizacja == i + 13) {
                                IloscKart++;
                        }
                }
                for (int x = 0; x < IloscKart; x++) {
                        for (int j = 0; j < s; j++) {
                                if (karty[j].lokalizacja == i + 13) {
                                        if (NajmniejszaKolejnosc > kolejnosc[j] && kolejnosc[j] > obecnyNajwiekszy) {
                                                NajmniejszaKolejnosc = kolejnosc[j];
                                                index = j;
                                        }
                                }
                        }
                        NajmniejszaKolejnosc = 10000;
                        kolejnosc[index] = ++obecnyNajwiekszy;
                        karty[index].kolejnosc = obecnyNajwiekszy;
                }
        }
        talia = (karta*)malloc(s * sizeof(karta));      //tworzymy tablice za pomoca malloca
        for (int i = 0; i < s; i++) {                            //i przenosimy do niej dane z tablicy karty
                talia[i].kolor = karty[i].kolor;
                talia[i].wartosc = karty[i].wartosc;
                talia[i].lokalizacja = karty[i].lokalizacja;
                talia[i].kolejnosc = karty[i].kolejnosc;
        }
        return talia;
}
void WczytajWartoscGreen(karta* talia) {
        if (g > 0) {
                gv = talia[0].wartosc;                          //jezeli tu dotarlismy, to znaczy ze g jest znane po przez segregowanie
                for (int i = 1; i < g; i++) {            //sprawdzamy wartosc zielonych kart
                        if (talia[i].wartosc != gv) {
                                gv = -1;
                                break;
                        }
                }
                if (gv > 0) {
                //      cout << "Found " << g << " green cards, all with " << gv << " value" << endl;
                }
                else {
                //      cout << "Different green cards values occurred" << endl;
                }
        }
        else {
                g = 0;
                gv = 0;
        //      cout << "Green cards does not exist" << endl;
        }
}
int SegregujKolor(karta* talia, int poczatek, char kolor) {
        karta zmieniana;
        int koniec = poczatek;
        for (int i = poczatek; i < s; i++) {
                for (int x = 1 + i; x < s; x++) {                        //segregujemy wedlug koloru
                        if (talia[x].kolor == kolor) {
                                zmieniana.kolor = talia[x].kolor;
                                zmieniana.wartosc = talia[x].wartosc;
                                zmieniana.lokalizacja = talia[x].lokalizacja;
                                zmieniana.kolejnosc = talia[x].kolejnosc;
                                talia[x].kolor = talia[i].kolor;
                                talia[x].wartosc = talia[i].wartosc;
                                talia[x].lokalizacja = talia[i].lokalizacja;
                                talia[x].kolejnosc = talia[i].kolejnosc;
                                talia[i].kolor = zmieniana.kolor;
                                talia[i].wartosc = zmieniana.wartosc;
                                talia[i].lokalizacja = zmieniana.lokalizacja;
                                talia[i].kolejnosc = zmieniana.kolejnosc;
                                koniec++;
                                break;
                        }
                }
                if (koniec == s - 1) {
                        koniec++;
                }
        }
        for (int i = poczatek; i < koniec; i++) {
                for (int x = 1 + i; x < koniec; x++) {           //segergujemy w posegregowanym kolorze niemalejaco
                        if (talia[i].wartosc > talia[x].wartosc) {
                                zmieniana.wartosc = talia[x].wartosc;
                                zmieniana.lokalizacja = talia[x].lokalizacja;
                                zmieniana.kolejnosc = talia[x].kolejnosc;
                                talia[x].wartosc = talia[i].wartosc;
                                talia[x].lokalizacja = talia[i].lokalizacja;
                                talia[x].kolejnosc = talia[i].kolejnosc;
                                talia[i].wartosc = zmieniana.wartosc;
                                talia[i].lokalizacja = zmieniana.lokalizacja;
                                talia[i].kolejnosc = zmieniana.kolejnosc;
                        }
                }
        }
        return koniec;
}
void SegregujTalie(karta* talia) {
        int koniec = SegregujKolor(talia,0,'g');        //Tutaj segregujemy talie najpierw wedlug koloru
        g = koniec;                                                                     //potem niemalejaco
        WczytajWartoscGreen(talia);
        int b = 0, r = 0, v = 0, y = 0, w = 0, l = 0;
        koniec = SegregujKolor(talia, koniec, 'b');
        b = koniec - g;
        koniec = SegregujKolor(talia, koniec, 'r');
        r = koniec - b - g;
        koniec = SegregujKolor(talia, koniec, 'v');
        v = koniec - r - b - g;
        koniec = SegregujKolor(talia, koniec, 'y');
        y = koniec - v - r - b - g;
        koniec = SegregujKolor(talia, koniec, 'w');
        w = koniec - y - v - r - b - g;
        koniec = SegregujKolor(talia, koniec, 'l');
        l = koniec - w - y - v - r - b - g;
        o = b;
}
int KtoWygrywaWTymKolorze(karta* talia, char kolor) {
        int obecnygracz=0;
        int suma = 0;
        for (int i = 2; i <= 2*n; i+=2) {
                int nowasuma = 0;
                for (int j = 0; j < s; j++) {
                        if(talia[j].kolor == kolor && talia[j].lokalizacja == i){
                                nowasuma++;
                        }
                }
                if (nowasuma > suma) {
                        suma = nowasuma;
                        obecnygracz = i;
                }
                else if (suma == nowasuma) {
                        obecnygracz = 0;
                }
        }
        return obecnygracz;
}
void NapiszOdpornoscNaKolor(int gracz, char kolor) {
        if (gracz > 0) {
                cout << "Na kolor ";
                if (kolor == 'b') {
                        cout << "blue";
                }
                else if (kolor == 'r') {
                        cout << "red";
                }
                else if (kolor == 'v') {
                        cout << "violet";
                }
                else if (kolor == 'y') {
                        cout << "yellow";
                }
                else if (kolor == 'w') {
                        cout << "white";
                }
                else if (kolor == 'l') {
                        cout << "black";
                }
                else {
                        cout << "nieznany";
                }
                cout <<" odporny jest gracz " << gracz / 2 << endl;
        }
}
int LiczeniePunktowWgKoloru(karta* talia, int gracz, char kolor) {
        int suma = 0;
        for (int i = 0; i < s; i++) {
                if (talia[i].kolor == kolor && talia[i].lokalizacja == gracz) {
                        suma += 1;
                }
        }
        return suma;
}
int LiczeniePunktow(karta* talia, int gracz, int b, int r, int v, int y, int w, int l) {
        int suma = 0;
        if (b != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'b');
        }
        if (r != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'r');
        }
        if (v != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'v');
        }
        if (y != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'y');
        }
        if (w != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'w');
        }
        if (l != gracz) {
                suma += LiczeniePunktowWgKoloru(talia, gracz, 'l');
        }
        for (int i = 0; i < s; i++) {
                if (talia[i].kolor == 'g' && talia[i].lokalizacja == gracz) {
                        suma += 2;
                }
        }
        return suma;
}
void ObslugaKoncaRundy(karta* talia) {
        int b = KtoWygrywaWTymKolorze(talia,'b');
        NapiszOdpornoscNaKolor(b, 'b');
        int r = KtoWygrywaWTymKolorze(talia, 'r');
        NapiszOdpornoscNaKolor(r, 'r');
        int v = KtoWygrywaWTymKolorze(talia, 'v');
        NapiszOdpornoscNaKolor(v, 'v');
        int y = KtoWygrywaWTymKolorze(talia, 'y');
        NapiszOdpornoscNaKolor(y, 'y');
        int w = KtoWygrywaWTymKolorze(talia, 'w');
        NapiszOdpornoscNaKolor(w, 'w');
        int l = KtoWygrywaWTymKolorze(talia, 'l');
        NapiszOdpornoscNaKolor(l, 'l');
        int *Wyniki = (int*)malloc(n * sizeof(int));
        for (int i = 2; i <= 2 * n; i += 2) {
                Wyniki[i/2 - 1] = LiczeniePunktow(talia, i, b, r, v, y, w, l);
        }
        for (int j = 0; j < n; j++) {
                cout << "Wynik gracza " << j + 1 << " = " << Wyniki[j] << endl;
        }
        free(Wyniki);
}
karta* WczytanieRozgrywki(karta* talia) {
        talia = WczytajTalie(talia);
        SegregujTalie(talia);
        //WykonanieProstegoRuchu(talia, 1);
        //CzyDobraIloscKart(talia);
        ObslugaKoncaRundy(talia);
        //WypisanieRozgrywki(talia);
        return talia;
}
int main()
{
        karta* talia = 0;
        talia = WczytanieRozgrywki(talia);
        free(talia);
        return 0;
}