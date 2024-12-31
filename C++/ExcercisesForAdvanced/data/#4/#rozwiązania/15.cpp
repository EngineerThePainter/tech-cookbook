#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//////////////////////////////////////////////////////
typedef long long int L;
class CezarMutant {
public:
  inline static string alfabet = "";
  string tekst;
  string szyfrowany;
  int klucz = 3;
  int modyfikator = 1;
  CezarMutant(int k, int m, string t) : tekst(t), klucz(k), modyfikator(m) {
    szyfruj();
  }
  void szyfruj() {
    // nie chcę utracić początkowej wartości klucza szyfrującego
    int klucz_pomoc = klucz;
    szyfrowany = tekst;
    for (auto& znak : szyfrowany) {
      auto poz = alfabet.find(znak);
      if (poz == string::npos) {
        cout << "Niedopuszczalny znak " << znak << "spoza alfabetu.\n";
        return;
      }
      znak = alfabet[(poz + klucz_pomoc) % alfabet.size()]; // szyfrowanie
      klucz_pomoc += modyfikator;
      klucz_pomoc %= alfabet.size();
    }
  }
  string deszyfruj() {
    // nie chcę utracić początkowej wartości klucza deszyfrującego
    int klucz_pomoc = klucz;
    string odwrotny; 
    // alfabet od końca, pozwoli na przesuwanie się w pozycji +klucz (prawo),
    // a nie -klucz (w lewo, gdzie pojawiają się pozycje ujemne)
    odwrotny.assign(alfabet.rbegin(), alfabet.rend());
    for (auto& znak : szyfrowany) {
      auto poz = odwrotny.find(znak);
      if (poz == string::npos) {
        cout << "Niedopuszczalny znak " << znak << "spoza alfabetu.\n";
        return "";
      }
      znak = odwrotny[(poz + klucz_pomoc) % odwrotny.size()]; // szyfrowanie
      klucz_pomoc += modyfikator;
      klucz_pomoc %= odwrotny.size();
    }
    return szyfrowany;
  }
};
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("15_do_szyfrowania.txt");
  getline(plik, CezarMutant::alfabet); // alfabet
  string pomocnicza;
  cout << "Alfabet: [" << CezarMutant::alfabet << "]" << endl;
  while (getline(plik, pomocnicza)) {
    CezarMutant s(3, 1, pomocnicza);
    cout << "k=3,m=1\n[" << pomocnicza << "] => [" << s.szyfrowany << "]" << endl;
    CezarMutant s2(5, 2, pomocnicza);
    cout << "k=5,m=2\n[" << pomocnicza << "] => [" << s2.szyfrowany << "]" << endl;
    cout << "=================== DESZYFRACJA =================\n";
    cout << s.deszyfruj() << endl;
    cout << s2.deszyfruj() << endl;
    cout << endl;
  }
  plik.close();
}
