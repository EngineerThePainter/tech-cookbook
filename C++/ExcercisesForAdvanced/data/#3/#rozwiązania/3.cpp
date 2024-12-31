#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <bitset>
#include <map>
#include <list>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
bool test3c(string b1, string b2) {
  int takie_same = 0;
  for (size_t poz = 0; poz < b1.size(); poz++)
    if (b1[poz] == b2[poz]) {
      takie_same++;
    }
  return takie_same >= 5;
}
int main() {
  srand(time(0));
  setlocale(LC_ALL, "");
  ifstream p("3_dane.txt");
  vector<bitset<8>> dane;
  string temp;
  // ładuję dane z pliku do wektora z 8-bitowymi liczbami
  while (p >> temp) {
    dane.push_back(stoi(temp.substr(0, 8), nullptr, 2));
  }
  // 3a)  ODP.: 479
  int ile_przez_8 = 0;
  for (bitset<8> b : dane)
    ile_przez_8 += (b << 5 == 0); // zwiększam licznik, gdy liczba podzielna jest przez 8    
  cout << "Podzielnych przez 8 jest " << ile_przez_8 << endl;

  // 3b) ODP.: 01010100 84 (27 razy)
  vector<unsigned> zliczanie;
  zliczanie.resize(256, 0); // zliczy każdą z liczb od 00000000 do 11111111  (0-255)
  for (auto b : dane) zliczanie[b.to_ulong()]++; // zliczam
  multimap<UL, bitset<8>> posortowane; // pary {ilość, liczba_bitowa}
  for (unsigned bit = 0; bit < zliczanie.size(); bit++)
    posortowane.insert({zliczanie[bit],bitset<8>(bit)}); // {ilość, liczba_bitowa}
  auto odp = posortowane.rbegin(); // ilość ostatniej pary jest największą ilością 
  cout << "Największa ilość: "
    << odp->second << " " << odp->second.to_ulong() << " (" << odp->first << " razy)\n";
  p.close();
  // 3c) ODP.: 8  
  p.open("3_dane.txt");
  list<string> bity; // lista pozwala efektywnie usuwać jej zawartość ze środka  
  while (p >> temp) {
    bity.push_back(temp.substr(0, 8));
  }
  p.close();
  cout << "\nLiczb na liście jest: " << bity.size() << endl;
  auto it = bity.begin();
  while (it != bity.end()) {
    auto check = it;
    ++check;
    while (check != bity.end()) {
      if (test3c(*it, *check)) check = bity.erase(check);
      else ++check;
    }
    ++it;
  }
  cout << "\nPozostało " << bity.size() << " liczb.\n";
  for (auto i = bity.begin(); i != bity.end(); ++i) {
    cout << *i << endl;
  }
}
