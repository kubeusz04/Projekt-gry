#include <iostream>  // Biblioteka do wyswietlania tekstu na ekranie
#include <cstdlib>   // Biblioteka do generowania liczb losowych
#include <ctime>     // Biblioteka do pobierania biezacego czasu (dla srand)
using namespace std;

// Klasa bazowa Postac, ktora reprezentuje kazda postac w grze (gracza lub przeciwnika)
class Postac {
protected:
    string nazwa;  // Nazwa postaci
    int zdrowie;   // Liczba punktow zdrowia postaci
    int atak;      // Liczba obrazen zadawanych przez postac w ataku

public:
    // Konstruktor klasy Postac
    Postac(string n, int z, int a) : nazwa(n), zdrowie(z), atak(a) {}

    // Czysta funkcja wirtualna, ktora zostanie nadpisana przez klasy pochodne
    virtual int wykonaj_akcje(int tura) = 0;

    // Funkcja otrzymywania przez postac obrazen
    void otrzymaj_obrazenia(int obrazenia) {
        zdrowie -= obrazenia;  // Zdrowie postaci zmniejsza sie o obrazenia
        if (zdrowie < 0) zdrowie = 0;  // Warunek by upewnic sie, ze zdrowie nie jest ponizej 0
        cout << nazwa << " otrzymuje " << obrazenia << " obrazen! Zdrowie: " << zdrowie << endl;
    }

    // Funkcja sprawdzajaca, czy postac nadal zyje
    bool czy_zyje() const {
        return zdrowie > 0;  // Jesli zdrowie jest wieksze niz 0, postac zyje
    }

    // Funkcja wyswietlajaca statystyki postaci
    void pokaz_statystyki() const {
        cout << "Nazwa: " << nazwa << ", Zdrowie: " << zdrowie << ", Atak: " << atak << endl;
    }
};

// Klasa Gracz dziedziczaca po Postac
class Gracz : public Postac {
private:
    bool superAtakGotowy; // Flaga która wskazuje, czy super atak jest gotowy do uzycia

public:
    // Konstruktor klasy Gracz, ustawiający bazowo stan super ataku na niedostepny
    Gracz(string n) : Postac(n, 100, 20), superAtakGotowy(false) {}

    // Funkcja nadpisujaca wykonanie akcji gracza
    int wykonaj_akcje(int tura) override {
        int wybor;
        cout << "\n1. Atak\n2. Leczenie\n";
        // Opcja super ataku pojawia sie tylko wtedy, gdy jest gotowa
        if (superAtakGotowy) {
            cout << "3. Super Atak\n";
        }
        cout << "4. Ucieczka\n";
        cout << "Wybierz akcje: ";
        cin >> wybor;

        // Informujemy gracza, czy super atak jest gotowy
        if (superAtakGotowy) {
            cout << "Super atak jest gotowy do uzycia!\n";
        }
        else {
            cout << "Super atak jest jeszcze w trakcie ladowania...\n";
        }

        int obrazenia = 0;
        switch (wybor) {
        case 1: {
            obrazenia = rand() % atak + 1;  // Obrazenia losowane sa od 1 do wartosci ataku
            cout << "Wykonujesz atak i zadajesz " << obrazenia << " obrazen!\n";
            break;
        }
        case 2: {
            int leczenie = rand() % 20 + 10;  // Losowanie liczby punktow leczenia od 10 do 29
            zdrowie += leczenie;
            if (zdrowie > 100) zdrowie = 100;  // warunek by upewnic sie ze zdrowie nie przekroczy 100
            cout << "Leczysz sie za " << leczenie << " punktow. Twoje zdrowie wynosi teraz: " << zdrowie << endl;
            break;
        }
        case 3:
            // Sprawdzenie, czy super atak jest gotowy
            if (superAtakGotowy) {
                obrazenia = (rand() % atak + 1) * 2;  // Super atak zadaje podwojne obrazenia
                cout << "Wykonujesz super atak i zadajesz " << obrazenia << " obrazen!\n";
                superAtakGotowy = false;  // Po uzyciu super ataku, staje sie on niedostepny
            }
            else {
                cout << "Super atak nie jest gotowy! Wybierz inna akcje.\n";
            }
            break;
        case 4:
            cout << "\nUciekasz z walki! Przegrywasz gre!\n";
            zdrowie = 0;  // Zdrowie gracza wynosi 0 wiec jest to jednoznaczne z porazka
            break;
        default:
            cout << "Nieprawidlowy wybor, tracisz ture!\n";
            break;
        }
        return obrazenia;  // Zwracamy liczbe zadanych obrazen
    }

