#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <ctime>
#include <map>
using namespace std;
//////////////////////////////////////////////////////
/* tu przechowamy tajne przypisanie pozycji piksela dla znaku z alfabetu */
map<char, pair<int, int>> mapa_kodowania;

/*
  Zwraca parę wiersz:kolumna dla pozycji bitu w napisie. Liczymy pozycje od 1.
  Na przykład dla 23 to 1x23, a dla 29 to 2x4, dla 1 to 1x1, a dla 625 to 25x25
*/
pair<int, int> pozycjaNaWK(int poz) {
  return { poz / 25 + bool(poz % 25), (poz % 25) ? poz % 25 : 25 };
}

/* 
  Zwraca w ciągu 625 bitów pozycję, która odpowiada pikselowi w obrazku na pozycji Wiersz x Kolumna  
*/
int WKnaPozycje(pair<int, int> wk) {
  return (wk.first - 1) * 25 + wk.second;
}

/* 
  Każdej literze alfabetu będzie przypisana niepowtarzalna para {wiersz, kolumna} 
*/
void losowe_kody() {
  string alfabet = "qwertyuiopasdfghjklzxcvbnm";
  set<pair<int, int>> kody; // zbiór gwarantuje niepowtarzalność par
  while (kody.size() < alfabet.size()) {    
    kody.insert(pozycjaNaWK(rand() % 625 + 1));
  }
  auto it = kody.begin();
  for (auto znak : alfabet) {
    mapa_kodowania[znak] = *it;
    it++;
  }
  // pokaż przypisania ZNAK=>WIERSZ x KOLUMNA
  for (auto& [znak, para] : mapa_kodowania) {
    cout << znak << " = " << para.first << " x " << para.second << " == " << WKnaPozycje(para) << endl;
  }
}
class Kryptotron {
public:      
  static array<bool, 625> koduj(char znak) {
    array<bool, 625> bity;
    auto pozycja = mapa_kodowania[znak];
    // 1) losowy ciąg bitów
    for (auto& bit : bity) bit = rand() % 2; // 0|1 -> biały, czarny
    // 2) pozycja niepowtarzalna dla znaku: czarna
    bity[WKnaPozycje(pozycja) - 1] = 1;
    // 3) pozycje pozostałych znaków: białe
    for (auto& [z, wk] : mapa_kodowania) {
      if (znak == z) continue;
      bity[WKnaPozycje(wk) - 1] = 0;
    }
    return bity;
  }
  // pokaż znak jako linię lub jako 25 wierszy po 25 znaków
  static void pokaz(ostream& s, char znak, bool linia = true) {
    auto bity = koduj(znak);
    int poz = 1;
    for (auto& e : bity) {
      s << e;
      if (!linia and ++poz % 25 == 1) s << endl;
    }    
  }  
  static void pokazSlowo(ostream& s, string slowo) {
    for (auto& z : slowo) {
      pokaz(s, z);
      s << endl;
    }
  }
  static string dekoduj(string plik) {
    ifstream szyfr(plik);
    string bity;
    string wynik;
    while (getline(szyfr, bity)) {      
      for (auto& [znak, wk] : mapa_kodowania) {
        if (bity[WKnaPozycje(wk) - 1] == '1') {
          wynik += znak;
          break;
        }
      }
    }
    szyfr.close();
    return wynik;
  }
  static void kodujDoPBM(char znak) {
    ofstream plik(string(1,znak) + ".pbm");
    plik << "P1" << endl;
    plik << "# To jest bitmapa 25x25 z literką " << znak << endl;
    plik << "25 25" << endl;
    pokaz(plik, znak, false);
    plik.close();
  }
};
int main() {
  setlocale(LC_ALL, ""); srand(time(0));

  losowe_kody();
  Kryptotron::pokaz(cout, 'a'); // linia bitów znaku 'a'
  cout << endl;
  // bity znaku 'a' w 25 wierszach po 25 kolumn, zwróć uwagę, że tylko jeden bit na pewno się nie zmieni :)
  Kryptotron::pokaz(cout, 'a', false); 
  cout << endl;
  ofstream plik("16_kodowanie.txt");
  Kryptotron::pokazSlowo(plik, "rabarbar");
  plik.close();

  cout << Kryptotron::dekoduj("16_kodowanie.txt");

  // tworzę plik PBM, który pozwala wyświetlić plik jako bitmapę czarno-białą, bazując na pliku
  // tekstowym o ustalonym formacie
  Kryptotron::kodujDoPBM('a');
  Kryptotron::kodujDoPBM('b');
  Kryptotron::kodujDoPBM('c');
}
/*
Do sugestii z zadania:
Gdybym znał metodę szyfrowania, ale nie wiedział, jaki piksel
przypisany jest do literki, mógłbym wygenerować odpowiednią liczbę obrazków dla jednej i tej
samej literki. Piksel, który jest zawsze czarny, byłby kandydatem dla tej literki.
Piksele, które nigdy nie byłyby czarne, byłyby kandydatami na kody dla pozostałych liter. Tworząc
dla każdej literki taki zbiór, mógłbym z dużym prawdopodobieństwem odszyfrować, jaki piksel
przypisany jest literce.
*/
