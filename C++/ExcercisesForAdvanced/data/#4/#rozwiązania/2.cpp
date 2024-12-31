#include <iostream>
#include <ctime>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////
class Dane {
public:
  int w;
};
void show(list<Dane>& l) {
  cout << endl;
  for (auto& e : l) cout << e.w << " ";
  cout << endl;
}
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  list<Dane> k;
  for (int sto = 100; sto--;) k.push_back({ rand() % 100 + 1 });
  show(k);
  // 1.
  k.sort([](auto& a, auto& b) {
    return (a.w % 2 == 0 and b.w % 2 == 1);
    }
  );
  show(k);
  // 2.
  k.sort([](auto& a, auto& b) {
    // parzyste-nieparzyste
    if (a.w % 2 == 0 and b.w & 1) return true;
    // porządek parzystych
    if (a.w % 2 == 0 and b.w % 2 == 0 and a.w > b.w) return true;
    // porządek nieparzystych
    if (a.w & 1 and b.w & 1 and a.w < b.w) return true;
    return false; // pozostały porządek
    });
  show(k);
  // 3.
  auto pierwsza = [](int n) {
    for (int i = 2; i <= sqrt(n); i++) if (n % i == 0) return false;
    return true;
  };
  k.sort([pierwsza](auto& a, auto& b) {
    return (pierwsza(a.w) and !pierwsza(b.w));
    });
  show(k);
}
