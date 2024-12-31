#include <iostream>
#include <ctime>
#include <string>
#include <list>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
const string reset("\033[0m"); // RESET koloru
const string blade("\033[107m"); // szare na białym
struct kuleczka {
  string kolor;
  UL numer;
};
void pokaz(list<kuleczka>& o, UL max) {
  auto it = o.begin();
  for (UL i = 1; i <= max; i++) {
    if (it != o.end() and it->numer == i) {
      cout << it->kolor[0] << it->numer << " ";
      if (it != o.end()) it++;
    }
    else cout << blade << " " << i << " " << reset;
  }
  cout << endl << endl;
}
int main() {
  setlocale(LC_ALL, "");
  int krok = 5;
  list<kuleczka> okrag;
  for (int i = 7; i--;) okrag.push_back(kuleczka{ "czerwona",okrag.size() + 1 });
  for (int i = 9; i--;) okrag.push_back({ "biała",okrag.size() + 1 });
  for (int i = 14; i--;) okrag.push_back({ "czarna",okrag.size() + 1 });
  UL ilosc = okrag.size();
  auto it = okrag.begin();
  while (okrag.size() > 1) {
    int odlicz = krok - 1;
    while (odlicz--) { // przesuwam się                    
      it++;
      if (it == okrag.end()) it = okrag.begin(); // cykl, bo to jest okrąg            
    }
    pokaz(okrag, ilosc);
    it = okrag.erase(it);
    if (it == okrag.end()) it = okrag.begin(); // gwarancja cyklu okręgu
  }

  pokaz(okrag, ilosc); // ostatnia, która została

  cout << "ODPOWIEDŹ: " << okrag.front().kolor <<
    " nr=" << okrag.front().numer << endl; // ostatnia
}
