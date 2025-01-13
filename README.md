
### **1. Wstęp**
Gra "Pojedynek" to tekstowa gra turowa, w której gracz walczy z przeciwnikiem wykorzystując w każdej turze wybraną akcję.

Program posiada:
- Turowy system walki.
- Obsługę mechaniki zdrowia, ataków, leczenia i super ataku.
- System menu.

---

### **2. Importowane biblioteki**
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
```
- `iostream` – do obsługi wejścia/wyjścia (np. `cin`, `cout`).
- `cstdlib` – do generowania liczb losowych (`rand()`).
- `ctime` – do ustawienia ziarna losowości (`srand()`).

---

### **3. Klasa bazowa `Postac`**
```cpp
class Postac {
protected:
    string nazwa;
    int zdrowie;
    int atak;
```
- **`Postac`** to klasa bazowa dla postaci (gracza i przeciwnika).
- **Atrybuty**:
  - `nazwa` – nazwa postaci.
  - `zdrowie` – liczba punktów zdrowia.
  - `atak` – maksymalna liczba obrażeń, które postać może zadać.
- **Konstruktor**:
  - Inicjalizuje nazwę, zdrowie i atak postaci.
- **Metody**:
  - `wykonaj_akcje(int tura)` – funkcja wirtualna, nadpisywana w klasach pochodnych.
  - `otrzymaj_obrazenia(int obrazenia)` – zmniejsza zdrowie postaci po otrzymaniu obrażeń.
  - `czy_zyje()` – sprawdza, czy postać ma zdrowie > 0.
  - `pokaz_statystyki()` – wyświetla statystyki postaci.

---

### **4. Klasa `Gracz`**
```cpp
class Gracz : public Postac {
private:
    bool superAtakGotowy;
```
- Dziedziczy po klasie `Postac`.
- **Dodatkowe atrybuty**:
  - `superAtakGotowy` – flaga wskazująca, czy gracz może użyć super ataku.
- **Konstruktor**:
  - Ustawia nazwę gracza, zdrowie na 100 i atak na 20.
  - `superAtakGotowy` ustawione na `false`.
- **Metody**:
  - `wykonaj_akcje(int tura)` – umożliwia wybór akcji przez gracza:
    - **Atak** – losowe obrażenia od 1 do wartości `atak`.
    - **Leczenie** – losowa regeneracja zdrowia (od 10 do 29).
    - **Super Atak** – podwójne obrażenia (co 4 tury).
    - **Ucieczka** – kończy walkę i ustawia zdrowie na 0 co jest jednoznaczne z porażką gracza.
  - `zaktualizuj_super_atak(int tura)` – co 4 tury ustawia `superAtakGotowy` na `true`.

---

### **5. Klasa `Przeciwnik`**
```cpp
class Przeciwnik : public Postac {
public:
    Przeciwnik(string n) : Postac(n, 100, 20) {}
```
- Dziedziczy po klasie `Postac`.
- **Konstruktor**:
  - Ustawia nazwę przeciwnika, zdrowie na 100 i atak na 20.
- **Metody**:
  - `wykonaj_akcje(int tura)` – przeciwnik zadaje losowe obrażenia od 1 do wartości `atak`.

---

### **6. Funkcja `walka`**
```cpp
void walka(Gracz& gracz, Przeciwnik& przeciwnik)
```
- Obsługuje walkę turową między graczem a przeciwnikiem.
- **Przebieg**:
  1. Wyświetla statystyki postaci.
  2. Rozpoczyna tury:
     - Gracz wybiera akcję, a przeciwnik automatycznie atakuje.
  3. Sprawdza, czy któraś z postaci została pokonana.
  4. Kończy walkę, gdy zdrowie gracza lub przeciwnika osiągnie 0.

---

### **7. Funkcja `menu`**
```cpp
void menu()
```
- Wyświetla główne menu gry.
- **Opcje**:
  - `1` – Rozpocznij grę:
    - Tworzy postać gracza i przeciwnika.
    - Rozpoczyna walkę.
  - `2` – Zakończ grę:
    - Kończy działanie programu.

---

### **8. Funkcja `main`**
```cpp
int main() {
    srand(time(0));
    menu();
    return 0;
}
```
- Ustawia ziarno generatora liczb losowych (unikalna losowość przy każdym uruchomieniu gry).
- Uruchamia menu główne.

---
