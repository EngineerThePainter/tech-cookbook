#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
// wykorzystam możliwość kolorowania znaków w konsoli
const string reset("\033[0m"); // RESET koloru
vector<string> kolory = { "\033[91m","\033[92m","\033[93m","\033[94m",
"\033[95m","\033[101m","\033[102m","\033[103m" };
vector<vector<string>> plecak; // '0' - puste miejsce w plecaku
const L plecak_size = 49; // od 0 do 49, rozmiar 50x50
// struktura przechowująca dane o zabawce
struct Zabawka {
  string nazwa = "";
  L bok = 0;
  UL grosze = 0;
  UL ile = 0;
  UL ile_start = 0;
  L kod_zabawki = 0;
  string kolor;
};
// zawartość zabawek w sklepie
vector<Zabawka> sklep;
// przeliczam kwotę na zł i grosze
pair<UL, UL> grosze(string kwota) {
  auto zlpoz = kwota.find("zl");
  UL zl = 0, gr = 0;
  if (zlpoz != string::npos) {
    zl = stoul(kwota.substr(0, zlpoz));
    kwota.replace(0, zlpoz + 2, "");
  }
  auto grpoz = kwota.find("gr");
  if (grpoz != string::npos) {
    gr = stoul(kwota.substr(0, grpoz));
  }
  return { zl,gr };
}
// wgranie danych sklepowych
void wgraj() {
  ifstream zabawki("21_zabawki.txt");
  string temp;
  getline(zabawki, temp); // ignoruję pierwszą linię z nagłówkami
  while (!zabawki.eof()) {
    string nazwa;
    getline(zabawki, nazwa, ';');
    getline(zabawki, temp, ';');
    L bok = stol(temp);
    getline(zabawki, temp, ';');
    auto [zl, gr] = grosze(temp);
    getline(zabawki, temp);
    UL ile = stoul(temp);
    L kod = sklep.size() + 1;
    string kolor = kolory.back();
    kolory.pop_back();
    sklep.push_back({ nazwa,bok,zl * 100 + gr,ile,ile,kod,kolor });
  }
  zabawki.close();
  cout << "Sklep wgrany.\n";
}
void przygotowania_plecaka() {
  plecak.resize(plecak_size + 1, {});
  for (auto& e : plecak) e.resize(plecak_size + 1, "0");
  cout << "Plecak pusty, gotowy i czeka.\n";
}
double cennosc(Zabawka& z) {
  return z.grosze * 1. / z.bok * 1.;
}
// operator porównywania cenności dwóch zabawek
bool operator<(Zabawka& z1, Zabawka& z2) {
  // stosunek cena/wielkość a przy równej cenności wielkość ma znaczenie
  return ((cennosc(z1) == cennosc(z2) and z1.bok >= z2.bok) or (cennosc(z1) < cennosc(z2)));
}
// sortowanie zabawek wg cenności i dzięki operatorowi <
void posortuj() {
  for (size_t i = sklep.size() - 1; i >= 1; i--) {
    for (size_t j = 0; j < i; j++) {
      if (sklep[j] < sklep[j + 1]) {
        Zabawka temp = sklep[j];
        sklep[j] = sklep[j + 1];
        sklep[j + 1] = temp;
      }
    }
  }
  cout << "Zabawki poukładane od najcenniejszych do najmniej cennych.\n";
}
// czy zabawka w podanym punkcie plecaka (z uwzględnieniem jej wielkości)
// mieści się jeszcze w plecaku?
bool w_plecaku(Zabawka& z, L xplecak, L yplecak) {
  if ((yplecak + z.bok - 1 > plecak_size) or (xplecak - z.bok + 1 < 0)) return false;
  return true;
}
// czy zabawka wstawiona na pozycję w plecaku koliduje z czymś innym? 
// uznajemy lewy dolny róg zabawki za wierzchołek na pozycji x-plecak, y-plecak,
// gdzie x i y to pozycja w plecaku o rozmiarze 50x50
bool kolizja(Zabawka& z, L xplecak, L yplecak) {
  for (L x = xplecak; x > xplecak - z.bok; x--) {
    for (L y = yplecak; y < yplecak + z.bok; y++) {
      if (plecak[x][y] != "0") return true;
    }
  }
  return false;
}
// jeżeli można, to wkładamy do plecaka zabawkę
bool wkladanie(Zabawka& z) {
  L x = -1, y = -1;
  L yplecak = plecak_size - z.bok + 1;
  y = yplecak;
  // wkładam od góry przy krawędzi prawej maksymalnie do dołu
  for (L xplecak = z.bok - 1; xplecak <= plecak_size; xplecak++) {
    if (!kolizja(z, xplecak, y)) {
      x = xplecak;
    }
    else break;
  }
  if (x != -1) {
    // ruch zabawki w lewo
    for (L yplecak = plecak_size - z.bok + 1; yplecak >= 0; yplecak--) {
      if (!kolizja(z, x, yplecak)) {
        y = yplecak;
      }
      else break;
    }
    // ruch zabawki w dół
    for (L xplecak = z.bok - 1; xplecak <= plecak_size; xplecak++) {
      if (w_plecaku(z, xplecak, y) and !kolizja(z, xplecak, y)) {
        x = xplecak;
      }
      else break;
    }
    // mam x, y - tu mogę włożyć przedmiot
    if (w_plecaku(z, x, y)) {
      for (L xpoz = x; xpoz > x - z.bok; xpoz--) {
        for (L ypoz = y; ypoz < y + z.bok; ypoz++) {
          plecak[xpoz][ypoz] = z.kolor + to_string(z.kod_zabawki) + reset;
        }
      }
      return true;
    }
  }
  return false;
}
void plecak_pokaz() {
  for (auto& e : plecak) {
    for (auto& z : e) {
      cout << z;
    }
    cout << endl;
  }
}
void kradnij_zachlannie() {
  for (auto& z : sklep) {
    while (z.ile and wkladanie(z)) {
      z.ile--;
      // usuń komentarz dla poniższego kodu, jeżeli chcesz obserwować, 
      // jak złodziej wkłada kolejne zabawki

      // plecak_pokaz(); string czekaj; cin >> czekaj; 
    }
  }
}
void sklep_spis(bool start = false) {
  for (auto& e : sklep) {
    cout << e.nazwa << " cenność=" << cennosc(e) << " wielkość=" << e.bok << " kod="
      << e.kolor << e.kod_zabawki << reset << " ILOŚĆ = " << e.ile;
    if (start) cout << "(start " << e.ile_start << ")";
    cout << endl;
  }
}
int main() {
  setlocale(LC_ALL, "");

  przygotowania_plecaka();

  wgraj();

  posortuj();

  sklep_spis();

  kradnij_zachlannie();

  plecak_pokaz();

  sklep_spis(true);
}
