#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct dane {
  string txt = "";
  L n = 0;
};

struct es { // element stosu
  dane d;
  es* pod = nullptr; // element stosu
};

struct Stos { // stos
  UL ile = 0;
  es* szczyt = nullptr;
};

// pokaż zawartość es
void es_pokaz(es* e) {
  if (e != nullptr) cout << "txt=" << e->d.txt << ", n=" << e->d.n << endl;
}

// pokaż górny element na stosie
void stos_szczyt(Stos& s) {
  if (s.ile) es_pokaz(s.szczyt);
  else cout << "\nbrak elementów na stosie\n";
}

// pokaż wszystko od szczytowego do dolnego elementu
void stos_wszystko(Stos& s) {
  es* e = s.szczyt;
  while (e != nullptr) {
    es_pokaz(e);
    e = e->pod;
  }
}

// dodaj es do stosu
void stos_dodaj(Stos& s, dane d) {
  es* nowy = new es;
  nowy->d = d;
  nowy->pod = s.szczyt;
  s.szczyt = nowy;
  s.ile++;
}

// usuń ze stosu
void stos_usun(Stos& s) {
  if (s.ile) {
    es* nowy = s.szczyt->pod;
    delete s.szczyt;
    s.ile--;
    s.szczyt = nowy;
  }
}

// kopia szczytowego elementu na stosie
void stos_kopia(Stos& s) {
  if (s.ile) {
    es* nowy = new es;
    nowy->d.n = s.szczyt->d.n;
    nowy->d.txt = s.szczyt->d.txt;
    nowy->pod = s.szczyt;
    s.szczyt = nowy;
    s.ile++;
  }
}
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  Stos s;

  stos_dodaj(s, { "Robert",100 });
  stos_dodaj(s, { "Katarzyna",120 });
  stos_dodaj(s, { "Bonifacy",90 });
  stos_szczyt(s);
  cout << s.ile << endl; // ile elementów na stosie?
  stos_wszystko(s);
  stos_usun(s);
  cout << s.ile << endl; // ile elementów na stosie?
  stos_wszystko(s);
  stos_kopia(s);
  cout << s.ile << endl; // ile elementów na stosie?
  stos_wszystko(s);
}
