#include <iostream>
#include <set>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
UL suma_dzielnikow(UL n) {
  UL s = 1;
  for (UL dzielnik = 2; dzielnik <= n / 2 + 1; dzielnik++) {
    if (n % dzielnik == 0) s += dzielnik;
  }
  return s;
}
int main() {
  setlocale(LC_ALL, "");
  set<UL> doskonale;
  // nie sprawdzam 1-ki, nie jest doskonała
  for (UL kandydaci = 2; kandydaci <= 10000; kandydaci++) {
    if (kandydaci == suma_dzielnikow(kandydaci)) {
      doskonale.insert(kandydaci);
    }
  }
  for (auto doskonala : doskonale) cout << doskonala << " ";
}
