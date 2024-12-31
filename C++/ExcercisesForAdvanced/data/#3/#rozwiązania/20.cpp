/*
Stan kasy przed wydawaniem kwot: 4898 zł 5 gr
Do wydania=769 zł 50 gr  wydano:1x50 gr  2x2 zł  1x5 zł  3x20 zł  1x200 zł  1x500 zł
Do wydania=433 zł 11 gr  wydano:1x1 gr  1x10 gr  1x1 zł  1x2 zł  1x10 zł  1x20 zł  2x200 zł
Do wydania=950 zł  wydano:1x10 zł  2x20 zł  1x100 zł  4x200 zł
Do wydania=34 zł 12 gr  wydano:1x2 gr  1x10 gr  2x2 zł  1x10 zł  1x20 zł
Do wydania=57 zł 98 gr  wydano:1x1 gr  1x2 gr  1x5 gr  2x20 gr  1x50 gr  1x2 zł  1x5 zł  1x10 zł  2x20 zł
Do wydania=432 zł 78 gr  wydano:1x1 gr  1x2 gr  1x5 gr  1x20 gr  1x50 gr  1x2 zł  1x10 zł  1x20 zł  2x200 zł
Do wydania=99 zł 22 gr  wydano:1x2 gr  1x20 gr  2x2 zł  1x5 zł  1x10 zł  4x20 zł
Do wydania=11 zł 45 gr  wydano:1x5 gr  2x20 gr  1x1 zł  1x10 zł
Do wydania=30 zł 21 gr  wydano:1x1 gr  1x20 gr  1x10 zł  1x20 zł
Do wydania=450 zł 99 gr  wydano:2x2 gr  1x5 gr  2x20 gr  1x50 gr  1x10 zł  2x20 zł  2x200 zł

KWOTY 1644 zł 88 gr  nie udało się wydać.

Do wydania=3 zł 44 gr  wydano:2x2 gr  2x20 gr  1x1 zł  1x2 zł

W kasie pozostało: 1625 zł 25 gr
*/
#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
map<UL, UL> kasa = { // w groszach!
  {50000, 1}, {20000, 16}, {10000, 4}, {5000, 0},
  {2000, 23}, {1000, 11}, {500, 27}, {200, 12}, {100, 48},
  {50, 30}, {20, 14}, {10, 7}, {5, 28}, {2, 13}, {1, 89}
};
UL kasa_oblicz(map<UL, UL>& k) {
  UL ile = 0;
  for (auto& [nominal, sztuk] : k) {
    ile += nominal * sztuk;
  }
  return ile;
}
string opisz(UL kwota) {
  return ((kwota / 100) ? to_string(kwota / 100) + " zł " : "") +
    ((kwota % 100) ? to_string(kwota % 100) + " gr " : "");
}
bool Dowydania(UL kwota) {
  if (kwota > kasa_oblicz(kasa)) return false;
  map<UL, UL> wydane;
  UL pamiec = kwota;
  auto it = kasa.rbegin();
  while (kwota > 0 and it != kasa.rend()) {
    if (kwota >= it->first and it->second > 0) {
      kwota -= it->first;
      it->second--;
      if (wydane[it->first])
        wydane[it->first]++;
      else
        wydane[it->first] = 1;
    }
    else {
      it++;
    }
  }
  if (kasa_oblicz(wydane) == pamiec) {
    cout << "Do wydania=" << opisz(pamiec) << " wydano:";
    for (auto& [n, i] : wydane) {
      cout << i << "x" << opisz(n) << " ";
    }
    cout << endl;
    //cout << "W kasie zostało: " << kasa_oblicz(kasa) / 100. << endl << endl;
    return true;
  }
  for (auto& [nominal, ile] : wydane) {
    kasa[nominal] += ile;
  }
  return false;
}
int main() {
  setlocale(LC_ALL, "");
  cout << "Stan kasy przed wydawaniem kwot: " << opisz(kasa_oblicz(kasa)) << endl;
  vector<UL> kwoty = { 76950, 43311, 95000, 3412, 5798, 43278, 9922, 1145, 3021, 45099, 164488, 344 };
  for (auto k : kwoty) {
    if (!Dowydania(k)) {
      cout << "\nKWOTY " << opisz(k) << " nie udało się wydać.\n\n";
    }
  }
  cout << "\n\nW kasie pozostało: " << opisz(kasa_oblicz(kasa)) << endl;
}
