#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
const string reset("\033[0m"); // reset koloru
const string green("\033[92m"); // zielony
const string red("\033[91m"); // czerwony
//////////////////////////////////////////////////////
struct Element {
  vector<float> oceny;
};
// średnia arytmetyczna
float sa(vector<float>& v) {
  float sr = 0;
  for (auto e : v) sr += e;
  return sr / v.size();
}
// zamiana miejscami elementów w wektorze vector<Element> dla pozycji
// i oraz i+1
void _swap(vector<Element>& v, size_t i) {
  if (i < v.size() - 1) { // sprawdzam, czy elementy na pozycjach istnieją
    Element temp = v[i];
    v[i] = v[i + 1];
    v[i + 1] = temp;
  }
}
// ładna prezentacja elementów wektora
void pokaz(vector<Element>& L, string color) {
  for (auto& e : L) {
    cout << color << sa(e.oceny) << reset;
    cout << "{";
    for (int i = 0; i < e.oceny.size(); i++) {
      cout << e.oceny[i];
      if (i < e.oceny.size() - 1) cout << ",";
    }
    cout << "}\n";
  }
  cout << endl;
}

bool operator==(Element& e1, Element& e2) {
  return (abs(sa(e1.oceny) - sa(e2.oceny)) <= 0.5);
}
bool operator>(Element& e1, Element& e2) {
  return (sa(e1.oceny) > sa(e2.oceny) and (sa(e1.oceny)-sa(e2.oceny) > 0.5));
}
bool operator<(Element& e1, Element& e2) {
  return (sa(e1.oceny) < sa(e2.oceny) and (sa(e2.oceny) - sa(e1.oceny) > 0.5));
}
void babelLT(vector<Element>& L) { // porządek rosnący
  for (size_t i = L.size() - 1; i >= 1; i--) {
    for (size_t j = 0; j < i; j++) {
      if (L[j] > L[j + 1]) _swap(L, j);
    }
  }
}
int main() {
  setlocale(LC_ALL, "");
  vector<Element> L = { {{1,1,2,3,6}}, {{1,.5,.9,3.5,2,6}}, {{ 8,11,3,4,0.1,3,2,0.01 }},
    {{ 3,6,4,1,3.5,22 }}, {{ 1,1,2,3,6 }}, {{1,.5,.9,3.5,2,3,9,6,8,4}},
    {{1}},{{0.5,0.5,0.2}}, {{-2,-5,1,-0.5} } };
  pokaz(L, red);
  babelLT(L);
  pokaz(L, green);
}
