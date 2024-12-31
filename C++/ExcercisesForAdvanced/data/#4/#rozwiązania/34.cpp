#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
//////////////////////////////////////////////////////
typedef long long int L;
class Kwadrat {
public:
  L x;
  L y;
  L d;
  Kwadrat(L ustawx, L ustawy, L ustawd) : x(ustawx), y(ustawy), d(ustawd) { }
  // przeciążę operator ==, który zinterpretuję jako pytanie: 
  // "Czy istnieje część wspólna o powierzchni niezerowej?"
  // (przyjmuję, że kwadraty styczne nie mają części wspólnej, gdyż pole krawędzi wspólnych
  // zmierza do zera)
  bool operator==(Kwadrat& k) {
    L k1x1 = x, k1y1 = y, k1x2 = x + d, k1y2 = y - d;
    L k2x1 = k.x, k2y1 = k.y, k2x2 = k.x + k.d, k2y2 = k.y - k.d;
    if (k1x1 >= k2x2 or k2x1 >= k1x2) return false;
    if (k1y2 >= k2y1 or k2y2 >= k1y1) return false;
    return true;
  }
};
int main() {
  setlocale(LC_ALL, "");  
  // Pomysł oprę na sprawdzaniu, czy kolejne pola 1 na 1 w obrębie badanej płaszczyzny
  // są przykryte kwadratami. Jeżeli pole przykrywa tylko jeden kwadrat: będzie częścią rozwiązania.
  // W każdym innym przypadku przeciwnie.  
  vector<Kwadrat> wszystko;
  ifstream plik("34_kwadraty.txt");
  L x, y, bok;
  while (plik >> x >> y >> bok) {
    wszystko.push_back({ x,y,bok });
  }
  plik.close();
  // Określam przybliżony zasięg badanej płaszczyzny (lewy górny, prawy dolny wierzchołek)
  L minx = 0, maxx = wszystko[0].x, miny = 0, maxy = wszystko[0].y;
  for (Kwadrat& k : wszystko) {
    if (minx > k.x) minx = k.x;
    if (miny > k.y) miny = k.y;
    if (maxx < k.x) maxx = k.x;
    if (maxy < k.y) maxy = k.y;
  }
  // lewy górny to minx, maxy
  // prawy dolny to maxx+3, miny-3
  map<pair<L, L>, L> ile_razy;  
  for (auto powx = minx; powx <= maxx + 3; powx++) {
    for (auto powy = maxy; powy >= miny - 3; powy--) {
      auto K = Kwadrat(powx, powy, 1);
      for (Kwadrat& k : wszystko) {
        if (K == k) {          
          ile_razy[{powx, powy}]++;
        }
      }
    }
  }
  L odp = 0;
  for (auto& [punkt, ile] : ile_razy) {
    if (ile == 1) odp++;
  }
  cout << "Pole powierzchni = " << odp++;
}
