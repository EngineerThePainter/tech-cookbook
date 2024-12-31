#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
// dla symulacji faktycznego upływu czasu
#include <chrono>
#include <thread>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
vector<string> klasy = { "1A","1B","1C","1D","2A","2B","2C","3A","3B","3C" };

map<string, int> odleglosci = { {"2p",28}, {"1p",18},{"E1",12}, {"E2",12}, {"E3",23} };

map<string, vector<string>> trasy = {
  { "1A", {"2p","1p","E1"}},{"1B",{"2p","1p","E2"}}, {"1C",{"2p","1p","E1"}}, {"1D",{"1p","E3"}},
  {"2A",{"1p","E3"}}, {"2B",{"1p","E2"}}, {"2C",{"1p","E2"}},
  {"3A",{"E3"}}, { "3B",{"E3"} }, { "3C",{"E3"} } };

map<string, int> ludzie = { { "1A", 18 },{"1B",21},{"1C",24}, {"1D",22}, {"2A",20},
{"2B",20},{"2C",26},{"3A",17},{"3B",19},{"3C",21} };

const float krok_czasu = 0.5; // pół sekundy jako minimalna jednostka upływu czasu

const chrono::milliseconds czas_faktyczny(0); // rzeczywiste pół sekundy 

struct Osoba {
  bool uczen = true; // false (nauczyciel)
  float metry = 0.; // metry do pokonania w szkole, zanim dojdzie do wyjścia
  // metry zmniejszają się 1 metr na 0.5 sekundy
  string wyjscie = ""; // którędy wychodzi (numer drzwi)
  string klasa = "";
};
struct Wyjscie {
  queue<Osoba*> osoby = {}; // kolejka osób, które podeszły do drzwi
  float odliczanie = 0.; // >0 nie może jeszcze przejść osoba, ==0 możesz puścić
  int ile = 0; // ile osób naraz można przepuścić, gdy odliczanie==0
  float czekanie = 0.; // co ile sekund można przepuścić wskazaną liczbę osób
};
struct Sala {
  queue<Osoba*> osoby = {}; // kolejka osób, które są w klasie przed ewakuacją
  float odliczanie = 1.; // 0 wypuść, >0 jeszcze nie można
  // ponieważ przepustowość drzwi w salach, to osoba na sekundę:
  int ile = 1; // ile osób może naraz wyjść po upływie 1 sekundy
  float czekanie = 1.; // co ile sekund można przepuścić 1 osobę
};

// funkcja umieszcza odpowiednią liczbę osób w salach (stan przed 8:00), ustalanie długości tras
void generator_start(string klasa, Sala& s) {
  float metry = 0;
  // z trasy obliczam liczbę metrów do przejścia dla tej osoby 
  // (np. po wyjściu z sali lekcyjnej osoba musi przejść pierwsze piętro i parter itd.)
  for (auto& miejsce : trasy[klasa]) metry += odleglosci[miejsce];
  // na podstawie liczby uczniów w klasie dodaję do sali s odpowiednią liczbę osób Osoba
  for (int i = 1; i <= ludzie[klasa]; i++) {
    s.osoby.push(new Osoba());
    s.osoby.back()->metry = metry; // tyle musi przejść
    s.osoby.back()->wyjscie = trasy[klasa].back(); // do tego wyjścia się ustawia
    s.osoby.back()->klasa = klasa; // z której klasy (np. 1A) jest ta osoba
  }
  // nie zapominajmy, że w każdej sali jest jeden nauczyciel,
  // którego dodaję na koniec kolejki z osobami w klasie
  s.osoby.push(new Osoba()); // + nauczyciel
  s.osoby.back()->uczen = false; // to nie uczeń
  s.osoby.back()->metry = metry; // musi przejść tyle metrów co każdy uczeń
  s.osoby.back()->wyjscie = trasy[klasa].back(); // wychodzi z klasą jako ostatni
  s.osoby.back()->klasa = klasa;
}
// sprawdzam, czy w salach znajduje się choćby jedna osoba
bool czy_sale_puste(map<string, Sala>& sale) {
  for (auto [klasa, sala] : sale) {
    if (sala.osoby.size()) return false;
  }
  return true;
}
// czy w kolejkach przed wyjściami ze szkoły są jeszcze jakieś osoby?
bool czy_wyjscia_puste(map<string, Wyjscie>& wyjscia) {
  for (auto& [klasa, wyj] : wyjscia) {
    if (wyj.osoby.size()) return false;
  }
  return true;
}

