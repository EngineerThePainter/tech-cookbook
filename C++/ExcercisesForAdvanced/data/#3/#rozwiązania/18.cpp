#include <iostream>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
bool lustrzane(UL n1, UL n2) {
  string sn1 = to_string(n1);
  string sn1_rev = string(sn1.rbegin(), sn1.rend());
  return (stoul(sn1_rev) == n2);
}
int main() {
  setlocale(LC_ALL, "");
  UL ile(0);
  for (UL i = 2; i <= 999; i++) {
    for (UL j = i + 1; j <= 1000; j++) {
      if (lustrzane(i, j)) {
        cout << i << ":" << j << endl;
        ile++;
      }
    }
  }
  cout << "\n\nLiczba: " << ile << endl;
}
