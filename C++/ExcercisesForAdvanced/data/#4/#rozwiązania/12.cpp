#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
string jakaDomena(string strona) {
  return strona.substr(strona.size() - 3, 3); // zwraca ostatnie trzy znaki .pl, .ua itp.
}
int main() {
  setlocale(LC_ALL, "UTF-8");
  system("chcp 65001"); // UTF-8 w konsoli
  ifstream plik_domen("12_domeny_krajowe.txt");
  string domena, kraj;
  map<string, string> domeny;
  while (getline(plik_domen, domena, '\t') and getline(plik_domen, kraj)) {
    domeny[domena] = kraj;
  }
  plik_domen.close();
  ifstream plik_stron("12_strony.txt");
  string strona;
  string protokol;
  set<string> strony; // strona (by uniknąć dubli dla http i https)
  multimap<string, string> protokoly; // protokół->strona

  while (plik_stron >> strona and plik_stron >> protokol) {        
    strony.insert({ strona });    
    protokoly.insert({ protokol,strona });    
  }
  plik_stron.close();  

  vector<pair<string, unsigned>> ile_w_domenie;
  // zliczam strony w domenach
  for (auto& dom : domeny) {
    auto ile = count_if(strony.begin(), strony.end(),
      [&](auto& element) {
        return (jakaDomena(element) == dom.first);
      });
    ile_w_domenie.push_back({ dom.first,ile });
  }  

  // Ile jest stron w domenie .pl? Podaj je z podziałem na oba protokoły. 
  cout << "Stron w domenie .pl = ";
  for (auto& e : ile_w_domenie)
    if (e.first == ".pl") {
      cout << e.second << endl;
      break;
    }
  cout << "Oto one: " << endl;
  for (auto& s : strony) {
    if (jakaDomena(s) == ".pl") cout << s << endl;
  }

  for (auto prot : vector<string>({ "http","https" })) {
    cout << endl << "Stron w domenie .pl z protokolem " << prot << " :" << endl;
      auto x = count_if(protokoly.begin(), protokoly.end(),
        [&](auto& element) {
          if (element.first == prot and jakaDomena(element.second) == ".pl") {
            cout << "(" << element.second << ")" << endl;
            return true;
          }
          return false;
        });
      cout << " = " << x << endl;
  }


  // Wymień te domeny wraz z nazwą kraju/regionu, które pod kątem liczby 
  // przypisanych do nich stron osiągnęły pierwszą, drugą i trzecią pozycję.   
  // sortuję malejąco ile_w_domenie
  sort(ile_w_domenie.begin(), ile_w_domenie.end(),
    [&](auto& e1, auto& e2) {
      return (e1.second > e2.second);
    });
  // trzy najlepsze wyniki w ilości stron w domenie (niekoniecznie trzy domeny!)
  int trzy_najlepsze_wyniki = 1;
  int temp = ile_w_domenie[0].second;
  for (auto& e : ile_w_domenie) {
    if (temp != e.second) trzy_najlepsze_wyniki++;
    temp = e.second;
    if (trzy_najlepsze_wyniki == 4) break;
    cout << "Domena " << e.first << " " << domeny[e.first] << " " <<
      " := " << e.second << endl;
  }
  // Ile jest stron obsługiwanych przez protokół HTTP, a ile przez HTTPS?
  cout << protokoly.count("http") << " stron HTTP\n";
  cout << protokoly.count("https") << " stron HTTPS\n";
  cout << "Wszystkich stron jest " << strony.size() << endl;  
}
