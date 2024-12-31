#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////
class Dane {
public:
  int w;  
};
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  vector<int> k1;
  for (int i = 1; i <= 100; i++) k1.push_back(rand() % 100 + 1);
  // porządek malejący (greater): większa na przód!
  sort(k1.begin(), k1.end(), greater<int>()); // domyślnie: rosnący (less)
  // można też posortować tak, z użyciem iteratorów odwrotnych 
  // sort(k1.rbegin(), k1.rend());
  for (auto& e : k1) cout << e << " "; cout << endl; 

  vector<Dane> k2;  
  for (int sto=100;sto--;) k2.push_back({ rand() % 100 + 1 });
  // sortowanie zbioru k2 z funkcją anonimową zawierającą mechanizm sortujący
  sort(k2.begin(), k2.end(), [](auto& a, auto& b) { return (a.w > b.w); });
  for (auto& e : k2) cout << e.w << " "; cout << endl;
}
