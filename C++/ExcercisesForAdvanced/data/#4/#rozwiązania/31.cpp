#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
//////////////////////////////////////////////////////
class Tusz {
public:
  float kartka=0;
  vector<float> CMYK;  
  Tusz() { CMYK.resize(4,0); }
  bool czytajZLinii(ifstream& plik) {
    if (!(plik >> kartka)) return false;    
    for (auto& e : CMYK) if (!(plik >> e)) return false;
    return true;
  }
  float kosztKartki() {
    // kolor 100.00 zł/50.0 ml, czarny 40.00 zł/50.0 ml 
    // kolor 2.00 zł/1.0 ml, czarny 0.80 zł/1.0 ml
    // 50ml -> 72 kartki -> 7200% pokrycia 
    // 1ml -> 144%
    float koszt = 0.;
    for (size_t a : {0, 1, 2}) // kolory
      koszt += (2 * ((1.0 * CMYK[a]) / 144.0)) / 1.0;
    koszt += (0.80 * ((1.0 * CMYK[3]) / 144.0)) / 1.0; // czarny
    return koszt;
  }
  float procentPokryciaWielomaTuszami() {
    float procent = 0, suma_kolor = 0;
    for (auto poz : { 0,1,2,3 }) suma_kolor += CMYK[poz];
    return suma_kolor - kartka;    
  }
};
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("31_tusz.txt");
  string linia;
  getline(plik, linia); // nagłówki przeczytane
  vector<Tusz> kartki;
  float procent;      
  while (!plik.eof()) {    
    Tusz t;
    if (t.czytajZLinii(plik)) kartki.push_back(t);
  }
  plik.close();
  float koszt = 0;
  for (auto& k : kartki) koszt += k.kosztKartki();
  cout << setprecision(2) << fixed << koszt << " za tusz.\n";
  // setprecision + fixed pokazuje dokładnie zaokrąglenie  
  float srednia = 0;
  for (auto& k : kartki) srednia += k.procentPokryciaWielomaTuszami();
  cout << "Średnie pokrycie " << setprecision(2) << fixed << srednia / 500.f << endl;
}
