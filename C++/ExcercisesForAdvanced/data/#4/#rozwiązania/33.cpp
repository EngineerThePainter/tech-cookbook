#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <list>
#include <string>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class Pojazd; // predeklaracja

class Metr {
public:
  inline static UL global_nr = 1;
  UL nr = 0;
  shared_ptr<Pojazd> pojazd = nullptr;
  string trasa; // 1 metr odcinka na trasie "AB", "BA", "CD", "DC"
  Metr(string t) : trasa(t) { nr = global_nr++; }
};

inline class Trasy {
public:
  map<string, map<UL, shared_ptr<Metr>>> metry; // metrowe odcinki dróg
  map<UL, shared_ptr<Metr>> globalnie; // mapa ze wszystkimi odcinkami dróg
  Trasy() {
    for (auto trasa : { "AB","BA","CD","DC" }) {
      for (UL metr = 1; metr <= 100; metr++) {
        metry[trasa][metr] = make_shared<Metr>(trasa);
        globalnie[Metr::global_nr - 1] = metry[trasa][metr];
      }
    }
  }
  queue<shared_ptr<Metr>> zbudujTrase(string trasa) {
    queue<shared_ptr<Metr>> sekwencja_do_przejechania;
    if (trasa == "AB") {
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["AB"][metr]);
    }
    else if (trasa == "BA") {
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["BA"][metr]);
    }
    else if (trasa == "ACD") {
      for (UL metr = 1; metr <= 50; metr++)
        sekwencja_do_przejechania.push(metry["AB"][metr]);
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["CD"][metr]);
    }
    else if (trasa == "BCD") {
      for (UL metr = 1; metr <= 50; metr++)
        sekwencja_do_przejechania.push(metry["BA"][metr]);
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["CD"][metr]);
    }
    else if (trasa == "DCA") {
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["DC"][metr]);
      for (UL metr = 51; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["BA"][metr]);
    }
    else if (trasa == "DCB") {
      for (UL metr = 1; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["DC"][metr]);
      for (UL metr = 51; metr <= 100; metr++)
        sekwencja_do_przejechania.push(metry["AB"][metr]);
    }
    return sekwencja_do_przejechania;
  }
  // testowane odcinki B* A*
  bool jestPojazdNaOdcinku(string odcinek) {
    if (odcinek == "B*") { // 1-50 (do skrzyżowania), droga BA
      for (UL m = 1; m <= 50; m++) if (metry["BA"][m]->pojazd != nullptr) return true;
      return false;
    }
    else if (odcinek == "A*") {
      for (UL m = 1; m <= 50; m++) if (metry["AB"][m]->pojazd != nullptr) return true;
      return false;
    }
  }
} T;

class Pojazd {
public:
  inline static UL globalny_nr = 1;
  inline static map<UL, shared_ptr<Pojazd>> pojazdy_oczekujace; // nie wjechały jeszcze na skrzyżowanie
  inline static map<UL, shared_ptr<Pojazd>> pojazdy; // pojazdy na skrzyżowaniu
  inline static list<shared_ptr<Pojazd>> pojazdy_odjechane; // odjechane, że hej!

