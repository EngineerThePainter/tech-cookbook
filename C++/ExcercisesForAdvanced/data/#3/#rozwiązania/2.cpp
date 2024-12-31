#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <map>
#include <algorithm>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
int main() {
  srand(time(0)); setlocale(LC_ALL, "");
  ifstream plik;
  plik.open("2_dane.txt");
  string temp;
  string a, b, c;
  L osoba;
  stringstream ss;
  map<L, array<double, 3>> wyniki; // tu włożę przeczytany plik
  getline(plik, temp); // ignoruję pierwszy wiersz z nagłówkami A B C id_osoby
  while (getline(plik, temp)) {    
    ss.clear();
    ss.str(temp);    
    ss >> a >> b >> c >> osoba;    
    wyniki[osoba][0] = stod(a);    
    wyniki[osoba][1] = stod(b);    
    wyniki[osoba][2] = stod(c);    
  }
  plik.close();
  cout << "Odczytano dane dla " << wyniki.size() << " osób\n";
  // posiadam wyniki, korzystam z obliczeń
  // a) Ile osób przynajmniej w jednym teście uzyskało wynik poniżej 10.00%?
  // b) Ile osób osiągnęło takie wyniki testów, że różnica pomiędzy dwoma dowolnymi z nich nigdy nie przekracza 2.00%?
  int ile_a = 0;
  int ile_b = 0;
  for (auto [o, w] : wyniki) {
    if (w[0] < 10.0 or w[1] < 10.0 or w[2] < 10.0) 
      ile_a++;
    if (abs(w[0] - w[1]) < 2.0 and abs(w[0] - w[2]) < 2.0 and abs(w[1] - w[2]) < 2.0)       
      ile_b++;    
  }
  cout << "#3.2.a) Osób = " << ile_a << endl;
  cout << "#3.2.b) Osób = " << ile_b << endl;
  // c) Podaj identyfikator id_osoby osób, które osiągnęły trzy najwyższe średnie procentowe (średni procent oblicz jako średnia arytmetyczna ze wszystkich trzech testów danej osoby).
  // korzystam z własności multimapy/mapy, która sortuje klucze :) (liczbowe sortuje rosnąco)
  multimap<double, L> srednie;
  for (auto& [o, w] : wyniki)
    srednie.insert({ (w[0] + w[1] + w[2]) / 3.0, o });
  auto it = srednie.rbegin();
  for (int i = 0; i < 3; i++) {
    cout << "#3.2.c) Osoba: " << it->second << " " << it->first << endl;
    it++;
  }

  // d) Znajdź osobę (osoby), których różnica między najniższym i najwyższym wynikiem procentowym jest największa.
  multimap<double, L> roznice;
  for (auto [o, w] : wyniki) {
    double mini = *min_element(w.begin(), w.end());
    double maxi = *max_element(w.begin(), w.end());
    roznice.insert({ maxi - mini,o });
  }
  cout << "#3.2.d) Osoba " << roznice.rbegin()->second << " z różnicą = " << roznice.rbegin()->first << endl;
}
