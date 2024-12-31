// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <queue>
#include <list>
constexpr float X = 19.;
constexpr float RAMKA = 1.;
using namespace std;
//////////////////////////////////////////////////////
enum class RODZAJ { ROCK = int('#'), VOID = int('.'), START = int('S'), END = int('K') }; 
class Pole : public Baza {
public:
  inline static unsigned long long int NR = 1;
  unsigned long long int nr = 0;
  bool przekraczalny = false;
  bool odwiedzony = false;
  RectangleShape blok;
  list<shared_ptr<Pole>> wyjscia; // góra, lewo, dół, prawo
  RODZAJ rodz;
  unsigned long long int licznik = 0;

  Pole(RODZAJ r) : rodz(r) {
    nr = NR++;
    blok.setSize(Vector2f(X, X));
    blok.setOutlineColor(Color(255, 0, 0));
    blok.setOutlineThickness(RAMKA);
    if (r == RODZAJ::ROCK) {
      blok.setFillColor(Color(40, 40, 40));
    }
    else {
      przekraczalny = true;
      if (r == RODZAJ::VOID) {
        blok.setFillColor(Color(200, 200, 200));
      }
      else if (r == RODZAJ::START) {
        blok.setFillColor(Color(100, 255, 100));
      }
      else {
        blok.setFillColor(Color(255, 100, 100));
      }
    }
  }
  void odwiedzaj() {    
    blok.setFillColor(Color(120, 120, 120));
  }
  void zapal() {
    blok.setFillColor(Color(255, 255, 255));
  }
  void badany() {
    blok.setFillColor(Color(255, 0, 0));
  }

  void rysuj() {
    program.W->draw(blok);
  }
  void progresuj() {}
};

class Plansza : public Baza {
public:
  vector<vector<shared_ptr<Pole>>> plansza;
  queue<shared_ptr<Pole>> kolejka_odw;
  shared_ptr<Pole> start; // zapamiętam początek
  bool stop = false;
  Plansza(string plik) {
    ifstream odczyt(plik);
    string linia;
    for (int wiersz = 0; odczyt >> linia; wiersz++) {
      plansza.push_back({});
      plansza.back().resize(linia.size());
      for (int kolumna = 0; auto & znak : linia) {
        plansza[wiersz][kolumna] = make_shared<Pole>(Pole(RODZAJ(znak)));
        plansza[wiersz][kolumna]->blok.setPosition(kolumna * (X + RAMKA), wiersz * (X + RAMKA));
        if (RODZAJ(znak) == RODZAJ::START) {
          start = plansza[wiersz][kolumna];
          plansza[wiersz][kolumna]->odwiedzaj();
          kolejka_odw.push(plansza[wiersz][kolumna]);
        }
        kolumna++;
      }
    }
    odczyt.close();
    // tworzę listę możliwych wyjść z każdego pola na inne pole 
    int wiersz = 0;
    for (auto& w : plansza) {
      int wsize = plansza.size();
      int kolumna = 0;
      for (auto& pole : w) {
        int ksize = w.size();
        // czy górne wyjście?
        if (wiersz - 1 >= 0 and plansza[wiersz - 1][kolumna]->przekraczalny)
          pole->wyjscia.push_back(plansza[wiersz - 1][kolumna]);
        // czy w prawo?
        if (kolumna + 1 < ksize and plansza[wiersz][kolumna + 1]->przekraczalny)
          pole->wyjscia.push_back(plansza[wiersz][kolumna + 1]);
        // czy w dół?
        if (wiersz + 1 < wsize and plansza[wiersz + 1][kolumna]->przekraczalny)
          pole->wyjscia.push_back(plansza[wiersz + 1][kolumna]);
        // czy w lewo
        if (kolumna - 1 >= 0 and plansza[wiersz][kolumna - 1]->przekraczalny)
          pole->wyjscia.push_back(plansza[wiersz][kolumna - 1]);
        kolumna++;
      }
      wiersz++;
    }
  }
  void rysuj() {
    for (int wiersz = 0; wiersz < plansza.size(); wiersz++) {
      for (int kolumna = 0; kolumna < plansza[wiersz].size(); kolumna++) {
        plansza[wiersz][kolumna]->rysuj();
      }
    }
  }
  void progresuj() {    
    if (stop) return; // już niczego nie analizuje, droga znaleziona (bądź nie)
    if (kolejka_odw.size() and kolejka_odw.front()->rodz != RODZAJ::END) {
      szukanieDrogi();            
    }
    else if (kolejka_odw.size() and kolejka_odw.front()->rodz == RODZAJ::END) {
      pokazDroge();
    }
  }
  // algorytm szukanieDrogi dla grafów (traktujemy Pole jak wierzchołek grafu)
  void szukanieDrogi() {
    static bool badany = false;
    auto& zkolejki = kolejka_odw.front();    
    zkolejki->badany();
    if (!badany) {
      zkolejki->badany(); badany = true;       
      return;
    }
    else { 
      badany = false; 
      // sf::sleep(sf::milliseconds(250)); // usuń znaki // rozpoczynające komentarz, by zobaczyć dokładniej analizę
    }
    zkolejki->odwiedzaj();        
    for (auto& wyjscie : zkolejki->wyjscia) {
      if (wyjscie != nullptr and !wyjscie->odwiedzony) {        
        wyjscie->zapal();
        wyjscie->odwiedzony = true;
        wyjscie->licznik = zkolejki->licznik + 1;
        kolejka_odw.push(wyjscie);
        wyjscie = nullptr;
      }
    }
    cout << endl;
    kolejka_odw.pop();
  }

  void pokazDroge() {
    static auto odKonca = kolejka_odw.front();
    odKonca->blok.setFillColor(Color::Yellow);
    if (odKonca->rodz != RODZAJ::START) {
      for (auto& p : odKonca->wyjscia) {
        if (p != nullptr and p->licznik == odKonca->licznik - 1) {
          odKonca = p;
        }
      }
    }
    else stop = true;
    start->blok.setFillColor(Color::Green);
  }
};
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  program.obiekty.push_back(make_shared<Plansza>("2_labirynt.txt"));  
  program.start();
}