  string trasa; // "AB", "BCD" itd.
  UL nr = 0;
  UL oczekuj = 0; // ile razy czekał  
  bool ruch_mozliwy = false;
  queue<shared_ptr<Metr>> trasaDoPokonania;
  shared_ptr<Metr> aktualnaPozycja;
  // trasa = np. "AB", "DCA" itd.  
  Pojazd() {}
  Pojazd(string ustaw_trase) {
    nr = globalny_nr++;
    trasaDoPokonania = T.zbudujTrase(ustaw_trase);
    trasa = ustaw_trase;
  }
  // testy ruchu w obecnym momencie
  string test_mozliwosci_ruchu() {
    string info("");
    // test czy następny metr na trasie jest wolny
    if (trasaDoPokonania.size() == 0) {
      ruch_mozliwy = true; // odjedzie w siną dal
      return info;
    }
    auto nastepny_metr = trasaDoPokonania.front();
    bool pojazd_przed, pas_wolny = true;
    if (nastepny_metr->pojazd == nullptr)
      pojazd_przed = false; // nie ma pojazdu przed pojazdem (wolny metr drogi)
    else
      pojazd_przed = true;
    // test, czy mogę wejść z tej drogi na inną drogę (w zależności od rasy)
    if (trasa == "ACD" and aktualnaPozycja->nr == 50) { // tuż przed skrętem w lewo sprawdzam
      if (T.jestPojazdNaOdcinku("B*")) { // czekam
        pas_wolny = false;
      }
      else { // mogę jechać
        pas_wolny = true;
      }
    }
    else if (trasa == "DCA" and aktualnaPozycja->nr == 100) {
      if (T.jestPojazdNaOdcinku("B*")) { // czekam
        pas_wolny = false;
      }
      else { // mogę jechać
        pas_wolny = true;
      }
    }
    else if (trasa == "DCB" and aktualnaPozycja->nr == 100) {
      if (T.jestPojazdNaOdcinku("B*") or T.jestPojazdNaOdcinku("A*")) { // czekam
        pas_wolny = false;
      }
      else { // mogę jechać
        pas_wolny = true;
      }
    }
    if (!pojazd_przed and pas_wolny) {
      ruch_mozliwy = true;
    }
    else {
      ruch_mozliwy = false;
      oczekuj++;      
    }
    return info;
  }
  // testy za nami - tylko się przesuwam po swojej trasie
  string ruch() {
    string info;
    if (ruch_mozliwy) {
      this->aktualnaPozycja->pojazd = nullptr; // tu go nie ma
      if (this->trasaDoPokonania.size() == 0) { // znika z symulacji, odjechał dalej
        pojazdy_odjechane.push_back(pojazdy[this->nr]);
        pojazdy[this->nr] = nullptr;
        info = "Pojazd " + to_string(this->nr) + " opuścił skrzyżowanie.\n";
      }
      else { // ruch po trasie
        this->aktualnaPozycja = trasaDoPokonania.front();
        trasaDoPokonania.front()->pojazd = pojazdy[this->nr];
        trasaDoPokonania.pop();
      }
      ruch_mozliwy = false;
    }
    return info;
  }

};


class Symulacja {
public:
  // {sekunda wprowadzenia, Pojazd}  
  inline static UL czas = 0;
  Symulacja() {
    setlocale(LC_ALL, "");
    ifstream plik("33_pojazdy.txt");
    string trasa;
    UL sekunda;
    while (plik >> trasa >> sekunda) {
      Pojazd::pojazdy_oczekujace[sekunda] = make_shared<Pojazd>(trasa);
    }
    cout << cz() << "Załadowano symulator z pojazdami. Liczba pojazdów: = "
      << Pojazd::pojazdy_oczekujace.size() << endl;
    plik.close();
  }
  void start() {
    do {      
      // sprawdzam, czy pojazdy w ruchu mogą ruszyć się w tej sekundzie
      for (auto [nrp, pojazd] : Pojazd::pojazdy) {
        auto info = pojazd->test_mozliwosci_ruchu();
        if (info != "") cout << cz() << info;
      }
      // dokonuję ruchów po testach
      for (auto [nrp, pojazd] : Pojazd::pojazdy) {
        string info = pojazd->ruch();
        if (info != "") cout << cz() << info;
      }
      // czyszczę te, które wyjechały
      if (Pojazd::pojazdy.size())
        for (auto it = Pojazd::pojazdy.begin(); it != Pojazd::pojazdy.end();) {
          if (it->second == nullptr) it = Pojazd::pojazdy.erase(it);
          else it++;
        }

      // pojazd pojawia się na trasie we wskazanej sekundzie
      if (Pojazd::pojazdy_oczekujace.size() and czas == Pojazd::pojazdy_oczekujace.begin()->first) {
        auto pojazd = Pojazd::pojazdy_oczekujace.begin()->second;
        auto metr = pojazd->trasaDoPokonania.front();
        if (metr->pojazd != nullptr) {
          cout << cz() << "<<<<<<<<Pojazd nr " << pojazd->nr 
            << " nie może wjechać! Droga zatarasowana!>>>>>>>>\n";
        }
        else {
          cout << cz() << "Pojazd nr " << pojazd->nr << " pojawia się na skrzyżowaniu.\n";
          metr->pojazd = pojazd;
          pojazd->aktualnaPozycja = metr;
          pojazd->trasaDoPokonania.pop(); // ten odcinek zaliczony
          Pojazd::pojazdy[pojazd->nr] = pojazd; 
          Pojazd::pojazdy_oczekujace.erase(Pojazd::pojazdy_oczekujace.begin());
        }
      }
      czas++;
    } while (Pojazd::pojazdy_odjechane.size() < 100);
  }
  static string cz() {
    return ":::" + to_string(czas) + " ";
  }
};

int main() {
  setlocale(LC_ALL, "");
  Symulacja S;
  S.start();
  // odpowiedź
  Pojazd::pojazdy_odjechane.sort([](auto a, auto b) {
      return (a->oczekuj > b->oczekuj);
    });
  cout << "Pojazd nr " << Pojazd::pojazdy_odjechane.front()->nr << 
    " " << Pojazd::pojazdy_odjechane.front()->oczekuj << "sek." << endl;
}
