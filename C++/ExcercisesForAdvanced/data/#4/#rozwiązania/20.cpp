#include <iostream>
#include <ratio>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::literals::chrono_literals;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
enum class Klawisz { Pauza, C, D, E, F, G, A, H, Cis, Dis, Fis, Gis, Ais };
map<Klawisz, string> KlawiszOpis{
  {Klawisz::Pauza,"Pauza" }, {Klawisz::C,"C"}, {Klawisz::D,"D"}, {Klawisz::E,"E"},
  {Klawisz::F,"F"}, {Klawisz::G,"G"}, {Klawisz::A,"A"}, {Klawisz::H,"H"},
  {Klawisz::Cis,"Cis"}, {Klawisz::Dis,"Dis"}, {Klawisz::Fis,"Fis"},
  {Klawisz::Gis,"Gis"}, {Klawisz::Ais,"Ais"}
};
enum class Oktawa { O1, O2, O3, O4 };
map<Oktawa, string> OktawaOpis{
  {Oktawa::O1,"1"}, {Oktawa::O2,"2"}, {Oktawa::O3,"3"}, {Oktawa::O4,"4"}
};
typedef ratio<1, 16> atom; // jedna szesnasta, ale można zmienić na inną (uniwersalne!)
typedef pair<UL, atom>  czas;
class Dzwiek {
public:
  Klawisz k;
  Oktawa o;
  czas czas_trwania;
};
class Melodia {
public:
  vector<Dzwiek> nutki;
  void dodaj(Klawisz d, Oktawa o, UL t) {
    if (o == Oktawa::O4 and d != Klawisz::C) {
      cout << "Niedozwolony zakres!\n"; // D4, E4 itd. Tylko C4 możliwy
      return;
    }
    nutki.push_back(Dzwiek({ d,o,czas({t,atom()}) }));
  }
  void graj() {
    cout << "START\n\n";
    for (auto& d : nutki) {      
      if (d.k != Klawisz::Pauza) {
        cout << KlawiszOpis[d.k] << OktawaOpis[d.o] << "... ";
      }
      else {
        cout << " (pauza) ";
      }
      // obliczam czas trwania w przybliżonych mikrosekundach
      auto catom =  (d.czas_trwania.second.num * 1.0 / d.czas_trwania.second.den * 1.0) * 1s;      
      cout << setprecision(2) << fixed << d.czas_trwania.first * catom << endl;
      this_thread::sleep_for(d.czas_trwania.first * catom);
    }
    cout << "\n\nKONIEC\n\n";
  }
  void do_pliku(string nazwa) {
    ofstream plik(nazwa);
    for (auto& d : nutki) {
      plik << UL(d.k) << " " << UL(d.o) << " " << d.czas_trwania.first << endl;
    }
    plik.close();
  }
  void z_pliku(string nazwa) {
    ifstream plik(nazwa);
    nutki.clear();
    UL kl, okt, cz;
    while (plik >> kl >> okt >> cz) {
      nutki.push_back(Dzwiek({ Klawisz(kl),Oktawa(okt),czas({cz,atom()}) }));
    }
    plik.close();
  }
};
int main() {
  setlocale(LC_ALL, "");
  Melodia M;
  M.dodaj(Klawisz::C, Oktawa::O2, 32); // 2 sek. C2
  M.dodaj(Klawisz::D, Oktawa::O2, 32);
  M.dodaj(Klawisz::E, Oktawa::O2, 32);
  M.dodaj(Klawisz::F, Oktawa::O2, 32);

  M.dodaj(Klawisz::Pauza, Oktawa::O2, 16); // 1 sek. pauzy

  M.dodaj(Klawisz::G, Oktawa::O2, 2); // 1/8 sek. G2
  M.dodaj(Klawisz::A, Oktawa::O2, 2);
  M.dodaj(Klawisz::H, Oktawa::O2, 16); // 1 sek. H2
  M.dodaj(Klawisz::C, Oktawa::O3, 8); // 1/2 sek. C3

  M.do_pliku("melodia.txt");
  M.z_pliku("melodia.txt");

  M.graj();
}
