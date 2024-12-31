#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////
class Ork {
public:
  string imie;
  int zdrowie{ 0 };
  int zdrowie_max;
  int sila{ 0 };
  int pancerz{ 0 }; // nieobowiązkowa cecha :)
  Ork() {
    // generuję losowo: imię/siłę/zdrowie/pancerz
    cout << "Z brudu ziemi i złej woli Czerwonego Oka zrodził się ork: ";
    string sp = "ggggggggrrrrrrrrrrrrhhhkkksssss";
    string sa = "oooooouuuyyya";
    for (int i = rand() % 2 + 2; i >= 0; i--) {
      imie.push_back(sp[rand() % sp.size()]);
      if (rand() % 2) imie.push_back(sp[rand() % sp.size()]);
      imie.push_back(sa[rand() % sa.size()]);
    }
    imie[0] -= 97 - 65; // pierwsza mała literka angielska na dużą
    cout << imie << ". ";
    zdrowie_max = zdrowie = rand() % 200 + 100;
    sila = rand() % 20 + 5;
    pancerz = rand() % 5;
    cout << "(siła=" << sila << " zdrowie=" 
      << zdrowie_max << " pancerz=" << pancerz << ")\n";
  }
  void pochwalSie() {
    cout << "Ork " << imie << " posiada : siła=" << sila << " zdrowie="
      << zdrowie_max << " pancerz=" << pancerz << "\n";
  }
  ~Ork() { cout << "Zwłoki orka " << this->imie << " wyparowały...\n"; }
  // bijemy orka-przeciwnika, zwracamy komunikat opisujący efekt 
  string hit(shared_ptr<Ork> przeciwnik) {
    string komunikat;
    if (rand() % 2) {
      vector<string> opis{
        "trafia", "tnie po głowie", "przebija nogę",
        "rozcina brzuch", "miażdży ramię", "rani pysk", "okalecza ucho"
      };
      komunikat += this->imie + " " + opis[rand() % opis.size()] + " "
        + przeciwnik->imie + "!";
      // zabieram zdrowie przeciwnikowi, ale uwzględniam jego pancerz
      przeciwnik->zdrowie -= max(0, this->sila - przeciwnik->pancerz);
      komunikat += " (" + przeciwnik->imie + "=" +
        to_string(przeciwnik->zdrowie) + " zdrowia zostało)\n";
    }
    else {
      komunikat += this->imie + " nie trafia w " + przeciwnik->imie + "...\n";
    }
    return komunikat;
  }
  // cała walka
  static string Walka(shared_ptr<Ork> ork1, shared_ptr<Ork> ork2) {
    string komunikat;
    // losujemy, kto będzie zadawał pierwszy cios
    vector<shared_ptr<Ork>> orki;
    if (rand() % 2) {
      orki.push_back(ork1);
      orki.push_back(ork2);
    }
    else {
      orki.push_back(ork2);
      orki.push_back(ork1);
    }
    int ten = 0;
    int tego = 1;

    do {
      cout << orki[ten]->hit(orki[tego]);
      if (orki[tego]->zdrowie <= 0) {
        komunikat += orki[tego]->imie + " przegrywa i ginie! Zwycięski " +
          orki[ten]->imie + " unosi zmasakrowaną rękę "
          "w geście zwycięstwa! ARRGGGHHH!!!\n";
        komunikat += orki[ten]->imie + " zyskuje siłę i zdrowie (+1/+10)\n";
        orki[ten]->sila++;
        orki[ten]->zdrowie_max += 10;
        orki[ten]->zdrowie = orki[ten]->zdrowie_max;

      }
      ten = (ten + 1) % orki.size();
      tego = (tego + 1) % orki.size();
      this_thread::sleep_for(chrono::milliseconds(250)); // nie za szybko
    } while (orki[ten]->zdrowie > 0 and orki[tego]->zdrowie > 0);
    return komunikat;
  }
};
// zasady walk: 
// SERIA 1: 12 orków, 6 par walczy, przeżywa 6 orków.
// SERIA 2: walczą ork 1-2 i 3-4 i 5-6, przeżywa 3 orków.
// SERIA 3: walczą 1-2, zwycięski ork walczy w ostatniej walce z orkiem 3.
// Dla zachowania szans, ork 3, który nie walczył, zyskuje bonus identyczny
// jak zwycięzca pary 1-2


int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  vector<shared_ptr<Ork>> HORDA; // :)
  for (int i = 1; i <= 12; i++) HORDA.push_back(make_shared<Ork>());
  // SERIA 1
  cout << Ork::Walka(HORDA[0], HORDA[1]);
  cout << Ork::Walka(HORDA[2], HORDA[3]);
  cout << Ork::Walka(HORDA[4], HORDA[5]);
  cout << Ork::Walka(HORDA[6], HORDA[7]);
  cout << Ork::Walka(HORDA[8], HORDA[9]);
  cout << Ork::Walka(HORDA[10], HORDA[11]);
  // usuwam orki martwe po 1. serii
  erase_if(HORDA, [&](auto&& ork) { return (ork->zdrowie <= 0); });
  // SERIA 2
  cout << Ork::Walka(HORDA[0], HORDA[1]);
  cout << Ork::Walka(HORDA[2], HORDA[3]);
  cout << Ork::Walka(HORDA[4], HORDA[5]);
  // usuwam orki martwe po 2. serii
  erase_if(HORDA, [&](auto&& ork) { return (ork->zdrowie <= 0); });
  // SERIA 3
  cout << Ork::Walka(HORDA[0], HORDA[1]);
  // bonus dla orka 3 
  HORDA[2]->zdrowie += 10;
  HORDA[2]->zdrowie_max += 10; // niepotrzebne, ale niech będzie
  HORDA[2]->sila += 1;
  // usuwam orki martwe po 3. serii
  erase_if(HORDA, [&](auto&& ork) { return (ork->zdrowie <= 0); });
  // OSTATNIA WALKA
  cout << Ork::Walka(HORDA[0], HORDA[1]);
  // usuwam orka martwego
  erase_if(HORDA, [&](auto&& ork) { return (ork->zdrowie <= 0); });
  cout << "ORK " << HORDA[0]->imie << "ZWYCIĘŻA OSTATECZNIE I NIEODWOŁALNIE.\n";  
  HORDA[0]->pochwalSie();
}
