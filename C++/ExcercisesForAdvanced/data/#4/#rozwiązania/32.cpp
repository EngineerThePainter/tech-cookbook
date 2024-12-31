#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
bool ON = true;
struct Dane {
  int kategoria;
  shared_ptr<Dane> za = nullptr; // wskaźnik na obiekt za obecnym
  ~Dane() {
    if (ON) cout << "Dane kategorii " << kategoria << " opuściły kolejkę." << endl;
  }
};
class Kolejka {
public:
  UL ile = 0; // ilość w kolejce
  UL ile_opuscilo = 0; // ile opuściło kolejkę
  UL ile_dodano = 0; // ile razy dodano do kolejki
  shared_ptr<Dane> pierwszy = nullptr;
  shared_ptr<Dane> ostatni = nullptr;
  UL maks = 0, aktualny_maks = 0;
  vector<int> dane_maks_kategoria, dane_maks_kategoria_aktualne;
  // dodaj na koniec kolejki dane
  void dodaj(int kat) {
    shared_ptr<Dane> nowy = make_shared<Dane>(kat, nullptr);
    if (ile == 0) {
      pierwszy = ostatni = nowy;
    }
    else {
      ostatni->za = nowy;
      ostatni = nowy;
    }
    ++ile;
    ile_dodano++;
    cout << "\t" << ile_dodano << ". Dane " << ostatni->kategoria << " dotarły na koniec kolejki (" << ile << ")" << endl;
    UL przed = ile;
    zasady(); // testy opuszczania kolejki
    // część analizująca najdłuższy proces dodawania danych bez usuwania z kolejki
    if (przed == ile) {
      maks++;
      dane_maks_kategoria.push_back(nowy->kategoria);
    }
    else {
      maks = 0;
      dane_maks_kategoria.clear();
    }
    if (maks > aktualny_maks) {
      aktualny_maks = maks;
      dane_maks_kategoria_aktualne = dane_maks_kategoria;
    }
  }

  void opusc() {
    if (ile == 1) {
      pierwszy = ostatni = nullptr;
    }
    else if (ile > 1) {
      pierwszy = pierwszy->za;
    }
    ile--;
    ile_opuscilo++;
  }
  void opusc(int kat) {
    while (ile > 0 and pierwszy->kategoria == kat) opusc();
  }
  void opusc(int kat1, int kat2) {
    while (ile > 0 and (pierwszy->kategoria == kat1 or pierwszy->kategoria == kat2)) opusc();
  }
  // analizujemy reguły wypuszczania po dodaniu danych...
  void zasady() {
    int kat = ostatni->kategoria;
    if (kat == 1) { // 5. kategoria opuszcza kolejkę
      opusc(5);
    }
    else if (kat == 2) { // 1. kategoria opuszcza kolejkę
      opusc(1);
    }
    else if (kat == 3) { // 2. kategoria opuszcza kolejkę
      opusc(2);
    }
    else if (kat == 4 or kat == 5) {
      UL i;
      do {
        i = ile;
        opusc(3, 4);
      } while (ile != i);
    }
  }
};

int main() {
  setlocale(LC_ALL, "");
  Kolejka K;
  string info;
  ifstream plik("32_kolejka.txt");
  int dane_kategorii;
  while (plik >> dane_kategorii) {
    K.dodaj(dane_kategorii);
    if (K.ile_dodano == 40) { // w następnym kroku pętli dodam 41. element
      info = "Przed dodaniem 41. danej kolejkę opuściło " + to_string(K.ile_opuscilo);
    }
  }
  plik.close();

  cout << K.aktualny_maks <<
    " -> największa liczba dodanych danych z rzędu niewywołująca opuszczania kolejki.\n";
  for (auto k : K.dane_maks_kategoria_aktualne) cout << k << " ";
  cout << endl;
  cout << info << endl; // przed 41. daną 

  cout << "W kolejce zostało " << K.ile << endl;
  shared_ptr<Dane> pomoc = K.pierwszy;

  while (pomoc != nullptr) {
    cout << pomoc->kategoria << " ";
    pomoc = pomoc->za;
  }
  cout << endl;
  // od tego momentu nie interesuje mnie komunikat opuszczania kolejki generowany
  // w destruktorze ~Dane
  ON = false;
}
