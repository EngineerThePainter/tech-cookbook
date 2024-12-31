#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <string>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
int main() {
  setlocale(LC_ALL, "");  
  ifstream plik("13.bin");     
  string temp;
  vector<unsigned> sumy;
  vector<string> wiersze;
  while (getline(plik,temp)) {
    unsigned suma = 0;
    cout << temp << ":\n";
    wiersze.push_back(temp);
    for (auto& znak : temp) { // ciąg 8 bitów
      string bity = bitset<8>(znak).to_string();
      cout << "'" << znak << "'" << "{";
      for (int poz = 0; poz <=6; poz+=2) {
        cout << bitset<2>(bity,poz,2).to_string() << "=" 
          << bitset<2>(bity, poz, 2).to_ulong()<<" ";
        suma += bitset<2>(bity, poz, 2).to_ulong();
      }
      cout << "}  ";
    }
    cout << endl;    
    sumy.push_back(suma);
  }
  plik.close();
  for (int p = 0; p < wiersze.size(); p++) {
    cout << wiersze[p] << " = " << sumy[p] << endl;
  }
}
