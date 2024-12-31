#include <iostream>
#include <random>
#include <ctime>
#include <stack>
#include <list>
#include <iomanip>

typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
default_random_engine rng(time(0));
uniform_real_distribution<double> d(0, 10);
const unsigned T = 1000;

struct Szescian {
  double a;
};
// zastosowanie wektora z sześcianami ułatwiłoby rozwiązanie zadania z powodu
// losowania N pozycji, jednak czasami chodzi o poćwiczenie poprawnego używania
// jakiegoś kontenera, zasobu itp.
list<Szescian*> Li;

bool operator<(Szescian& a, Szescian& b) {
  return (a.a < b.a);
}
bool operator>(Szescian& a, Szescian& b) {
  return (a.a > b.a);
}
bool operator==(Szescian& a, Szescian& b) {
  return (a.a == b.a);
}

pair<size_t, size_t> segregator(unsigned N) {
  if (N > T) return { 0,0 }; // za duże N
  stack<Szescian> A, B;
  auto it = Li.begin();
  for (unsigned i = 1; i <= N; i++, it++) {
    Szescian szescian = **it;
    if (i % 2 == 1) { // nieparzysta pozycja sześcianu na liście
      if (A.size() == 0 or A.top() < szescian) {
        A.push(szescian);
        cout << "A<" << A.top().a << "\n";
      }
    }
    else {
      if (B.size() == 0 or (B.top() > szescian)) {
        B.push(szescian);
        cout << "\tB<" << B.top().a << "\n";
      }
    }
  }
  return { A.size(), B.size() };
}

void gen(list<Szescian*>& Li) {
  for (int i = 1; i <= T; i++) {
    Li.push_back(new Szescian);
    Li.back()->a = d(rng);
  }
}


bool czyJest(unsigned poz, vector<unsigned>& v) {
  for (auto e : v) {
    if (poz == e) return true;
  }
  return false;
}

double objetosc(unsigned N) {
  if (N > T) return 0; // za duże N
  double o = 0.;
  // wszystkie_pozycje zawiera wszystkie numery pozycji na liście sześcianów.
  // Z tych pozycji wylosuję N pozycji (N sześcianów)
  vector<unsigned> wszystkie_pozycje;
  wszystkie_pozycje.resize(T, 0);
  for (unsigned i = 0; i < T; i++) wszystkie_pozycje[i] = i + 1;
  vector<unsigned> losowe_pozycje; // N losowych pozycji niepowtarzających się
  while (losowe_pozycje.size() < N) {
    unsigned poz = rand() % wszystkie_pozycje.size();
    losowe_pozycje.push_back(wszystkie_pozycje[poz]);
    // usuwam wylosowaną spośród wszystkich, by uniknąć dublowania
    wszystkie_pozycje.erase(wszystkie_pozycje.begin() + poz);
  }

  // przechodzimy przez całą listę i na wylosowanych pozycjach podbieramy sześcian
  unsigned poz = 1;
  for (auto s : Li) {
    if (czyJest(poz, losowe_pozycje)) { // czy pozycja jest wylosowana?
      double temp = s->a * s->a * s->a;
      o += temp;
      cout << setprecision(25)
        << "Pozycja " << poz << ": objętość = " << temp << endl;
    }
    poz++;
  }
  return o;
}
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  gen(Li);
  cout << Li.size() << endl; // ile sześcianów

  double o = objetosc(2);
  cout << "Objętość suma: = " << o << endl;

  unsigned ile = 100;
  auto [ileA, ileB] = segregator(ile);
  cout << "Dla N=" << ile << ":\n";
  cout << "Na stosie A znalazło się " << ileA << " sześcianów.\n";
  cout << "Na stosie B znalazło się " << ileB << " sześcianów.\n";
}
