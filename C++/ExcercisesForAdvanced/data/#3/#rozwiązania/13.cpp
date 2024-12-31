#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
// test: czy a i b są względnie pierwsze?
bool wp(L a, L b) {
if (a > b) {
    L temp = b;
    b = a;
    a = temp;
  }
  for (L dzielnik = 2; dzielnik <= a; dzielnik++) {
    if (a % dzielnik == 0 and b % dzielnik == 0) return false;
  }
  return true;
}

vector<pair<L, L>> pary_wp(set<L> zb) {
  vector<pair<L, L>> wynik;
  while (zb.size()) {
    auto x = *zb.begin();
    zb.erase(x);
    for (auto it = zb.begin(); it != zb.end(); it++) {
      if (wp(x, *it)) wynik.push_back({ x,*it });
    }
  }
  return wynik;
}
int main() {
  setlocale(LC_ALL, "");
  set<L> zb = { 2,6,7,8,9 };
  for (auto e : pary_wp(zb)) cout << e.first << " " << e.second << endl;
} 
