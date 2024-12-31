#include <iostream>
#include <fstream>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
const string red("\033[91m"); // czerwony
const string green("\033[92m"); // zielony
const string reset("\033[0m"); // RESET koloru
//////////////////////////////////////////////////////
struct Blob {
  L zdrowie_max = 10000000; // 10 milionów
  L zdrowie = 10000000;  
  L regeneracja_zdrowie_max = 300000;
  L regeneracja_zdrowie_min = 57000;
  // ile sekund upłynęło od ostatniego zranienia Bloba
  L czas_od_zranienia = 0; 
  L czas_do_ataku = 45;
  L czas_od_ostatniego_ataku = 0;
  L obrazenia = 20000; 
  L ile_atakow = 0;
};
struct SuperHero {
  // nazwa bohatera
  string bohater;
  L zdrowie;
  L czas_do_ataku;
  L czas_od_ostatniego_ataku;
  L obrazenia;
  // dla Ignoratora informacja o opóźnieniach po atakowaniu  
  bool lag = false;
  L co_ile_atakow_lag = 5;
  L ile_atakow=0;
  bool komunikat = false;
  
};
// Analiza zmian u bohaterów po upływie sekundy
void sekunda(SuperHero& sh, Blob& b) {
  if (sh.zdrowie <= 0) {
    if (!sh.komunikat) { // wysyłam komunikat o śmierci tylko raz
      cout << red << ">>>>>>  " << sh.bohater << " nie żyje.\n" << reset;
      sh.komunikat = true;
    }
    return; // nie żyje
  }
  sh.czas_od_ostatniego_ataku++;  
  if (sh.czas_do_ataku == sh.czas_od_ostatniego_ataku) {
    // Atak
    sh.ile_atakow++;
    cout << sh.bohater << " atakuje!\n";
    b.zdrowie -= sh.obrazenia;
    cout << "Blob zdrowie = [" << b.zdrowie << "]\n";
    // zapis ataku w blobie
    b.czas_od_zranienia = 0;

    sh.czas_od_ostatniego_ataku = 0;
    // lag dla Zgniotka
    if (sh.lag and sh.ile_atakow % sh.co_ile_atakow_lag == 0) {
      sh.czas_do_ataku++;
      sh.obrazenia += 20000;
    }
  }
}
// analiza zmian u Bloba po upływie sekundy
void sekunda(Blob& b, SuperHero& g, SuperHero& z, SuperHero& i) {
  if (b.zdrowie <= 0) {
    cout << "Blob nie żyje.\n";
    return; // nie żyje
  }
  b.czas_od_ostatniego_ataku++;
  b.czas_od_zranienia++;
  // regeneracja (co sekundę, więc zawsze)
  if (b.czas_od_zranienia > 1) b.zdrowie += b.regeneracja_zdrowie_max;
  else b.zdrowie += b.regeneracja_zdrowie_min;
  if (b.zdrowie > b.zdrowie_max) b.zdrowie = b.zdrowie_max;
  cout << green << "Blob się leczy do wartości = [" << b.zdrowie << "]\n" << reset;
  
  if (b.czas_do_ataku == b.czas_od_ostatniego_ataku) {
    // Atak
    b.ile_atakow++;    
    double procent_obrazen = (b.zdrowie * 1.0) / (b.zdrowie_max * 1.0);
        cout << procent_obrazen << "%" << endl;
    L obrazenia = b.obrazenia * procent_obrazen;
    cout << red << ">>>> Blob atakuje z siłą " << obrazenia << "! <<<<\n" << reset;
    g.zdrowie -= obrazenia;
    cout << g.bohater << " zdrowie = [" << g.zdrowie << "]\n";
    z.zdrowie -= obrazenia;
    cout << z.bohater << " zdrowie = [" << z.zdrowie << "]\n";
    i.zdrowie -= obrazenia;    
    cout << i.bohater << " zdrowie = [" << i.zdrowie << "]\n";
    
    b.czas_od_ostatniego_ataku = 0;    
  }
}

int main() {
  setlocale(LC_ALL, "");  

  Blob blob;
  SuperHero gilgotek{ "Gilgotek", 50000, 30, 0, 500000 };
  SuperHero zgniotek{ "Zgniotek", 25000, 1, 0, 250000, true, 5 };
  SuperHero ignorator{ "Ignorator", 75000, 10, 0, 2000000 };
  ofstream zdrowie("zdrowie.csv");
  // pętla odliczająca czas
  L czas = 0;
  do {
    czas++;
    cout << "Upłynęło sekund: " << czas << endl;
    sekunda(blob, gilgotek, zgniotek, ignorator);
    sekunda(gilgotek, blob);
    sekunda(zgniotek, blob);
    sekunda(ignorator, blob);
    zdrowie << blob.zdrowie << endl;
  } while
    (blob.zdrowie > 0 and
      (
        gilgotek.zdrowie > 0 or
        zgniotek.zdrowie > 0 or
        ignorator.zdrowie > 0
        )
      );
  if (blob.zdrowie < 0) {
    cout << red << "\n\nBLOB NIE ŻYJE !!!\n\n" << reset;
    cout << "Blob zginął w " << czas << " sekundzie walki.\n";
  }
  if (gilgotek.zdrowie < 0) cout << red << gilgotek.bohater << " NIE ŻYJE!!!\n\n" << reset;
  if (zgniotek.zdrowie < 0) cout << red << zgniotek.bohater << " NIE ŻYJE!!!\n\n" << reset;
  if (ignorator.zdrowie < 0) cout << red << ignorator.bohater << " NIE ŻYJE!!!\n\n" << reset;
  // ++ Zginie Zgniotek, zgnieciony glutem Bloba. ++
  zdrowie.close();
}
