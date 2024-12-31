#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
vector<pair<UL, UL>> bli(UL N) {
  vector<UL> sito;
  vector<UL> pierwsze;
  vector<pair<UL, UL>> wynik;
  sito.resize(N + 1, 0);
  for (UL i = 2; i < sito.size(); i++) sito[i] = i;
  for (UL i = 2; i < sito.size(); i++) {
    if (sito[i] == 0) continue;
    pierwsze.push_back(i);
    for (UL skreslam = i + i; skreslam < sito.size(); skreslam += i) sito[skreslam] = 0;
  }
  for (size_t i = 0; i < pierwsze.size() - 1; i++) {
    if (pierwsze[i] + 2 == pierwsze[i + 1]) {
      wynik.push_back({ pierwsze[i],pierwsze[i + 1] });
    }
  }
  return wynik;
}
int main() {
  setlocale(LC_ALL, "");
  auto v = bli(1000);
  cout << "Znalazłem " << v.size() << " par bliźniaczych!\n";

  for (auto& [p1, p2] : v) {
    cout << p1 << " " << p2 << endl;
  }
}
