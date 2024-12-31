#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
typedef long long int L;
//////////////////////////////////////////////////////
class WyciagaczLiczb {
public:
  string text;
  vector<L> calkowite;
  vector<double> ulamkowe;
  // konstruktory
  WyciagaczLiczb(string txt) : text(txt) {}
  WyciagaczLiczb(ifstream& plik) {
    string temp;
    while (!plik.eof()) {
      getline(plik, temp);
      text += temp;
    }    
  }
  // tutaj wykorzystam regex
  void poszukiwania() {
    // całkowite i ułamkowe z + lub - na początku
    regex wzorzec("((\\+|-|)[\\d|\\d\\.])+");            
    auto it = regex_iterator(text.begin(), text.end(), wzorzec);
    // domyślny konstruktor typu regex_iterator to iterator końcowy
    auto end = decltype(it)(); 
    while( it != end) { // dopóki znajduję kolejne dopasowania
      match_results m = *it; // dopasowanie
      string liczba = m.str();
      size_t poz = liczba.find("."); // czy jest kropka, np. 14.4?
      if (poz!= string::npos) {        
        liczba.replace(poz,1,","); // 14.4 -> 14,4
        ulamkowe.push_back(stod(liczba)); // string -> double
      }
      // string -> long long int
      else calkowite.push_back(stoll(liczba)); 
      ++it;
    }    
  }
};
int main() {
  setlocale(LC_ALL, "");
  // konstruktor ze stringiem
  WyciagaczLiczb w1(
    "abc 12 defg -431 hij 14.4 klmno +1 prst 89.172 u99w44.55yz"
    "abc 42 defg -123 hij -14.4 klmno 1 prst +172.98 u99w44.55yz");
  w1.poszukiwania();
  cout << "Całkowite: " << endl;
  for (auto e : w1.calkowite) cout << e << " "; cout << endl;
  cout << "Ułamkowe: " << endl;
  for (auto e : w1.ulamkowe) cout << e << " "; cout << endl;
  
  ifstream plik("5_liczby_w_tekscie.txt");
  // konstruktor z otwartym do odczytu plikiem
  WyciagaczLiczb w2(plik);
  w2.poszukiwania();
  cout << "Całkowite: " << endl;
  for (auto e : w2.calkowite) cout << e << " "; cout << endl;
  cout << "Ułamkowe: " << endl;
  for (auto e : w2.ulamkowe) cout << e << " "; cout << endl;
}
