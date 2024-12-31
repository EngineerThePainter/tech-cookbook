#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct Element {
  Element* za = nullptr;
  vector<double> dane;
};
struct KolejkaDK { // DK->dwa końce
  Element* pierwszy = nullptr;
  Element* ostatni = nullptr;
  UL size = 0;
};
// dodaj na koniec
void dodaj_na_koniec(KolejkaDK& K, const initializer_list<double> d) {
  Element* nowy = new Element;
  nowy->dane.insert(nowy->dane.end(), d.begin(), d.end());
  if (K.size) { // są elementy
    K.ostatni->za = nowy;
    K.ostatni = nowy;
  }
  else { // nie ma żadnych elementów w kolejce
    K.pierwszy = K.ostatni = nowy;
  }
  K.size++;
}

// wypuść/skasuj z początku
void opusc_kolejke(KolejkaDK& K) {
  if (K.size == 0) return; // pusta kolejka, wychodzę
  if (K.size > 1) {
    Element* temp = K.pierwszy;
    K.pierwszy = K.pierwszy->za;
    delete temp;
  }
  else if (K.size == 1) { // jest jeden
    delete K.pierwszy;
    K.pierwszy = K.ostatni = nullptr;
  }
  K.size--;
}
vector<double> pierwszy(KolejkaDK& K) {
  if (K.size) {
    return K.pierwszy->dane;
  }
  cout << "Brak jakichkolwiek elementów.\n";
  return {};
}
vector<double> ostatni(KolejkaDK& K) {
  if (K.size) {
    return K.ostatni->dane;
  }
  cout << "Brak jakichkolwiek elementów.\n";
  return {};
}
void pokaz(KolejkaDK& K) {
  if (K.size) {
    cout << "---\n";
    Element* temp = K.pierwszy;
    while (temp != nullptr) {
      cout << "->";
      for (auto e : temp->dane) cout << e << " ";
      cout << "\n";
      temp = temp->za;
    }
    cout << "###\n";
  }
  else cout << "Brak elementów w kolejce.\n";
}
int main() {
  setlocale(LC_ALL, "");
  KolejkaDK kdk;
  dodaj_na_koniec(kdk, { 1., 2., 3. });
  dodaj_na_koniec(kdk, { 2., 3., 4.5 });
  dodaj_na_koniec(kdk, { 5., 7., 11. });
  cout << "Obecnych elementów : " << kdk.size << endl;
  cout << "Pierwszy element w kolejce vector<double> zawiera: ";
  for (auto e : pierwszy(kdk)) cout << e << " ";
  cout << endl;
  cout << "Ostatni element w kolejce vector<double> zawiera: ";
  for (auto e : ostatni(kdk)) cout << e << " ";
  cout << endl;
  pokaz(kdk); // elementy kolejki
  opusc_kolejke(kdk); // pierwszy opuszcza kolejkę (usuwanie)
  pokaz(kdk);
}
