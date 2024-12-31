#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct Element {
  Element* lewo = nullptr;
  Element* prawo = nullptr;
  int dane = 0;
};

struct ListaC {
  UL ile = 0;
  Element* pierwszy = nullptr; // dostęp do jakiegoś elementu
};
int pobierz(ListaC& lc) {
  if (lc.ile) {
    return lc.pierwszy->dane;
  }
  else {
    cout << "Nie ma elementów na liście.\n";
    return 0;
  }
}
// przesuń się na następny element na liście (++lc)
void operator++(ListaC& lc) {
  if (lc.ile) {
    lc.pierwszy = lc.pierwszy->prawo;
  }
}
// przesuń się na poprzedni element na liście
void operator--(ListaC& lc) {
  if (lc.ile) {
    lc.pierwszy = lc.pierwszy->lewo;
  }
}
// lc+5 oznacza przesunięcie się o 5 w prawo
void operator+(ListaC& lc, UL oile) {
  if (lc.ile) {
    for (UL x = 1; x <= oile; x++) ++lc;
  }
}
// lc-5 oznacza przesunięcie się o 5 w lewo
void operator-(ListaC& lc, UL oile) {
  if (lc.ile) {
    for (UL x = 1; x <= oile; x++) --lc;
  }
}
// dodaj za pierwszym nowym elementem
void dodaj_za(ListaC& lc, int d) {
  Element* nowy = new Element;
  nowy->dane = d;
  if (lc.ile == 0) {
    nowy->lewo = nowy;
    nowy->prawo = nowy;
    lc.pierwszy = nowy;
  }
  else { // wstaw za obecnym pierwszym
    nowy->lewo = lc.pierwszy;
    nowy->prawo = lc.pierwszy->prawo;
    lc.pierwszy->prawo->lewo = nowy;
    lc.pierwszy->prawo = nowy;
  }
  lc.ile++;
}
// pokaż, idąc w lewo
void lewo(ListaC& lc) {
  Element* temp = lc.pierwszy;
  for (UL i = 1; i <= lc.ile; i++) {
    cout << temp->dane << " ";
    temp = temp->lewo;
  }
  cout << " [" << lc.ile << " elementów]" << endl;
}
// pokaż, idąc w prawo
void prawo(ListaC& lc) {
  Element* temp = lc.pierwszy;
  for (UL i = 1; i <= lc.ile; i++) {
    cout << temp->dane << " ";
    temp = temp->prawo;
  }
  cout << " [" << lc.ile << " elementów]" << endl;
}
void usun(ListaC& lc) {
  if (lc.ile == 1) {
    delete lc.pierwszy;
    lc.pierwszy = nullptr;
    lc.ile--;
  }
  else if (lc.ile > 1) {
    Element* nowy = lc.pierwszy->prawo;
    lc.pierwszy->lewo->prawo = lc.pierwszy->prawo;
    lc.pierwszy->prawo->lewo = lc.pierwszy->lewo;
    delete lc.pierwszy;
    lc.pierwszy = nowy;
    lc.ile--;
  }
}
void usun(ListaC& lc, int szukana) {
  if (lc.ile) {
    Element* temp = lc.pierwszy;
    do {
      if (lc.pierwszy->dane == szukana) {
        usun(lc);
        return;
      }
      lc + 1;
    } while (temp != lc.pierwszy);
  }
}
int main() {
  setlocale(LC_ALL, "");
  ListaC l;
  lewo(l);
  dodaj_za(l, 10);
  cout << pobierz(l) << endl;
  dodaj_za(l, 30);
  dodaj_za(l, 50);
  dodaj_za(l, 90);
  lewo(l);
  prawo(l);
  l + 1; // przesuń w prawo o 1
  prawo(l);
  l - 2; // przesuń w lewo o 2
  prawo(l);
  l + 6;
  prawo(l);

  usun(l);
  prawo(l);

  usun(l, 10);
  usun(l, 30);
 prawo(l);
}
