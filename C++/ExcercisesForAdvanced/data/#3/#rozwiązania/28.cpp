#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <map>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
bool szansa(UL s) {
  return (rand() % 100 + 1 <= s);
}
//////////////////////////////////////////////////////
map<char, UL> ile_wydarzen = { {'A',0}, {'B',0}, {'C',0}, {'D',0}, {'E',0} };
map<char, UL> szanse = { {'A',5}, {'B',20}, {'C',50}, {'D',60}, {'E',90} };
// odliczanie to : { wydarzenie, {sekundy od ostatniego wydarzenia, co sekund ile wydarzenie} }
map<char, pair<float, float>> odliczanie = { {'A',{0,1}}, {'B',{0,3}}, {'C',{0,4}}, {'D',{0,7.5}}, {'E',{0,8}} };
float ile_sek_od_D = -1; // ile upłynęło czasu od D
float odD = 3; // tyle po D, aby wydarzyło się E
bool czyD = false;
float krok_czasu = 0.5; // 0.5 sekundy
float czas = 0; // sekundy obliczające czas trwania całej symulacji
UL ileA = 10; // tyle A, by zatrzymać symulację

int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  while (true) {
    czyD = false; // czy w tej jednostce czasu zadziało się D?
    // A 
    // jeżeli minął czas oczekiwania na zdarzenie
    if (odliczanie['A'].first == odliczanie['A'].second)
      if (szansa(szanse['A'])) {
        cout << "[A] w " << czas << " sekundzie.\n";
        ile_wydarzen['A']++; // wydarzenie zaistniało
        odliczanie['A'].first = 0; // zerowanie czasu oczekiwania
      }
      else odliczanie['A'].first = 0;
    odliczanie['A'].first += krok_czasu; // upływ czasu 
    if (ile_wydarzen['A'] == ileA) {
      cout << "A = " << ileA << ". STOP\n";
      break; // natychmiast zakończ
    }

    // B, C, D
    for (auto c : { 'B', 'C', 'D' }) {
      if (odliczanie[c].first == odliczanie[c].second)
        if (szansa(szanse[c]))
        { // zaistniało wydarzenie 
          ile_wydarzen[c]++;
          cout << "[" << c << "] w " << czas << " sekundzie.\n";
          odliczanie[c].first = 0;
          if (c == 'D') {
            czyD = true;
            ile_sek_od_D = 0;
          }
        }
        else odliczanie[c].first = 0;
      odliczanie[c].first += krok_czasu;
    }
    if (ile_sek_od_D >= 0 and !czyD) ile_sek_od_D += krok_czasu;
    // E
    if (ile_sek_od_D <= odD and ile_sek_od_D != -1)
      cout << "ile sekund od D: " << ile_sek_od_D << endl;
    if (odliczanie['E'].first == odliczanie['E'].second and ile_sek_od_D <= odD)
      if (szansa(szanse['E'])) {
        ile_wydarzen['E']++;
        cout << "[E] w " << czas << " sekundzie.\n";
        odliczanie['E'].first = 0;
      }
      else odliczanie['E'].first = 0;

    odliczanie['E'].first += krok_czasu;
    czas += krok_czasu;
    cout << "CZAS = " << czas << "\n";
    // możesz cofnąć komentarz dla spowolnienia czasu i lepszej obserwacji wydarzeń
    // this_thread::sleep_for(chrono::milliseconds(500)); // odczekaj 0,5 sekundy
  }

  cout << "Ile razy wystąpiło każde wydarzenie?\n";
  for (auto [c, ile] : ile_wydarzen) {
    cout << c << " " << ile << endl;
  }

  cout << "Symulacja trwała " << czas << " sekund.\n";
}
