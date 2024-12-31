#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("11_dane.txt");
  string temp;
  map<string, UL> ilosci;
  while (!plik.eof()) {
    if (plik >> temp) {
      if (ilosci.count(temp) == 0) ilosci[temp] = 0;
      ilosci[temp]++;
    }
  }
  plik.close();
  UL mini = ilosci.size();
  for (auto& [slowo, ilosc] : ilosci) {
    cout << slowo << "=" << ilosc << endl;
    if (ilosc < mini) mini = ilosc;
  }
  cout << "\nSłowa o najmniejszej liczbie wystąpień (" << mini << "):\n";
  for (auto& [slowo, ilosc] : ilosci) {
    if (ilosc == mini) cout << slowo << "\n";
  }
}
