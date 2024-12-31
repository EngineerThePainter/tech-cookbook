#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
unsigned w = 54;
unsigned k = 177;
// zlicza, czy w obszarze wskazanym w zadaniu znak na pozycji wiersz/kolumna
// ma w otoczeniu przynajmniej 8 znaków #
int zlicz(vector<vector<char>>& znaki, unsigned wiersz, unsigned kolumna) {
  int wynik = 0;
  for (unsigned i = wiersz - 3; i <= wiersz + 3; i++) {
    for (unsigned j = kolumna - 3; j <= kolumna + 3; j++) {      
      if (znaki[i][j] == '#') {
        wynik++;        
      }
    }
  }  
  return wynik - 1; // nie liczę tego środkowego znaku #, dla którego badam obszar
}
int main() {
  setlocale(LC_ALL, "");  
  srand(time(0));
  vector<vector<char>> znaki;
  znaki.resize(w, {}); // 54 wiersze
  ifstream dane("34_znaki.txt");
  char znak;
  unsigned wiersz = 0;
  unsigned przeczytane = 0;
  while (!dane.eof()) {        
    if (dane >> znak) {
      przeczytane++;
      if (przeczytane <= k) {
        znaki[wiersz].push_back(znak);
      }
      if (przeczytane == k) {
        wiersz++;
        przeczytane = 0;
      }
    }
  }  
  int x=0;
  for (unsigned wiersz = 3; wiersz < w - 3; wiersz++) {
    for (unsigned kolumna = 3; kolumna < k - 3; kolumna++) {
      if (znaki[wiersz][kolumna] == '#') {
        x = zlicz(znaki, wiersz, kolumna);        
        if (x >= 4) {
          cout << "Istnieje obszar dla znaku # o pozycji wiersza "
            << wiersz+1 << " i kolumny " << kolumna+1 << " zawierający " << x << " #.\n";
        }
      }
    }
  }
  dane.close();
}
