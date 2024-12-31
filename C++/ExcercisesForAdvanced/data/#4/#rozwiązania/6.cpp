#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
//////////////////////////////////////////////////////
const string dark("\033[7m");
const string reset("\033[0m");
enum Bierki : unsigned {
  bPionek, cPionek, bKrol, cKrol, bHetman, cHetman,
  bGoniec, cGoniec, bSkoczek, cSkoczek, bWieza, cWieza, pusto
};
enum Kolumny : int { A, B, C, D, E, F, G, H };
enum Wiersze : int { w1, w2, w3, w4, w5, w6, w7, w8 };
map<Bierki, string> reprezentacja{
  {bPionek,"P"},  {cPionek,"p"},  {bKrol,"K"},  {cKrol,"k"},
  {bHetman,"H"},  {cHetman,"h"},  {bGoniec,"G"}, {cGoniec,"g"},
  {bSkoczek,"S"}, {cSkoczek,"s"},  {bWieza,"W"}, {cWieza,"w"},
  {pusto,"."}
};
map<Kolumny, string> strKolumny{
  {A,"A"},{B,"B"},{C,"C"},{D,"D"},{E,"E"},{F,"F"},{G,"G"},{H,"H"}
};
map <Wiersze, string> strWiersze{
  {w1,"1"},{w2,"2"},{w3,"3"},{w4,"4"},{w5,"5"},{w6,"6"},{w7,"7"},{w8,"8"}
};
class Pole {
public:
  bool biale = true;
  Bierki bierka;
  string operator()() { // użycie obiektu jako funkcji zwróci "rysunek" pola
    if (biale) {
      return dark + reprezentacja[bierka] + reset;
    }
    else {
      return reprezentacja[bierka];
    }
  }
};
class Ruch {
public:
  pair<Kolumny, Wiersze> ruch_z;
  pair<Kolumny, Wiersze> ruch_na;
};
class Szachownica {
public:
  map<Kolumny, map<Wiersze, Pole>> szachownica;
  vector<Ruch> gra;
  Szachownica() {
    restart();
  }
  void restart() {
    // początkowe ustawienie pionków na planszy
    for (auto w = w1; w <= w8; w = Wiersze(w + 1)) {
      for (auto k = A; k <= H; k = Kolumny(k + 1)) {
        Pole p;
        p.biale = ((w + k) % 2 == 0) ? false : true; // czarne/białe pole
        if (w == w1 and (k == A or k == H)) p.bierka = bWieza;
        else if (w == w8 and (k == A or k == H)) p.bierka = cWieza;
        else if (w == w1 and (k == B or k == G)) p.bierka = bSkoczek;
        else if (w == w8 and (k == B or k == G)) p.bierka = cSkoczek;
        else if (w == w1 and (k == C or k == F)) p.bierka = bGoniec;
        else if (w == w8 and (k == C or k == F)) p.bierka = cGoniec;
        else if (w == w1 and k == D) p.bierka = bHetman;
        else if (w == w8 and k == D) p.bierka = cHetman;
        else if (w == w1 and k == E) p.bierka = bKrol;
        else if (w == w8 and k == E) p.bierka = cKrol;
        else if (w == w2) p.bierka = bPionek;
        else if (w == w7) p.bierka = cPionek;
        else p.bierka = pusto;
        szachownica[k][w] = p;
      }
    }
  }
  // dodaje ruch do wektora z historią ruchów gry, wykonuje ruch
  // na szachownicy w obecnym stanie
  void rusz(Ruch r, bool pokazywanie=true) {
    odtwarzaj(r);
    gra.push_back(r);
    if (pokazywanie) pokaz();
  }
  void odtwarzaj(Ruch r) {
    auto bierka = szachownica[r.ruch_z.first][r.ruch_z.second].bierka;
    szachownica[r.ruch_z.first][r.ruch_z.second].bierka = pusto;
    szachownica[r.ruch_na.first][r.ruch_na.second].bierka = bierka;    
  }
  // ustawia szachownicę na konkretny ruch z historii gry,
  // 0 to pozycja początkowa. Wartość nie powinna być większa 
  // niż wielkość wektora z historią ruchów
  void pokaz_nty(size_t i = 0) {
    Szachownica tymczasowa;    
    for (size_t j = 0; j + 1 <= i; j++) {
      tymczasowa.rusz(gra[j],false);
    }
    tymczasowa.pokaz();    
  }  
  // pokaż obecny stan szachownicy
  void pokaz() {
    if (gra.size()) {
      auto r = *gra.rbegin();
      cout << "RUCH nr=" << gra.size() << " z " <<
        strKolumny[r.ruch_z.first] << strWiersze[r.ruch_z.second] <<
        " na pozycję " <<
        strKolumny[r.ruch_na.first] << strWiersze[r.ruch_na.second] 
        << endl;
    }
    else {
      cout << "START GRY\n";
    }
    for (auto w = w8; w >= w1; w = Wiersze(w - 1)) {
      for (auto k = A; k <= H; k = Kolumny(k + 1)) {
        cout << szachownica[k][w]();
      }
      cout << endl;
    }
    cout << endl;
  }
  void zapisz() {
    ofstream z("4_zapis_gry.txt"); // plik do zapisu gry
    for (auto& r : gra) {
      z << r.ruch_z.first << " " << r.ruch_z.second << " "
        << r.ruch_na.first << " " << r.ruch_na.second
        << endl;
    }
    z.close();
  }
  void zapisz_nty(size_t nty) {
    ofstream z("4_zapis_gry_ruch_nr" + to_string(nty) + ".txt");
    Szachownica tymczasowa;
    for (size_t j = 0; j + 1 <= nty; j++) {
      tymczasowa.rusz(gra[j], false);
    }
    for (auto w = w8; w >= w1; w = Wiersze(w - 1)) {
      for (auto k = A; k <= H; k = Kolumny(k + 1)) {
        z << reprezentacja[tymczasowa.szachownica[k][w].bierka];
      }
      z << endl;
    }
    z.close();
  }
  void odczyt() {
    gra.clear();
    restart();
    ifstream o("4_zapis_gry.txt");
    int zk, zw, nak, naw;
    while (o >> zk and o >> zw and o >> nak and o >> naw) {
      rusz(Ruch({
        {Kolumny(zk),Wiersze(zw)},
        {Kolumny(nak),Wiersze(naw)}
        }), false);      
    }
    o.close();
  }
};

int main() {
  setlocale(LC_ALL, "");
  Szachownica s;
  s.pokaz();
  s.rusz(Ruch({ {A,w2},{A,w4} })); // biały pionek z A2 na A4 itd.
  s.rusz(Ruch({ {A,w7},{A,w5} }));  
  s.rusz(Ruch({ {H,w2},{H,w4} })); // trzeci ruch
  s.rusz(Ruch({ {E,w7},{E,w5} }));  
  s.rusz(Ruch({ {G,w1},{H,w3} }));  
  s.rusz(Ruch({ {B,w8},{C,w6} })); // szósty ruch

  cout << "\tSytuacja po ruchu nr: 3" << endl;
  s.pokaz_nty(3);
  s.pokaz(); // pokaż sytuację po ostatnim ruchu (szósty ruch)
  s.zapisz();
  s.zapisz_nty(3);

  Szachownica s2; 
  s2.odczyt(); // odczyt dla testu, inna szachownica
  s2.pokaz();
  s2.pokaz_nty(4);
}
