#include <iostream>
#include <random>
#include <list>
#include <ctime>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
const UL LIMIT = 250000;
const double dodajProcent = .45;
class Klient {
public:
  inline static UL licznik = 0;
  Klient() {
    Klient::licznik++;
  }
};
int main() {
  setlocale(LC_ALL, "");
  default_random_engine(rng);
  rng.seed(time(0));
  uniform_real_distribution<double> podajnik(0, 1);
  list<unique_ptr<Klient>> kolejka;
  UL wejsc_do_petli = 0;
  // PRZYPADEK 1
  UL opuscilo = 0;
  while (kolejka.size() < LIMIT) {
    if (podajnik(rng) > dodajProcent) {
      kolejka.push_back(make_unique<Klient>());
      wejsc_do_petli++;
    }
    else if (kolejka.size()) {
      kolejka.pop_front();
      opuscilo++;
      wejsc_do_petli++;
    }
  }
  cout.precision(15);
  cout << "PRZYPADEK 1:\n";
  cout << "Pętla wykonała się " << wejsc_do_petli << " razy." << endl;
  cout << "Utworzonych klientów: " << Klient::licznik << endl;
  cout << "ODP:" << opuscilo * 1.0 / kolejka.size() * 1.0 << endl;
  cout << "ODP:" << opuscilo * 1.0 / Klient::licznik * 1.0 << endl;
  cout << "ODP:" << opuscilo * 1.0 / wejsc_do_petli * 1.0 << endl;

  // PRZYPADEK 2
  opuscilo = 0;
  kolejka.clear();
  Klient::licznik = 0;
  wejsc_do_petli = 0;

  while (kolejka.size() < LIMIT) {
    wejsc_do_petli++;
    if (podajnik(rng) > dodajProcent) {
      kolejka.push_back(make_unique<Klient>());
    }
    else if (kolejka.size()) {
      kolejka.pop_front();
      opuscilo++;
    }
    else {
      kolejka.push_back(make_unique<Klient>());
      kolejka.pop_front();
      wejsc_do_petli++; // dwa wydarzenia, więc ponownie zwiększam jakby liczbę kroków pętli
      opuscilo++;
    }
  }
  cout << "PRZYPADEK 2:\n";
  cout << "Pętla wykonała się " << wejsc_do_petli << " razy." << endl;
  cout << "Utworzonych klientów: " << Klient::licznik << endl;
  cout << "ODP:" << opuscilo * 1.0 / kolejka.size() * 1.0 << endl;
  cout << "ODP:" << opuscilo * 1.0 / Klient::licznik * 1.0 << endl;
  cout << "ODP:" << opuscilo * 1.0 / wejsc_do_petli * 1.0 << endl;
  /*
    Interpretacja:
    W pierwszym przypadku licznik kroków pętli jest z reguły mniejszy,
    ponieważ ignorujemy te kroki pętli, które próbują wypuścić klienta z pustej
    kolejki. Podobnie liczba utworzonych klientów w pierwszym przypadku jest nieznacznie,
    ale regularnie mniejsza, gdyż w tym pierwszym przypadku nie tworzymy klienta,
    a w drugim przypadku zawsze go dodajemy i od razu wypuszczamy.
    Obliczone i wymagane w zadaniu stosunki są bardzo podobne. Wartość bliska
    4.5 oznacza, przy szansie 45% na opuszczenie i 55% na pojawienie się
    w kolejce, że trzeba utworzyć około 1 380 000, by kolejka osiągnęła 250 000 - zatem
    trzeba utworzyć o 4.5 razy więcej osób od tej liczby, którą ma osiągnąć kolejka.
    Sprawdź to dla np. 500 000 osób w kolejce. Proporcja będzie taka sama! Wynika
    to ze stosunku 45/55.

    Wartość zbliżona do 0.82 to stosunek osób, które opuściły kolejkę, do
    wszystkich utworzonych. Łatwo zauważyć, że do proporcji 1 brakuje 0.18,
    i gdyby tę wartość pomnożyć przez 4.5 i dodać do 0.18 otrzymamy... około 1.
    Zatem 0.82 to właśnie ten 4.5-krotny narzut do wartości 0.18, a ta z kolei
    wyraża tutaj owe 250,000 osób (W stosunku do wszystkich
    utworzonych to właśnie około 0.18. Sprawdź to instrukcją:
    cout << "ODP:" << 250000 * 1.0 / Klient::licznik * 1.0 << endl;

    Wartość 0.45 to wartość dokładnie oddająca szansę na opuszczenie kolejki
    w kolejnych zdarzeniach. Nie może być inna przy odpowiednio dużej próbie
    i generatorze losowym o dobrym rozkładzie.
  */
}