int main() {
  setlocale(LC_ALL, "");
  /*
    Zadanie rozwiąże za mnie proces symulacji. Nie będę wykonywać obliczeń poprzez poszukiwanie
    wzorów dla upływającego czasu i kolejnych zdarzeń, ale każda osoba będzie we właściwym czasie
    i zgodnie z regułami, odległościami, prędkościami itp. wykonywać w upływającym czasie odpowiednie czynności
  */

  // mapa wszystkich drzwi wyjściowych, kolejki osób przed nimi są puste
  map<string, Wyjscie> wyjscia = { {"E1",Wyjscie()}, {"E2",Wyjscie()}, {"E3",Wyjscie()} };
  // ustawiam parametry przepustowości
  wyjscia["E1"].ile = 1; wyjscia["E1"].czekanie = wyjscia["E1"].odliczanie = 2.; // 1 osoba na 2 sekundy
  wyjscia["E2"].ile = 1; wyjscia["E2"].czekanie = wyjscia["E2"].odliczanie = 2.5; // 1 na 2.5 sekundy
  wyjscia["E3"].ile = 3; wyjscia["E3"].czekanie = wyjscia["E3"].odliczanie = 1.; // 3 na 1 sekundę

  // lista osób, które obecnie wyszły z klas i poruszają się po korytarzach (piętra i parter),
  // ale jeszcze nie podeszły do przydzielonych im wyjść
  list<Osoba*> korytarz = {};

  // lista sal, w których będą wszystkie osoby z klas i nauczyciele
  map<string, Sala> sale;

  // osoby poza szkołą, już uratowane
  vector<Osoba*> ewakuowani;

  // w każdej sali umieszczam uczniów i nauczyciela zgodnie z liczbami podanymi w zadaniu
  for (auto& klasa : klasy) {
    sale[klasa] = Sala();
    generator_start(klasa, sale[klasa]);
  }
  // sprawdzam, czy liczba osób w salach jest właściwa?
  for (auto& klasa : klasy) {
    cout << "W sali klasy " << klasa << " znajduje się " << sale[klasa].osoby.size() << " osób\n";
  }
  float czas = 0.; // sekundy, które upłyną od 8:00

  /* GŁÓWNA PĘTLA SYMULACJI */

  // dopóki sale nie są puste lub wciąż ktoś jest na korytarzach szkolnych,
  // lub kolejki przed drzwiami wyjściowymi nie są puste - wykonuj sumulację,
  // każdy krok pętli to upływ krok_czasu sekund (dla nas to 0.5 sekundy)
  while (korytarz.size() or !czy_sale_puste(sale) or !czy_wyjscia_puste(wyjscia)) {
    // opuszczanie wyjścia E1, E2, E3 (o ile ktoś już jest, by opuścić)
    for (auto& [nazwa, wyjscie] : wyjscia) {
      if (wyjscie.osoby.size()) { // jeżeli są osoby w kolejce przed wyjściem        
        if (wyjscie.odliczanie > 0) wyjscie.odliczanie -= krok_czasu; // upływ czasu
        if (wyjscie.odliczanie == 0.) { // można puszczać (przepustowość pozwala)
          // wypuszczam dopuszczalną liczbę osób w kolejce, o ile te osoby tam są
          for (int i = 1; i <= wyjscie.ile and wyjscie.osoby.size(); i++) {
            Osoba* o = wyjscie.osoby.front(); // pierwsza w kolejce
            wyjscie.osoby.pop(); // wypuszczona
            ewakuowani.push_back(o); // już jest w ewakuowanych
            cout << "Osoba z klasy " << o->klasa << " ewakuowana przez "
              << nazwa << " po upływie " << czas + krok_czasu << "sek.\n";
          }
          wyjscie.odliczanie = wyjscie.czekanie; // musimy odczekać
        }
      }
      else {
        wyjscie.odliczanie = wyjscie.czekanie; // nie ma osób, przepustowość "czeka"
      }
    }
    // poruszanie się po korytarzu
    // prędkość ruchu to 2 metry na sekundę, czyli 1 metr na 0.5 sekundy
    for (auto it = korytarz.begin(); it != korytarz.end(); ) {
      auto osoba = *it;
      if (osoba->metry > 0) { // jeszcze idzie
        osoba->metry -= 1;
        cout << ((osoba->uczen) ? "Uczeń" : "Nauczyciel") << " z klasy " << osoba->klasa << " idzie korytarzem...\n";
        if (osoba->metry == 0) { // skończyła
          // opuszczanie korytarza, wejście do kolejki wyjść
          it = korytarz.erase(it);
          wyjscia[osoba->wyjscie].osoby.push(osoba);
        }
        if (it != korytarz.end()) it++;
      }
    }
    // opuszczanie sal i wejście na korytarz (osoba na sekundę)
    for (auto& [klasa, sala] : sale) { // sprawdzam każdą salę
      if (sala.osoby.size()) { // jeżeli ktoś tu jeszcze jest w sali
        sala.odliczanie -= krok_czasu; // odliczam czas dla przepustowości
        if (sala.odliczanie == 0.) { // można wypuścić
          // ile osób można wypuścić, tyle wypuszczam
          for (int i = 1; i <= sala.ile; i++) {
            Osoba* osoba = sala.osoby.front(); // osoba pierwsza w kolejce...
            sala.osoby.pop(); // ...wyszła z sali...
            korytarz.push_back(osoba); // ...na korytarz
            cout << ((osoba->uczen) ? "Uczeń" : "Nauczyciel") << " z klasy " << osoba->klasa << " opuszcza salę...\n";
          }
          // ustawiam pauzę, muszę poczekać przed 
          // puszczeniem następnych zgodnie z przepustowością drzwi
          sala.odliczanie = sala.czekanie;
        }
      }
    }
    czas += krok_czasu;
    cout << "\n\n [" << czas << "s.] \n\n";
    this_thread::sleep_for(czas_faktyczny);
  }
  cout << "Ewakuowanych: " << ewakuowani.size() << endl;
  cout << "Czas ewakuacji: " << czas << " sek.\n";
  cout << "Ostatnia osoba:" << ((ewakuowani.back()->uczen) ? " uczeń " : " nauczyciel ")
    << " z klasy " << ewakuowani.back()->klasa << endl;
}
