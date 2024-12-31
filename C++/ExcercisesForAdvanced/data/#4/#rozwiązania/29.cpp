#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;

int main() {
  setlocale(LC_ALL, "");

  ifstream plik_jagi("29_baba_jaga.txt");
  vector<string> mapa_lasu;
  string ln;
  while (getline(plik_jagi, ln)) mapa_lasu.push_back(ln);
  plik_jagi.close();
  // policzę ile jest obszarów 4xkwadrat (wg identycznych znaków, które je tworza)
  map<string, UL> obszary4;
  for (UL w = 0; w < 800 - 1; w += 2) {
    for (UL k = 0; k < 800 - 1; k += 2) {
      string kod4;
      kod4 += mapa_lasu[w][k];
      kod4 += mapa_lasu[w][k + 1];
      kod4 += mapa_lasu[w + 1][k];
      kod4 += mapa_lasu[w + 1][k + 1];
      obszary4[kod4]++;
    }
  }
  // obszar/y, które wystąpiły 429 razy (są jednoznaczne)
  string kod_chatki;
  for (auto [kod, ile] : obszary4) {
    if (ile == 429) {
      cout << kod << " == " << ile << endl;
      kod_chatki = kod;
    }
  }
  // 429 współrzędnych lewego, górnego kwadraciku obszarów z chatkami
  UL chatka = 1;
  for (UL w = 0; w < 800 - 1; w += 2) {
    for (UL k = 0; k < 800 - 1; k += 2) {
      string kod4;
      kod4 += mapa_lasu[w][k];
      kod4 += mapa_lasu[w][k + 1];
      kod4 += mapa_lasu[w + 1][k];
      kod4 += mapa_lasu[w + 1][k + 1];
      if (kod4 == kod_chatki) cout << "Chatka nr " << chatka++ << " = " << w + 1 << "x" << k + 1 << endl;
    }
  }
}
