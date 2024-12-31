#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
//////////////////////////////////////////////////////
enum rodzaj_paliwa { GAZ, ROPA, BENZYNA };
class Tankowanie {
public:
  string data;
  double litry;
  double cena;
  Tankowanie(string d, double li, double zl)
    :data(d), litry(li), cena(zl) {}
};
class Samochod {
public:
  Samochod() {}
  Samochod(string nr, string mod, string rok_p, string data_k, double licz_kup, rodzaj_paliwa rp) :
    nr_rej(nr), model(mod), rok_prod(rok_p), data_kupna(data_k),
    licznik_kupno(licz_kup), rodzaj(rp) {}
  string nr_rej;
  string model;
  string rok_prod;
  string data_kupna;
  double licznik_kupno;
  rodzaj_paliwa rodzaj;
  map<string, double> licznik; // data:stan licznika na koniec dnia
  vector<Tankowanie> tankowania;
  void tankuj(string data, double litr, double zl) {
    tankowania.push_back(Tankowanie(data, litr, zl));
  }
  void wprowadzLicznik(string data, double stan) {
    licznik[data] = stan;
  }
  string rodzajPaliwa() {
    if (rodzaj == rodzaj_paliwa::GAZ) return "gaz";
    if (rodzaj == rodzaj_paliwa::ROPA) return "ropa";
    return "benzyna";
  }
  double paliwoSuma(string rok) {
    double ilosc = 0;
    for (auto& t : tankowania)
      if (t.data.substr(0, 4) == rok) ilosc += t.litry;
    return ilosc;
  }
  double paliwoKoszt(string rok) {
    double kwota = 0;
    for (auto& t : tankowania)
      if (t.data.substr(0, 4) == rok) kwota += t.cena;
    return kwota;
  }
  /*
  Liczy km na podstawie danych z wpisów stanu licznika. Pierwszy wpis z roku kończy przejazd,
  zatem trzeba uwzględnić ostatni wpis wcześniejszego roku (albo stan początkowy licznika).
  Gdy pytam o rok, z którego wpisy nie istnieją, zwraca 0.
  */
  double ileKm(string rok) {
    double ostatnie_km, start = licznik_kupno;
    auto ostatni_rok_wczesniej = find_if(licznik.rbegin(), licznik.rend(),
      [rok](auto& it) {
        return (it.first.substr(0, 4) == to_string(stol(rok) - 1));
      });
    if (ostatni_rok_wczesniej != rend(licznik)) {
      start = ostatni_rok_wczesniej->second;
    }
    auto ostatni = find_if(licznik.rbegin(), licznik.rend(),
      [rok](auto& it) {
        return (it.first.substr(0, 4) == rok);
      });
    if (ostatni == rend(licznik)) ostatnie_km = start;
    else ostatnie_km = ostatni->second;
    return ostatnie_km - start;
  }
  double spalanie(string rok) {
    auto km = ileKm(rok);
    auto p = paliwoSuma(rok);
    if (km > 0) return p * (100. / km);
    else return 0;
  }

};

int main() {
  setlocale(LC_ALL, "");
  map<string, Samochod> FLOTA; // { nr_rejestracyjny, Samochod }
  FLOTA.emplace("1", Samochod("1", "Fiat 126p", "1980", "1984-02-02", 75000.0, rodzaj_paliwa::BENZYNA));
  FLOTA["1"].tankuj("1984-02-03", 25, 100);
  FLOTA["1"].tankuj("1984-02-12", 20, 86);
  FLOTA["1"].tankuj("1985-02-01", 44, 112);
  FLOTA["1"].tankuj("1985-02-10", 44, 112);
  cout << FLOTA["1"].paliwoSuma("1984") << endl; // paliwo w roku
  cout << FLOTA["1"].paliwoKoszt("1984") << endl; // koszt za paliwo w roku
  FLOTA["1"].wprowadzLicznik("1985-02-03", 75900);
  FLOTA["1"].wprowadzLicznik("1985-02-04", 76100);
  FLOTA["1"].wprowadzLicznik("1985-02-06", 77456);
  cout << FLOTA["1"].ileKm("1985") << endl; // 2456 km 
  cout << FLOTA["1"].ileKm("1986") << endl; // 0 km, bo nie ma wpisów z tego roku 
  cout << FLOTA["1"].spalanie("1985") << endl; // przybliżone spalanie na 100 km
}
