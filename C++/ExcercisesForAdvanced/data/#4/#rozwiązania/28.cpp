#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("28_gustaw.txt");
  vector<UL> spisy;
  UL spis, ile=0;
  while (plik >> spis) spisy.push_back(spis);
  plik.close();
  cout << "Wpisów w pliku = " << spisy.size() << endl;

  auto poz = spisy.size()-1;
  for (; poz >= 1; poz--) {        
    if (spisy[poz] - 50 < spisy[poz - 1]) break;    
  }
  cout << "\n\nOd dnia " << poz+2 << 
    " każdy wzrost względem dnia poprzedniego przekraczał 50 wyświetleń." << endl;
    
  for (poz = 0; poz < spisy.size()-2; poz++) {    
    if (spisy[poz + 2] - spisy[poz + 1] < spisy[poz + 1] - spisy[poz]) ile++;    
  }
  cout << "\n\nDni, w których wzrost był mniejszy niż wzrost dzień wcześniej = " << ile << endl;
}
