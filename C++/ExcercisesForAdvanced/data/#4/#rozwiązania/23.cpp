#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class Prostopadloscian {
public:
  UL a;
  UL b;
  UL c;
  Prostopadloscian(vector<UL> v) : a(v[0]), b(v[1]), c(v[2]) {}
  UL objetosc() { return a * b * c; }
  UL polePodstawy() { return a * b; }
  bool operator<(Prostopadloscian& p) {
    if (objetosc() < p.objetosc()) return true;
    else if (objetosc() > p.objetosc()) return false;
    if (c < p.c) return true;
    else if (c > p.c) return false;
    if (polePodstawy() < p.polePodstawy()) return true;
    else if (polePodstawy() > p.polePodstawy()) return false;
  }
  bool operator==(Prostopadloscian& p) {
    return (objetosc() == p.objetosc() and c == p.c and polePodstawy() == p.polePodstawy());
  }
  bool operator>(Prostopadloscian& p) {
    return !(*this < p or *this == p);
  }
  bool operator>=(Prostopadloscian& p) {
    return !(*this < p);
  }
  bool operator<=(Prostopadloscian& p) {
    return (*this == p or *this < p);
  }
  static void swap(vector<Prostopadloscian>& V, int a, int b) {
    auto pomoc = V[a];
    V[a] = V[b];
    V[b] = pomoc;
  }
  static void quicksort(vector<Prostopadloscian>& V, int lewy, int prawy) {
    if (prawy <= lewy) return; // warunek stopu rekurencji
    auto pivot = V[lewy];
    int z_lewa = lewy + 1;
    int pozycja = lewy + 1;
    while (z_lewa <= prawy) {
      if (pivot >= V[z_lewa]) {
        // zamiana miejscami
        swap(V, z_lewa, pozycja);
        pozycja++;
      }
      z_lewa++;
    }
    swap(V, lewy, pozycja - 1);
    quicksort(V, lewy, pozycja - 2);
    quicksort(V, pozycja, prawy);
  }
  void info() {
    cout << a << "," << b << "," << c
      << " Objętość=" << objetosc() << " PolePods=" << polePodstawy() << " Wysokość=" << c << endl;
  }
};

int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  vector<Prostopadloscian> V;
  for (int i = 1; i <= 100; i++)
    V.push_back(Prostopadloscian({ UL(rand() % 100 + 1), UL(rand() % 100 + 1) ,UL(rand() % 100 + 1) }));
  Prostopadloscian::quicksort(V, 0, V.size() - 1);
  for (auto& e : V) e.info();
}
