#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
#define K 250 // maks kolumn
#define W 250 // maks wierszy
#define multiple 4 // mnożnik przy rysowaniu 
class Gra {
public:
  // krok, iteracja 
  UL krok = 0;
  // komórki: true żywe, false martwe
  array<array<bool, W>, K> komorki{ {0} };
  // true - komórka ma zmienić stan w następnej iteracji: na żywą (true), na martwą (false)
  array<array<bool, W>, K> stan{ {0} };
  unsigned iluZywychSasiadow(size_t w, size_t k) {
    unsigned ile = 0;
    if (k == 0 or k == K - 1 or w == 0 or w == W - 1) return ile;
    for (auto [kmod, wmod] :
      vector<pair<int, int>>{ {-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1} }) {
      if (komorki[w + wmod][k + kmod]) ile++;
    }
    return ile;
  }
  // ustawia komórki żywe na starcie, np. this->start({{100,100},{100,101}}); 
  void start(vector<pair<int, int>> ozywione) {
    // wszystkie martwe:
    for (auto& wiersz : komorki) wiersz.fill(false);
    // ożywiam
    for (auto [w, k] : ozywione) komorki[w][k] = true;
    toPBM();
  }
  // jeden krok/iteracja w algorytmie
  void tik() {
    // ustawiam wszystkie stany przyszłe na: komórka martwa
    for (auto& wiersz : stan) wiersz.fill(false);
    // analiza obecnej sytuacji
    for (size_t w = 0; w < W; w++) {
      for (size_t k = 0; k < K; k++) {
        unsigned i = iluZywychSasiadow(w, k);
        if ((!komorki[w][k] and i == 3) or
          (komorki[w][k] and (i == 2 or i == 3))) stan[w][k] = true; // ożywa lub żyje dalej
      }
    }
    // krok
    krok++;
    // ustawiam, kto żyje, a kto martwy
    komorki = stan;
    toPBM();
    cout << "Krok nr " << krok << " wygenerowany.\n";
  }
  // grafika .pbm na podstawie obecnego stanu komórek (powiększenie * multiple)
  void toPBM() {
    ofstream plik(to_string(krok) + ".pbm"); // 1.pbm, 2.pbm itd.
    plik << "P1" << endl;
    plik << "# Krok " << krok << endl;
    plik << W * multiple << " " << K * multiple << endl;
    for (auto& wiersz : komorki) {
      for (unsigned i = 1; i <= multiple; i++)
        for (auto& komorka : wiersz) {
          plik << string(multiple, int(komorka) + 48);
        }
    }
    plik.close();
  }
};
int main() {
  setlocale(LC_ALL, ""); srand(time(0));
  Gra g;
  g.start({
    {119,126},
    {120,120},{120,121},
    {121,121}, {121,125}, {121,126}, {121,127}
    });
  for (int i = 1; i <= 10; i++) g.tik(); // powstanie 10 kroków gry
}
