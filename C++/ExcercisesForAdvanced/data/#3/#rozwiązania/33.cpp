#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
unsigned ile_wierszy = 0;
unsigned ile_kolumn = 0;
// użycie: get("wiersz",1) -> pierwszy wiersz 
// użycie: get("kolumna,5) -> piąta kolumna 
vector<char> get(vector<char>& z, string typ, unsigned nr) {
  if (nr == 0) return {}; // wiersz i kolumnę liczymy od 1
  vector<char> fragment;
  if (typ == "wiersz") {
    if (nr > ile_wierszy) return {}; // za duży numer
    for (unsigned poz = (nr - 1) * ile_kolumn; 
      poz <= (nr-1) * ile_kolumn + ile_kolumn -1; poz++) {
      fragment.push_back(z[poz]);
    }
  }
  else  { // kolumna
    if (nr > ile_kolumn) return {}; // za duży numer
    for (unsigned poz = nr - 1, step = 1; 
      step <= ile_wierszy; poz += ile_kolumn,step++) {
      fragment.push_back(z[poz]);
    }
  }
  return fragment;
}
bool dwie_identyczne(vector<char> v1, vector<char> v2) {
  return (string(v1.begin(), v1.end()) == string(v2.begin(), v2.end()));  
}
bool dwie_podobne(vector<char> v1, vector<char> v2) {
  if (dwie_identyczne(v1, v2)) return false;
  for (auto z : v1) {    
    for (int poz = 0; poz < v2.size(); poz++) {
      if (z == v2[poz]) {
        v2.erase(v2.begin() + poz);
        break;
      }
    }
  }
  return (!v2.size());
}

int main() {
  setlocale(LC_ALL, "");  
  srand(time(0));
  vector<char> znaki;
  ifstream dane("33_litery.txt");  
  string temp;
  getline(dane, temp);
  ile_kolumn = temp.size();
  dane.close();
  dane.open("33_litery.txt");

  while (!dane.eof()) {
    char znak='#';
    if (dane >> znak) {      
      znaki.push_back(znak);
    }    
  }
  ile_wierszy = znaki.size() / ile_kolumn;
  cout << "W pliku wykryto " << ile_kolumn << " liter w wierszu.\n";
  cout << "W pliku wykryto " << ile_wierszy << " wierszy.\n";
  
  // test i przykładowe wykorzystanie funkcji get()
  for (auto znak : get(znaki, "wiersz", 5)) cout << znak;
  cout << endl;
  for (auto znak : get(znaki, "kolumna", 5)) cout << znak;
  cout << endl;

  // rozwiązania:
  // Czy istnieją dwie identyczne kolumny? (takie same znaki na odpowiednich pozycjach)
  bool dik= false;
  for (unsigned kol1 = 1; kol1 <= ile_kolumn; kol1++) {
    for (unsigned kol2 = 1; kol2 <= ile_kolumn; kol2++) {
      if (kol1 == kol2) continue;
      if (dwie_identyczne(
        get(znaki, "kolumna", kol1), get(znaki, "kolumna", kol2))) {
        cout << "Identyczna jest kolumna " << kol1 << " i kolumna " << kol2 << endl;
        dik = true;
        break;
      }
    }
    if (dik) break;
  }
  if (dik) cout << "Istnieją dwie identyczne kolumny!\n";  
  // Czy istnieją dwa identyczne wiersze? (takie same znaki na odpowiednich pozycjach)
  bool diw = false;
  for (unsigned wiersz1 = 1; wiersz1 <= ile_wierszy; wiersz1++) {
    for (unsigned wiersz2 = 1; wiersz2 <= ile_wierszy; wiersz2++) {
      if (wiersz1 == wiersz2) continue;
      if (dwie_identyczne(
        get(znaki, "wiersz", wiersz1), get(znaki, "wiersz", wiersz2))) {
        cout << "Identyczny jest wiersz " << wiersz1 << " i wiersz " << wiersz2 << endl;
        diw = true;
        break;
      }      
    }
    if (diw) break;
  }
  if (diw) cout << "Istnieją dwa identyczne wiersze!\n";

  // Czy istnieją dwie kolumny składające się z tych samych znaków i 
  // takiej samej liczby wystąpień każdego znaku, 
  // bez zachowania zgodności na odpowiednich pozycjach (nie mogą być identyczne)?
  bool dpk = false;
  for (unsigned kol1 = 1; kol1 <= ile_kolumn; kol1++) {
    for (unsigned kol2 = 1; kol2 <= ile_kolumn; kol2++) {
      if (kol1 == kol2) continue;
      if (dwie_podobne(
        get(znaki, "kolumna", kol1), get(znaki, "kolumna", kol2))) {
        cout << "Podobna jest kolumna " << kol1 << " i kolumna " << kol2 << endl;
        dpk = true;
        break;
      }
    }
    if (dpk) break;
  }
  if (dpk) cout << "Istnieją dwie podobne kolumny!\n";
  dane.close();  
}
