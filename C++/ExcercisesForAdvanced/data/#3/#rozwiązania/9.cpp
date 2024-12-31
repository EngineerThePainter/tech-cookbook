#include <iostream>
#include <vector>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct Element {
  int dane = 0;
  bool priorytet = false;
};
bool operator>(Element& a, Element& b) {
  return ((a.priorytet and !b.priorytet)
    or (a.priorytet == b.priorytet and a.dane > b.dane));
}
bool operator==(Element& a, Element& b) {
  return (a.priorytet == b.priorytet and a.dane == b.dane);
}
bool operator>=(Element& a, Element& b) {
  return ((a > b) or (a == b));
}
// dodatkowo: pozostałe operatory mogłyby być zdefiniowane następująco
bool operator<(Element& a, Element& b) { return !(a >= b); }
bool operator<=(Element& a, Element& b) { return !(a > b); }
bool operator!=(Element& a, Element& b) { return !(a == b); }

void swap(vector<Element>& v, int a, int b) {
  Element temp = v[a];
  v[a].dane = v[b].dane;
  v[a].priorytet = v[b].priorytet;
  v[b] = temp;
}
void mergesort(vector<Element>& v, int lewy, int prawy) {
  if (lewy >= prawy) return;
  vector<Element> temp = v;
  int q = (lewy + prawy) / 2;
  mergesort(temp, lewy, q);
  mergesort(temp, q + 1, prawy);
  int poz = lewy;
  int lkrok = lewy, pkrok = q + 1;
  while (lkrok <= q and pkrok <= prawy) {
    if (temp[lkrok] <= temp[pkrok]) {
      v[poz++] = temp[lkrok++];
    }
    else {
      v[poz++] = temp[pkrok++];
    }
  }
  while (lkrok <= q) v[poz++] = temp[lkrok++];
  while (pkrok <= prawy) v[poz++] = temp[pkrok++];
}
int main() {
  setlocale(LC_ALL, "");
  vector<Element> V = { {10,true},{-5,false},{1,true},{50,false},{0,false},{0,true},{33,false},
    {-5,true},{-5,true},{12,false},{-6,false},{-7,true},{44,false},{1,true},{20,false},
    {17,false}, {19,false},{33,true},{-22,true} };

  mergesort(V, 0, V.size() - 1);
  for (auto& [d, p] : V) cout << "{" << d << "," << ((p) ? "true" : "false") << "},";
}
