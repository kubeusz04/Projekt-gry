
### **1. Wstęp**
Gra "Pojedynek" to tekstowa gra walki turowej, w której gracz zmierza się z przeciwnikiem. Program umożliwia:
- Tworzenie postaci gracza.
- Losowe generowanie przeciwnika.
- Wybór akcji przez gracza w trakcie walki.
- Obsługę mechaniki zdrowia, ataków, leczenia i super ataku.
- Prosty system menu.

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
    - **Leczenie** – losowa regeneracja zdrowia (10–20 punktów).
    - **Super Atak** – podwójne obrażenia (co 4 tury).
    - **Ucieczka** – kończy walkę i ustawia zdrowie na 0.
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
  - Obsługuje błędny wybór.

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

### **Mechanika gry**
1. **Zdrowie**:
   - Gracz i przeciwnik zaczynają z 100 punktami zdrowia.
   - Zdrowie maleje po otrzymaniu obrażeń.
2. **Atak**:
   - Losowa liczba obrażeń od 1 do wartości `atak`.
3. **Leczenie**:
   - Losowa liczba regeneracji (10–20 punktów).
4. **Super Atak**:
   - Co 4 tury, podwójne obrażenia.
5. **Ucieczka**:
   - Gracz kończy walkę z porażką.

---

### **Możliwości rozwoju**
1. **Nowe klasy postaci**:
   - Dodanie nowych przeciwników z różnymi cechami (np. różne zdrowie, specjalne umiejętności).
2. **Rozgrywka**:
   - Wielu przeciwników.
   - System poziomów i zdobywania doświadczenia.
3. **Grafika**:
   - Dodanie interfejsu graficznego.
4. **Zapisywanie gry**:
   - Możliwość zapisu i wczytywania postaci.
