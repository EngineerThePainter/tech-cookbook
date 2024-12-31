#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
const UL N = 22;
// const UL x = 3;
int main() {
  setlocale(LC_ALL, "");
  // rozwiązanie BEZ klas
  vector<UL> K;
  K.resize(N, 0);
  UL i = 1;
  for (auto& e : K) e = i++; // e reprezentuje kulkę i różny kolor równocześnie  
  /*
    Rozwiązanie bez tworzenia klas
  */
  vector<set<UL>> wszystkie3dlaK; // bo x = 3
  for (UL poz1 = 0; poz1 < K.size(); poz1++) {
    for (UL poz2 = poz1 + 1; poz2 < K.size(); poz2++) {
      for (UL poz3 = poz2 + 1; poz3 < K.size(); poz3++) {
        wszystkie3dlaK.push_back({ K[poz1], K[poz2], K[poz3] });
      }
    }
  }
  double wszystkie_zdarzenia = 0;
  double zdarzenia_z_powtorzonym_kolorem = 0;
  vector<set<UL>> wszystkie3dlaC(wszystkie3dlaK);
  for (auto k : wszystkie3dlaK) {
    for (auto c : wszystkie3dlaC) {
      auto a = k.size() + c.size(); // dla x=3 to 6 :)
      // włożę zbiór k do c 
      c.insert(k.begin(), k.end()); // zbiór set nie ma powtórzeń, więc...
      // ...gdy c.size() < 6, to jakiś kolor MUSIAŁ się powtórzyć!
      if (c.size() < a) zdarzenia_z_powtorzonym_kolorem += 1;
      wszystkie_zdarzenia += 1;
    }
  }
  cout.precision(15);
  cout << zdarzenia_z_powtorzonym_kolorem << endl;
  cout << fixed << wszystkie_zdarzenia << endl;
  cout << "Prawdopodobieństwo: " << zdarzenia_z_powtorzonym_kolorem / wszystkie_zdarzenia << endl;
  /*
    Korzystając ze wzoru na kombinację, można to było policzyć szybciej:
    możliwych trójek jest 22!/3!*(22-3)!, co daje 1540 kombinacji trzech kul.
    Ponieważ do worka mam wrzucić trzy dodatkowe kule z identycznego zbioru, ich też
    jest 1540, zatem wszystkich możliwych trójek kul z K i C w worku jest
    1540*1540. Spośród tych 2371600 przypadków sześciu kul trzeba wyłapać te,
    wśród których przynajmniej jedna para ma ten sam kolor.
    Uwaga! Czy jednak komputer policzyłby 22 silnia? (22!)
  */
}
