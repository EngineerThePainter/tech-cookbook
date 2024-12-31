#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <ctime>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
const string blue("\033[94m"); // niebieski
const string reset("\033[0m"); // RESET koloru
const string dark("\033[7m"); // inverse
UL szerokosc() { // losowa szerokość od 1 do 3
  return rand() % 3 + 1;
}
int main() {
  setlocale(LC_ALL, ""); 
  srand(time(0));
  ofstream fmapa("mapa.txt");

  map<pair<UL, UL>, string> mapa; // { {x,y}, znak_terenu }
  // x=1, y=1 uznajemy za lewy górny róg mapy
  UL x = 50; // rozmiar mapy - kolumny
  UL y = 20; // rozmiar mapy - wiersze    

  for (UL i = 1; i <= y; i++) {
    for (UL j = 1; j <= x; j++) {
      if (i == 1 or j == 1 or i == y or j == x) mapa.insert({ {j, i}, "#" }); // krawędzie
      else { // umieszczam losowo pola i równiny w proporcji około 3:1
        if (rand() % 100 + 1 <= 75) mapa.insert({ {j,i}," "});
        else mapa.insert({ {j,i}, "*"});
      }      
    }
  }
  // generuję rzekę, która nadpisuje wyżyny i niziny
  // gdzie wypływa (zachodnia krawędź gór)
  UL x_start = 2; // rzeka od drugiej do x-1 kolumny
  UL y_start = rand() % (y - 2) + 2; // 2-49
  UL mod = 0; // czynnik losowości skręcający rzekę
  while (x_start <= x - 1) {
    UL mod_szansa = rand() % 100 + 1;
    if ( mod_szansa < 34) mod++;
    else if (mod_szansa < 67) mod--;
    UL sz = szerokosc();
    for (int i = 0; i < sz; i++) {
      if (y_start + i + mod <= y - 1 and y_start + i + mod > 1)
        mapa[{x_start, y_start + i + mod}] = "=";
      else i--;
    }
    x_start++;
  }

  for (UL i = 1; i <= y; i++) {
    for (UL j = 1; j <= x; j++) {      
      fmapa << mapa[{j, i}];
      if (mapa[{j, i}] == "=")
        cout << dark << blue << mapa[{j, i}] << reset;
      else cout << dark << mapa[{j, i}] << reset;
    }
    fmapa << endl;
    cout << endl;

  }
  
  fmapa.close();
}
