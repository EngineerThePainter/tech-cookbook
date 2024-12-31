#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
size_t pozycja_naglowka(vector<wstring>& naglowki, wstring umiejka) {
  size_t poz = 0;
  for (auto x : naglowki) {
    poz++;
    if (x == umiejka) {
      return poz;
    }
  }
}

int main() {
  setlocale(LC_ALL, "");
  // system("chcp 65001"); // zmienia kodowanie konsoli w systemie Windows  na UTF-8; ta instrukcja może się przydać
  wifstream pwyniki("4_wyniki.txt"); // plik też ma kodowanie UTF-8
  wstring pomoc;
  // nagłówki: agent, strzelanie itd.
  vector<wstring> naglowki = { L"agent", L"strzelanie", L"hakowanie",
    L"walka wręcz", L"pływanie", L"wspinaczka", L"inteligencja", L"wiedza" };
  // przeczytaj pierwszy wiersz z nagłówkami
  getline(pwyniki, pomoc);
  // czytaj dane i włóż je do unordered_map według schematu:
  // { {umiejętność, { {wartość, agent}, {wartość, agent}, ... }, ... } np.
  // { {"strzelanie", { {59, "agent 001"}, {135, "agent 002"}, ... } itd;
  unordered_map<wstring, multimap<int, wstring>> dane;
    for (size_t p = 1; p < naglowki.size(); p++)
      dane.insert({ naglowki[p], {} });

  // podczas odczytu zwróć uwagę na obecność pustych wierszy w pliku 4_wyniki.txt
  // i usuń je, jeżeli występują
  while (!pwyniki.eof()) {
    wstring agent;
    getline(pwyniki, agent, L','); // agent
    // strzelanie ... inteligencja
    size_t p = 0;
    p++;
    for (int i = 6; i--;) {
      getline(pwyniki, pomoc, L',');
      dane[naglowki[p]].insert({ stoi(pomoc), agent });
      p++;
    }
    // wiedza
    getline(pwyniki, pomoc);
    dane[naglowki[p]].insert({ stoi(pomoc), agent });
  }
  // a) Podaj listę osób (nazwa/numer agenta) o 10 najlepszych wynikach z pływania.

  cout << "a)\n";
  set<int> ten; // 10 najlepszych wyników
  auto iten = dane[L"pływanie"s].rbegin(); // uwaga, iterator odwrotny
  while (iten != dane[L"pływanie"s].rend() and ten.size() <= 10) {
    auto& [v, agent] = *iten++;
    ten.insert(v);
    if (ten.size()<=10) wcout << agent << L"->" << v << endl;    
  }
  // b) W której umiejętności agenci radzą sobie najlepiej 
  // (analizuj arytmetyczną średnią punktów wszystkich agentów dla każdej umiejętności).  
  cout << "b)\n";
  double maxsrednia = -1;
  wstring umiejka;
  for (size_t p = 1; p < naglowki.size(); p++) {
    double srednia = 0;
    for (auto& [v, agent] : dane[naglowki[p]]) {
      srednia += v;
    }
    srednia /= dane[naglowki[p]].size();
    if (maxsrednia < srednia) {
      maxsrednia = srednia;
      umiejka = naglowki[p];
    }
  }
  wcout << L"Największa średnia = "s << maxsrednia << L" to umiejętność "s << umiejka << endl;
  cout << "c)\n";
  // c)   Wyświetl listę osób, które uzyskały
  // najgorszy wynik w danej umiejętności.

  for (size_t p = 1; p < naglowki.size(); p++) {
    auto first = dane[naglowki[p]].begin();
    int fv = first->first;
    while (fv == first->first) { // ta pętla pokaże wszystkich o najniższej wartości
      auto& [v, agent] = *first;
      wcout << agent << L" w umiejętności " << naglowki[p] << L" zdobył tylko " << v << endl;
      ++first;
    }

  }
  cout << "d)\n";
  // d)   Przedstaw uporządkowane listy agentów od najlepszego do najgorszego dla wspinaczki, hakowania i wiedzy.
  for (auto& e : vector<wstring>{ L"wspinaczka",L"hakowanie",L"wiedza" }) {
    wcout << L"------------" << e << endl;
    for (auto it = dane[e].rbegin(); it != dane[e].rend(); it++) {
      auto& [v, agent] = *it;
      wcout << agent << L"\t\t" << v << endl;
    }
  }
  cout << "\n\ne)\n\n";
  map<wstring, int> przyrost_agenta;
  for (auto& [v, agent] : dane[L"inteligencja"]) {
    przyrost_agenta[agent] = v / 10;
    wcout << agent << L"\t=\t" << przyrost_agenta[agent] << endl;
  }
  cout << "\nHAKOWANIE AGENTÓW w 2030 roku\n";
  for (auto& [v, agent] : dane[L"hakowanie"]) {
    wcout << agent << L"\t=\t" << v + 10 * przyrost_agenta[agent] << L" było " << v << endl;
  }
  cout << "\nWIEDZA AGENTÓW w 2040 roku\n";
  for (auto& [v, agent] : dane[L"wiedza"]) {
    wcout << agent << L"\t=\t" << v + 20 * przyrost_agenta[agent] << L" było " << v << endl;
  }
  pwyniki.close();
}
