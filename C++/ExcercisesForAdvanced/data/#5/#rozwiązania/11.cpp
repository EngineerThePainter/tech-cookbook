#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////
inline class Miasta : public map<unsigned, pair<string, string>> {
public:
  Miasta() {
    ifstream plik("11_miasta_krainy.txt");
    string nazwaMiasta, nazwaKrainy;
    unsigned nrMiasta;
    // ignoruję pierwszy wiersz: nr_miasta, miasto, kraina
    getline(plik, nazwaMiasta);
    while (plik >> nrMiasta >> nazwaMiasta >> nazwaKrainy) {
      (*this)[nrMiasta] = { nazwaMiasta,nazwaKrainy };
    }
    plik.close();
  }
  unsigned odszukajPoNazwie(string nazwaMiasta) {
    for (auto& [nrMiasta, miasto_kraina] : (*this)) {
      if (nazwaMiasta == miasto_kraina.first) return nrMiasta;
    }
    return 0;
  }
  string nazwaMiasta(unsigned nr) { return (*this)[nr].first; }
  string nazwaKrainy(unsigned nr) { return (*this)[nr].second; }
} M;

inline class Kopalnie : public map<unsigned, unsigned> {
public:
  Kopalnie() {
    ifstream plik("11_kopalnie.txt");
    unsigned nr;
    string nazwa;
    // ignoruję pierwszy wiersz // nr kopalni, przypisane miasto (nazwa) 
    getline(plik, nazwa);
    while (plik >> nr >> nazwa) {
      (*this)[nr] = M.odszukajPoNazwie(nazwa);
    }
    plik.close();
  }
  string nazwaMiasta(unsigned nr) { return M.nazwaMiasta((*this)[nr]); }
  string nazwaKrainy(unsigned nr) { return M.nazwaKrainy((*this)[nr]); }
} K;

// {dzien: {kopalnia: wydobycie}}
inline class Wydobycie : public map<string, map<unsigned,double>> {
public:
  double charytatywnie = 0;
  double soboty_niedziele = 0;
  Wydobycie() {
    ifstream plik("11_wydobycie.txt");
    string dzien, urobekS;
    // ignorujemy wiersz z nazwami kolumn
    getline(plik, dzien);    
    for (unsigned nrDnia = 1; plik >> dzien; nrDnia++) {
      for (auto nr_kopalni = 1; nr_kopalni <= 200; nr_kopalni++) {
        plik >> urobekS;        
        urobekS.replace(urobekS.find(","), 1, ".");                        
        (*this)[dzien][nr_kopalni] = stod(urobekS);     
        double datek = stod("0.00" + urobekS.substr(urobekS.find(".") + 2));
        charytatywnie += datek;        
        // gdy jest sobota lub niedziela, wiemy, że pierwszy dzień to środa, zatem 4, 5 to sobota i niedziela itd.
        if (nrDnia%7==4 or nrDnia%7==5)
          soboty_niedziele += (*this)[dzien][nr_kopalni];
      }
    }
    plik.close();
  }
  vector<pair<string, double>> wydobycieWgMiastNiemalejaco() {
    map<string, double> wyniki; // miasto->wydobycie
    for (auto& [data, m] : (*this)) {
      for (auto& [nrKopalni, wydobycie] : m) {        
        wyniki[K.nazwaMiasta(nrKopalni)] += wydobycie;
      }
    }
    vector<pair<string, double>> posortuj(wyniki.begin(), wyniki.end());
    sort(posortuj.begin(), posortuj.end(),
      [&](auto&a, auto&b) {
        return (a.second > b.second);
      });
    return posortuj;
  }
  vector<pair<string, double>> wydobycieWgKrainyNiemalejaco() {
    map<string, double> wyniki; // miasto->wydobycie
    for (auto& [data, m] : (*this)) {
      for (auto& [nrKopalni, wydobycie] : m) {
        wyniki[K.nazwaKrainy(nrKopalni)] += wydobycie;
      }
    }
    vector<pair<string, double>> posortuj(wyniki.begin(), wyniki.end());
    sort(posortuj.begin(), posortuj.end(),
      [&](auto& a, auto& b) {
        return (a.second > b.second);
      });
    return posortuj;
  }
  vector<pair<string, double>> wydobycieWgDniaNiemalejaco() {
    map<string, double> wyniki; // miasto->wydobycie
    for (auto& [data, m] : (*this)) {
      for (auto& [nrKopalni, wydobycie] : m) {
        wyniki[data] += wydobycie;
      }
    }
    vector<pair<string, double>> posortuj(wyniki.begin(), wyniki.end());
    sort(posortuj.begin(), posortuj.end(),
      [&](auto& a, auto& b) {
        return (a.second > b.second);
      });
    return posortuj;
  }
} W;

int main() {
  setlocale(LC_ALL, "");
  cout.precision(12);
  // w pliku „wydobycie” mamy 9 miejsc po przecinku, taka precyzja przy wyświetlaniu wystarczy;
  // można też posłużyć się wartością numeric_limits<double>::max_digits10 zamiast 12 (#include <limits>)
  
  cout << "Które miasto wydobyło najwięcej ton kruszcu? Podaj nazwę.\n";
  auto odp1 = W.wydobycieWgMiastNiemalejaco();
  cout << fixed << odp1[0].first << " " << odp1[0].second << endl;
 
  auto odp2 = W.wydobycieWgKrainyNiemalejaco();
  cout << "\nKtóra kraina wydobyła najwięcej ton kruszczu? Podaj nazwę.\n";
  cout << fixed << odp2[0].first << " " << odp2[0].second << endl;  

  cout << "\nIle łącznie kruszczu przekazano na cele charytatywne? Podaj jak najdokładniejszą wartość.\n";
  cout << fixed << W.charytatywnie << endl;

  cout << "\nPodaj łączne wydobycie kruszcu w soboty i niedziele.\n";
  cout << fixed << W.soboty_niedziele << endl;

  auto odp5 = W.wydobycieWgDniaNiemalejaco();
  cout << "\nKtórego dnia wydobyto najwięcej kruszczu? Podaj datę.\n";
  cout << fixed << odp5[0].first << " " << odp5[0].second << endl;  
}
