#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
bool czyPierwsza(unsigned n) {
  if (n < 2) return false;
  for (unsigned i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) return false;
  }
  return true;
}
unsigned dobryKwadrat(vector<vector<int>>& dane, int n, int x, int y) {
  unsigned suma = 0;
  for (int i = x; i < x + n; i++) {
    for (int j = y; j < y + n; j++) {
      suma += dane[i][j];
    }
  }
  if (czyPierwsza(suma)) return suma;
  return 0;
}
int main() {
  setlocale(LC_ALL, "");
  ifstream pdane("32_cyfry.txt");
  char pomocnicza;
  vector<vector<int>> dane;
  dane.resize(25, {});
  // czytam dane (25x25 cyfr)
  for (auto& v : dane) {
    int wiersz = 25;
    while (wiersz--) {
      pdane >> pomocnicza;
      v.push_back(pomocnicza - 48);
    }
  }
  // obliczenia
  unsigned ile_kwadratow = 0;
  unsigned wszystkie_mozliwe_kwadraty = 0;
  map<unsigned, unsigned> ile_pierwszych; // { liczba pierwsza, ilość kwadratów }
  for (int n = 2; n <= 25; n++) {
    for (int x = 0; x < 25; x++) {
      if (n + x - 1 >= 25) break;
      for (int y = 0; y < 25; y++) {
        if (n + y - 1 >= 25) break;
        wszystkie_mozliwe_kwadraty++;
        unsigned suma = dobryKwadrat(dane, n, x, y);
        if (suma > 0) {
          ile_kwadratow++;
          cout << "Kwadrat o boku " << n << " utworzył liczbę pierwszą : " <<
            suma << ". Pozycja wiersz,kolumna = (" << x + 1 << ", " << y + 1 << ")\n";
          // można pominąć poniższą linię, ale zostawiam dla czytelności zliczania
          if (!ile_pierwszych[suma]) ile_pierwszych[suma] = 0;
          ile_pierwszych[suma]++;
        }
      }
    }
  }
  cout << "Wszystkich kwadratów w zbiorze K jest " << ile_kwadratow << endl;
  cout << "Wszystkich możliwych kwadratów jest " << wszystkie_mozliwe_kwadraty << endl;

  cout << "Liczby pierwsze: ";
  for (auto& [p, s] : ile_pierwszych) {
    cout << p << " ";
  }
  cout << endl;

  for (auto& [p, s] : ile_pierwszych) {
    cout << "Liczba pierwsza " << p << " jest w " << s << " kwadratach.\n";
  }

  pdane.close();
}
