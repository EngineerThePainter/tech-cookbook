#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("27_spis.txt");
  map<string, double> dane2023;
  map<string, double> dane2024;
  vector<pair<string, double>> doPosortowania;
  string data, slicznik;
  double licznik;
  while (getline(plik, data, '\t') and getline(plik, slicznik)) {
    /*
      W przypadku konwersji liczby w postaci 123,34 na 123.34 można użyć następującego polecenia:
      slicznik.replace(slicznik.find(","), 1, ".");
    */
    if (data.substr(0, 4) == "2023")
      dane2023[data] = stod(slicznik);
    else
      dane2024[data] = stod(slicznik);
  }
  plik.close();
  // DANE:
  // START w roku 2023 15000 km
  // 7 litrów/100 km
  // 5zł/1 litr w 2023
  // 9zł/1 litr w 2024

  double km23 = 0, km24 = 0;
  double start = 15000;
  cout.precision(15);
  cout << "Licznik początkowy dla roku 2023 = " << start << endl;
  for (auto& [data, licznik] : dane2023) {
    doPosortowania.push_back({ data,licznik - start });
    km23 += licznik - start;
    start = licznik;
  }
  cout << "Przejechane km w 2023 = " << km23 << endl; // km w 2023 roku
  start = dane2023.rbegin()->second;
  cout << "Licznik początkowy dla roku 2024 = " << start << endl;
  for (auto& [data, licznik] : dane2024) {
    doPosortowania.push_back({ data,licznik - start });
    km24 += licznik - start;
    start = licznik;
  }
  cout << "Przejechane km w 2024 = " << km24 << endl; // km w 2024 roku
  double koszt = km23 / 100.0 * 7.0 * 5.00 + km24 / 100.0 * 7.0 * 9.00;
  cout << "Koszt = " << koszt << " zł" << endl;

  sort(doPosortowania.begin(), doPosortowania.end(),
    [](auto& a, auto& b) {
      return (a.second > b.second);
    });
  double maks = doPosortowania[0].second;
  auto it = doPosortowania.begin();
  cout.precision(6);
  while (it->second == maks) {
    cout << "Najwięcej przejechanych kilometrów w dniu: " <<
      it->first << "(" << it++->second << "km)\n";
  }
}