    // Funkcja aktualizujaca stan super ataku
    void zaktualizuj_super_atak(int tura) {
        if (tura % 4 == 0) {  // Co 4 tury super atak staje sie dostepny
            superAtakGotowy = true;
        }
    }
};

// Klasa Przeciwnik dziedziczaca po Postac
class Przeciwnik : public Postac {
public:
    // Konstruktor klasy Przeciwnik
    Przeciwnik(string n) : Postac(n, 100, 20) {}

    // Funkcja nadpisujaca wykonanie akcji przeciwnika
    int wykonaj_akcje(int tura) override {
        int obrazenia = rand() % atak + 1;  // Losowanie obrazen zadanych przez przeciwnika
        cout << nazwa << " atakuje i zadaje " << obrazenia << " obrazen!\n";
        return obrazenia;  // Zwracamy liczbe zadanych obrazen
    }
};

// Funkcja zarzadzajaca walka miedzy graczem a przeciwnikiem
void walka(Gracz& gracz, Przeciwnik& przeciwnik) {
    cout << "\n------------------------------------------\n";
    cout << "Rozpoczyna sie walka!\n";
    cout << "\nStatystyki bohaterow na poczatku walki:\n";
    cout << "Twoja postac:\n";
    gracz.pokaz_statystyki();
    cout << "\nPrzeciwnik:\n";
    przeciwnik.pokaz_statystyki();

    int tura = 1;  // Zmienna do przechowywania numeru tury

    // Petla walki, ktora trwa do momentu, gdy ktoras ze stron nie zostanie pokonana
    while (gracz.czy_zyje() && przeciwnik.czy_zyje()) {
        cout << "\n------------------------------------------\n";
        cout << "--- Tura " << tura << " ---\n";

        // aktualizowanie stanu super ataku gracza co ture
        gracz.zaktualizuj_super_atak(tura);

        // Tura gracza
        cout << "\nTwoja tura:" << endl;
        int obrazenia = gracz.wykonaj_akcje(tura);  // Gracz wykonuje akcje i zadaje obrazenia
        if (!gracz.czy_zyje()) {  // Sprawdzenie, czy gracz nadal zyje, jesli nie - przegrywa
            cout << "\nPrzeciwnik zwycieza! Wracasz do menu glowniego.\n";
            return;
        }
        przeciwnik.otrzymaj_obrazenia(obrazenia);  // Przeciwnik otrzymuje obrazenia

        if (!przeciwnik.czy_zyje()) {  // Sprawdzenie, czy przeciwnik nadal zyje, jesli nie - gracz wygrywa
            cout << "\nPokonales przeciwnika! Wracasz do menu glownego.\n";
            return;
        }

        // Tura przeciwnika
        cout << "\nTura przeciwnika:" << endl;
        obrazenia = przeciwnik.wykonaj_akcje(tura);  // Przeciwnik wykonuje atak
        gracz.otrzymaj_obrazenia(obrazenia);  // Gracz otrzymuje obrazenia od przeciwnika

        if (!gracz.czy_zyje()) {  
            cout << "\nZostales pokonany! Wracasz do menu glowniego.\n";
            return;
        }

        tura++;  // Przejście do nastepnej tury
    }
}

// Funkcja menu glownego
void menu() {
    while (true) {
        cout << "\n------------------------------------------\n";
        cout << "--- Menu Glowne ---\n";
        cout << "1. Rozpocznij gre\n2. Wyjdz\n";
        cout << "Wybierz opcje: ";
        int wybor;
        cin >> wybor;

        if (wybor == 1) {  // Rozpoczecie gry
            cout << "\nPodaj nazwe swojej postaci: ";
            string nazwa;
            cin >> nazwa;
            Gracz gracz(nazwa);  // Tworzymy postac gracza
            Przeciwnik przeciwnik("Wróg");  // Tworzymy przeciwnika

            walka(gracz, przeciwnik);  // Rozpoczynamy walke

        }
        else if (wybor == 2) {  // Zakoncznie gry
            cout << "Do zobaczenia!\n";
            break;
        }
        else {
            cout << "Nieprawidlowy wybor, sproboj ponownie.\n";
        }
    }
}

int main() {
    srand(time(0));  // Uruchamiamy generator liczb losowych
    menu();  // Uruchamiamy menu glowne
    return 0;
}
