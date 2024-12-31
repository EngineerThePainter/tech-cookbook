#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////
class Czas {
private:
  string reprezentacja;
  unsigned godz;
  unsigned min;
  unsigned sek;
  // godz, min, sek -> na napis
  void naNapis() {    
    string format("%02d");    
    char bufor1[100], bufor2[100], bufor3[100];
    sprintf_s(bufor1, 100, format.c_str(), godz);
    sprintf_s(bufor2, 100, format.c_str(), min);
    sprintf_s(bufor3, 100, format.c_str(), sek);
    reprezentacja = string(bufor1) + ":" + string(bufor2) + ":" + string(bufor3);
  }
  void naLiczby() {
    godz = stoul(reprezentacja.substr(0, 2));
    min = stoul(reprezentacja.substr(3, 2));
    sek = stoul(reprezentacja.substr(6, 2));
  }
public:
  // Czas("12:34:22")
  Czas(string r) :reprezentacja(r) {
    naLiczby();
  }
  // Czas(12,34,22) -> 12:34:22
  Czas(unsigned g, unsigned m, unsigned s) :godz(g), min(m), sek(s) {
    naNapis();
  }
  string operator()() { return reprezentacja; }
  // ustawia nowe wartości
  void operator()(unsigned g, unsigned m, unsigned s) {
    godz = g; min = m; sek = s;
    naNapis();
  }
  unsigned Godz() { return godz; }
  unsigned Min() { return min; }
  unsigned Sek() { return sek; }
  // przypisanie
  void operator=(Czas c) {
    godz = c.Godz();
    min = c.Min();
    sek = c.Sek();
    naNapis();
  }
  // zwiększa czas o podane sekundy
  void sekundyPlus(unsigned sekundy) {
    sek += sekundy;
    unsigned minuty = sek / 60;
    sek %= 60;
    if (minuty > 0) minutyPlus(minuty);
    else naNapis();
  }
  void minutyPlus(unsigned minuty) {
    min += minuty;
    unsigned godziny = min / 60;
    min %= 60;
    if (godziny > 0) godzinyPlus(godziny);
    else naNapis();
  }
  void godzinyPlus(unsigned godziny) {
    godz += godziny;
    unsigned dni = godz / 24; // i tak ignoruję dni
    godz %= 24;
    naNapis();        
  }
  // zamienia godzinę na sekundy, licząc od 00:00:00
  unsigned naSekundy() {
    return godz * 3600 + min * 60 + sek;
  }
  // ustawia czas od godziny 00:00:00 na podstawie sekund
  void naPodstawieSekund(unsigned sekundy) {
    godz = min = sek = 0;
    naNapis();
    sekundyPlus(sekundy);
  }
  // różnica czasu w sekundach
  unsigned operator-(Czas& c) {
    long long c1 = naSekundy();
    long long c2 = c.naSekundy();
    return abs(c1-c2);
  }
};
class Robot {
public:
  Czas start;
  Czas koniec;
  Robot(Czas&& s, Czas&& k): start(s), koniec(k){}  
  unsigned czasPracyRobotaWsek() {
    return start - koniec;
  }
  // ładna reprezentacja czasu pracy Robota (w godz,min,sek)
  string czasPracy() {
    Czas c(0, 0, 0);
    c.sekundyPlus(czasPracyRobotaWsek());
    return c();
  }
  // czy Robot pracował o podanej godzinie?
  bool czyPracowal(Czas c) {
    return (start.naSekundy() <= c.naSekundy() and c.naSekundy() <= koniec.naSekundy());
  }
};

class Praca {
  vector<Robot> magazyn;
public:
  Praca() {
    magazyn.reserve(100);
    ifstream plik("9_czas.txt");
    string start, koniec;
    while (plik >> start >> koniec) {
      magazyn.push_back(Robot(Czas(start), Czas(koniec)));
    }
    plik.close();
  }
  // pokazuje listę przeczytanych danych
  void pokaz(unsigned ile=100) {
    for (unsigned nr = 1;  auto & robot : magazyn) {
      cout << nr << ". " << robot.start() << " - " << robot.koniec() << " = " << robot.czasPracyRobotaWsek() 
        << "(" << robot.czasPracy() << ")" << endl;
        nr++;
        if (nr > ile) break;
    }
  }
  // posortuj wg najwcześniejszej godziny rozpoczęcia
  void sortujWgRozpoczecia() {
    sort(magazyn.begin(), magazyn.end(), 
      [](Robot& Robot1, Robot& Robot2) {
        return (Robot1.start.naSekundy() < Robot2.start.naSekundy());
      });
  }
  // posortuj wg najdłuższej pracy robota
  void sortujWgCzasuPracy() {
    sort(magazyn.begin(), magazyn.end(),
      [](Robot& Robot1, Robot& Robot2) {
        return (Robot1.czasPracyRobotaWsek() > Robot2.czasPracyRobotaWsek());
      });
  }
  // liczę, ile robotów pracowało o wyznaczonym czasie
  void analiza() {
    vector<pair<Czas, Czas>> zakresy_czasu_pracy_gdy_100;
    Czas symulacja(0, 0, 0); // symulacja upływającego czasu
    // przeanalizuję każdą sekundę dnia pracy
    Czas zakres_start(0,0,0);    
    while (true) {
      unsigned ile_naraz = 0;
      for (Robot& r : magazyn) {
        if (r.czyPracowal(symulacja)) ile_naraz++;
      }      
      if (ile_naraz == 100) {
        if (zakres_start.naSekundy()==0) zakres_start = symulacja;
      }
      else {
        if (zakres_start.naSekundy() > 0) {          
          zakresy_czasu_pracy_gdy_100.push_back({ zakres_start,symulacja });
          zakres_start(0, 0, 0);          
        }
      }
      if (symulacja.naSekundy() == 3600 * 24 - 1) break; // ostatnia sekunda doby
      symulacja.sekundyPlus(1);
      
    }
    for (auto& zakres : zakresy_czasu_pracy_gdy_100) {
      cout << zakres.first() << " - " << zakres.second() << endl;
    }
  }
  vector<Robot> kopia() { return magazyn; }
};

int main() {
  setlocale(LC_ALL, "");  
  Praca P;
  auto kopia = P.kopia();

  P.sortujWgRozpoczecia();
  cout << "Najwcześniejsza godzina: " << endl;
  P.pokaz(1); 
  cout << endl;

  P.sortujWgCzasuPracy();
  auto drugakopia = P.kopia();
  P.pokaz(1);
  cout << "Najdłuższa praca to: ";
  cout << drugakopia[0].czasPracyRobotaWsek() << " sek. czyli " << drugakopia[0].czasPracy() << endl;  
  for (unsigned nr = 1; auto & robot : kopia) {
    if (robot.czasPracyRobotaWsek() == drugakopia[0].czasPracyRobotaWsek()) {
      cout << "Wykonał ją robot nr=" << nr << endl;
      break;
    }
    nr++;
  }
  cout << endl << "Zakres czasu pracy, podczas którego pracowało wszystkie 100 robotów: ";
  P.analiza();
}
