#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
struct Zawodnik {
  string imie;
  string gatunek;
  UL id;
};
map<UL,Zawodnik> zawodnicy; // lista zawodników, pary {id,Zawodnik}

struct Trasa {
  UL nr; // nr trasy
  // data, kiedy odbyła się rywalizacja na tej trasie
  UL dzien;
  UL miesiac;
  UL rok;
};
map<UL, Trasa> zawody; // lista zawodów, pary {nr,Trasa}
map<UL, map<UL, UL>> wyniki; // lista wyników, para {nr_trasy, {id_zwierzaka,punkty}}

int main() {
  setlocale(LC_ALL, ".UTF-8"); // pliki txt mają kodowanie UTF-8
  cout << "Odczytywanie listy z zawodnikami.\n";
  ifstream fzawodnicy("27_zawodnicy.txt");
  string temp;
  getline(fzawodnicy, temp); // ignoruję pierwszy wiersz z nagłówkami: id imie gatunek
  while (!fzawodnicy.eof()) {
    UL id;
    if (fzawodnicy >> temp) {
      zawodnicy.insert({ id = stoul(temp), {} });
      zawodnicy[id].id = id;
    }
    if (fzawodnicy >> temp) zawodnicy[id].imie = temp;
    if (fzawodnicy >> temp) zawodnicy[id].gatunek = temp;
  }
  fzawodnicy.close();

  wcout << L"Odczytywanie listy zawodów.\n";
  ifstream fzawody("27_zawody.txt");
  getline(fzawody, temp); // ignoruję nagłówki: nr data (dz.m.rok)
  while (!fzawody.eof()) {
    UL nr;
    if (fzawody >> temp) {      
      zawody.insert({ nr=stoul(temp), {} });
      zawody[nr].nr = nr;      
    }
    if (getline(fzawody, temp, '.')) zawody[nr].dzien = stoul(temp);
    if (getline(fzawody, temp, '.')) zawody[nr].miesiac = stoul(temp);
    if (fzawody>>temp) zawody[nr].rok = stoul(temp);
  }  
  fzawody.close();

  wcout << L"Odczytywanie wyników.\n";
  ifstream fwyniki("27_wyniki.txt");
  getline(fwyniki, temp); // ignoruję wiersz za nagłówkami: nr_trasy id_zwierza wynik
  while (!fwyniki.eof()) {
    UL nr, id, wynik;
    if (fwyniki >> temp) {
      nr = stoul(temp);
      if (wyniki.find(nr) == wyniki.end()) wyniki[nr] = {};
    }
    if (fwyniki >> temp) {
      id = stoul(temp);
      wyniki[nr][id] = 0;
    }
    if (fwyniki >> temp) {
      wynik = stoul(temp);
      wyniki[nr][id] = wynik;
    }
  }
  fwyniki.close();  
  wcout << L"Wszystkie dane z pliku załadowane.\n";

  // a) Podaj listę (id, imię i gatunek) zwierząt o trzech najlepszych wynikach punktowych. [2,] 
  /*
Punkty = 347
        10. Spidi żółw
Punkty = 343
        4. Groguś borsuk
Punkty = 330
        1. Brutus pies
        2. Misza owca
  */
  // (przy okazji zadania a) podliczę niezbędne rzeczy do zadania c)
  map<UL, UL> punkty; // id_zwierza => punkty razem
  map<UL, UL> punkty_plywanie; // punkty z zawodów parzystych
  for (auto& [nr, lista] : wyniki) {    
    for (auto& [id, wynik] : lista) {
      if (punkty.find(id) == punkty.end()) punkty[id] = 0;
      punkty[id] += wynik;
      if (nr % 2 == 0) {
        if (punkty_plywanie.find(id) == punkty_plywanie.end()) punkty_plywanie[id] = 0;
        punkty_plywanie[id] += wynik;
      }
    }    
  }
  wcout << L"Zdobyte punkty: " << endl;
  for (auto& [id, wynik] : punkty) {
    wcout << L"Zwierzę id=" << id << L" ";
    cout << zawodnicy[id].imie << " " << zawodnicy[id].gatunek;
    wcout << L" zdobyło " << wynik << L" punktów" << endl;
  }
  map<UL, vector<UL>> punkty_sort; // punkty => [id zwierząt]
  for (auto [id, wynik] : punkty) {
    punkty_sort[wynik].push_back(id);    
  }
  wcout << L"Lista trzech najlepszych wyników:\n";
  auto it = punkty_sort.rbegin();
  for (int i = 1; i <= 3; i++) { // trzy najlepsze wyniki
    cout << "Punkty = " << it->first << "\n";
    for (auto id : it->second) {
      cout << "\t" << id << ". " << zawodnicy[id].imie << " " << zawodnicy[id].gatunek << endl;

    }
    it++;
  }
  
  // b) Podaj zwycięzcę zawodów (lub zwycięzców w przypadku tej samej liczby punktów), 
  // wyświetlając id, imię i gatunek. Uwzględnij tylko wyniki zawodów, które 
  // odbyły się w wakacje (lipiec i sierpień) [1,].
 /*
Wakacyjne punkty = 86
        10. Spidi żółw
 */
  // szukam numerów zawodów, które odbyły się w wakacje
  set<UL> numery;
  for (auto& [nr, data] : zawody) {
    if (data.miesiac == 8 or data.miesiac == 7) {
      numery.insert(nr);
    }
  }
  wcout << L"Numery zawodów, które odbyły się w wakacje: \n";
  for (auto nr : numery) cout << nr << " ";
  cout << endl;
  map<UL, UL> punkty_wakacje; // id_zwierza => punkty razem
  for (auto& [nr, lista] : wyniki) {
    if (numery.find(nr) == numery.end()) continue;
    for (auto& [id, wynik] : lista) {
      if (punkty_wakacje.find(id) == punkty_wakacje.end()) punkty_wakacje[id] = 0;
      punkty_wakacje[id] += wynik;
    }
  }
  wcout << L"Wakacyjne zdobycze punktowe: " << endl;
  for (auto& [id, wynik] : punkty_wakacje) {
    wcout << L"Zwierzę id=" << id << L" ";
    cout << zawodnicy[id].imie << " " << zawodnicy[id].gatunek;
    wcout << L" zdobyło " << wynik << L" punktów" << endl;
  }
  map<UL, vector<UL>> punkty_wakacje_sort; // punkty => [id zwierząt]
  for (auto [id, wynik] : punkty_wakacje) {
    punkty_wakacje_sort[wynik].push_back(id);
  }

  wcout << L"Najlepszy wakacyjny wynik:\n";
  it = punkty_wakacje_sort.rbegin();
  cout << "Wakacyjne punkty = " << it->first << "\n";
  for (auto id : it->second) {
    cout << "\t" << id << ". " << zawodnicy[id].imie << " " << zawodnicy[id].gatunek << endl;
  }

  // c) Przyjmując, że zawody o parzystych numerach wymagały od zawodników umiejętności 
  // dobrego pływania, podaj listę (id, imię i gatunek) najgorszego pływaka. [1,] 
/*
Punkty = 140
        9. Gałka sowa
*/
  wcout << L"Zdobyte punkty zależne od umiejętności pływania: " << endl;
  for (auto& [id, wynik] : punkty_plywanie) {
    wcout << L"Zwierzę id=" << id << L" ";
    cout << zawodnicy[id].imie << " " << zawodnicy[id].gatunek;
    wcout << L" zdobyło " << wynik << L" punktów" << endl;
  }
  map<UL, vector<UL>> punkty_plywanie_sort; // punkty => [id zwierząt]
  for (auto [id, wynik] : punkty_plywanie) {
    punkty_plywanie_sort[wynik].push_back(id);
  }
  wcout << L"Najgorszy wynik w pływaniu:\n";
  auto iter = punkty_plywanie_sort.begin();  
  cout << "Punkty = " << iter->first << "\n";
  for (auto id : iter->second) {
    cout << "\t" << id << ". " << zawodnicy[id].imie << " " << zawodnicy[id].gatunek << endl;
  }

  // d) Uwzględniając tylko te zawody, które odbywały się w poniedziałki, 
  // podaj dane (id, imię i gatunek) najgorszego zawodnika. 1 stycznia 2022 to sobota. [2]
 /*
 Punkty = 27
        5. Kima kura
 */
  // wyznaczam poniedziałkowe zawody (ich numery), rok 2022 ma 365 dni.
  vector<pair<int,int>> poniedzialki_w_roku; // pary {dzień miesiąca, miesiąc} będące poniedziałkiem
  int start = 6; // sobota
  int d=1, m=1; // dzień miesiąca, miesiąc (1 stycznia)
  vector<int> miesiace = { 31,28,31,30,31,30,31,31,30,31,30,31 };
  for (int i = 1; i <= 365; i++) {    
    if (start == 1) {
      if (start == 1) poniedzialki_w_roku.push_back({ d,m });      
    }
    start = (start + 1 == 8) ? 1 : start + 1;
    miesiace[m - 1]--;
    d++;
    if (miesiace[m - 1] == 0) {
      m++;
      d = 1;
    }    
  }
  wcout << L"Poniedziałki w roku 2022: ";
  for (auto& dm : poniedzialki_w_roku) {
    cout << dm.first << "-" << dm.second << "  ";
  }
  // szukam numerów zawodów, które odbyły się w tych dniach
  set<UL> zawody_poniedzialkowe;
  for (auto& [nr, trasa] : zawody) {
    for (auto& dm : poniedzialki_w_roku) {
      if (trasa.dzien == dm.first and trasa.miesiac == dm.second) {
        zawody_poniedzialkowe.insert(nr);
        break;
      }
    }
  }
  wcout << L"\nNumery zawodów poniedziałkowych: ";
  for (auto nr : zawody_poniedzialkowe) cout << nr << " ";
  cout << endl;

  map<UL, UL> punkty_poniedzialki; // id_zwierza => punkty razem
  for (auto& [nr, lista] : wyniki) {
    if (zawody_poniedzialkowe.find(nr) == zawody_poniedzialkowe.end()) continue;
    for (auto& [id, wynik] : lista) {
      if (punkty_poniedzialki.find(id) == punkty_poniedzialki.end()) punkty_poniedzialki[id] = 0;
      punkty_poniedzialki[id] += wynik;
    }
  }
  wcout << L"Poniedziałkowe zdobycze punktowe: " << endl;
  for (auto& [id, wynik] : punkty_poniedzialki) {
    wcout << L"Zwierzę id=" << id << L" ";
    cout << zawodnicy[id].imie << " " << zawodnicy[id].gatunek;
    wcout << L" zdobyło " << wynik << L" punktów" << endl;
  }
  map<UL, vector<UL>> punkty_poniedzialki_sort; // punkty => [id zwierząt]
  for (auto [id, wynik] : punkty_poniedzialki) {
    punkty_poniedzialki_sort[wynik].push_back(id);
  }
  wcout << L"Najgorszy poniedziałkowy wynik:\n";
  iter = punkty_poniedzialki_sort.begin();
  cout << "Punkty = " << iter->first << "\n";
  for (auto id : iter->second) {
    cout << "\t" << id << ". " << zawodnicy[id].imie << " " << zawodnicy[id].gatunek << endl;
  }
}
