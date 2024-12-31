#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("21_liczby.txt");  
  string wszystko,pomoc;
  while (plik >> pomoc) {
    wszystko += pomoc;
  }  
  plik.close();
  map<string, UL> zliczacz;
  for (size_t poz = 0; poz <= wszystko.size() - 6; poz++) {
    zliczacz[wszystko.substr(poz, 6)]++;    
  }
  vector<pair<string, UL>> doPosortowania(zliczacz.begin(), zliczacz.end());
  ranges::sort(doPosortowania,
    [](auto& a, auto& b) {
      return (a.second > b.second);
    });
  UL maks = doPosortowania[0].second;
  for (auto& [ciag, ile] : doPosortowania) {
    if (ile != maks) break;
    cout << "Podciąg " << ciag << " = " << ile << " razy" << endl;
    
  }
}
