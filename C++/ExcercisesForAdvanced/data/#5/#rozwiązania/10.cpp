// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr unsigned kMin = 3; // minimalna liczba krążków
constexpr unsigned kMax = 12; // maksymalna liczba krążków
constexpr float podstawa = 24.; // wielkość podstawowa do budowy krążka
class Krazek : public Baza, public RectangleShape {
private:
  unsigned wielkosc = 1; // wielkość, 1 najmniejszy  
public:
  Krazek(unsigned w = 1) {
    setFillColor(Color(160, 180, 190));
    wielkosc = w;
    setSize(Vector2f(w * podstawa + podstawa, podstawa));
    setOutlineColor(Color(0, 0, 50));
    setOutlineThickness(1);
    setOrigin(Vector2f((w * podstawa + podstawa) / 2., podstawa / 2.));
  }
  
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() { }
};

typedef stack<shared_ptr<Krazek>> sPalik;
class Palik : public RectangleShape, public Baza, public sPalik {
private:
  unsigned nr; // 1, 2, 3 
public:
  Palik(unsigned nrPalika) { Palik(nrPalika, 0); }
  Palik(unsigned nrPalika, unsigned nKrazki = 3) : nr(nrPalika) {
    setSize(Vector2f(podstawa / 2, kMax * (podstawa * 1.5)));
    setOrigin(Vector2f(podstawa / 4, kMax * (podstawa * 1.5))); // dół palika jako jego punkt położenia
    setPosition(Vector2f(WIDTH / 4 * nr, HEIGHT - 100));
    setFillColor(Color::Black);
    if (nKrazki != 0 and (nKrazki<kMin or nKrazki>kMax)) { nKrazki = 3; }
    nalozKrazkiNaStart(nKrazki);    
  }
  void nalozKrazkiNaStart(unsigned nKrazki = 3) {
    for (unsigned i = nKrazki; i >= 1; i--) {
      auto k = make_shared<Krazek>(i);
      program.obiekty.push_back(k);
      Push(k);
    }
  }
  void Push(shared_ptr<Krazek> k) {
    push(k);
    top()->setPosition(Vector2f(getPosition().x, getPosition().y - podstawa * size()));
  }
  void Pop() { pop(); }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {}
};
class Hanoi {
  queue <pair<shared_ptr<Palik>, shared_ptr<Palik>>> ruchy;
  shared_ptr<Palik> p1 = nullptr;
  shared_ptr<Palik> p2 = nullptr;
  shared_ptr<Palik> p3 = nullptr;
public:
  Hanoi(unsigned nKrazki = 3) {
    p1 = make_shared<Palik>(1, nKrazki);
    p2 = make_shared<Palik>(2, 0);
    p3 = make_shared<Palik>(3, 0);
    program.obiekty.push_back(p1);
    program.obiekty.push_back(p2);
    program.obiekty.push_back(p3);
    start(nKrazki, p1, p2, p3);

    program.dodaj_rysowanie(
      [&]() {
        if (ruchy.size()) {          
          auto& [a, c] = ruchy.front(); // z a na c (paliki)
          if (ruchy.size() % 2 == 0) { // animacja poprzedzająca
            ruchy.pop();
            a->setFillColor(Color::Yellow);
            c->setFillColor(Color::Red);
          }
          else { // przekładanie krążka
            auto krazek = a->top();
            ruchy.pop();
            a->Pop();
            c->Push(krazek);
            p1->setFillColor(Color::Black);
            p2->setFillColor(Color::Black);
            p3->setFillColor(Color::Black);

          }
        }
      });
  }
  void start(unsigned n, shared_ptr<Palik>& a, shared_ptr<Palik>& b, shared_ptr<Palik>& c) {
    if (n > 0) {
      start(n - 1, a, c, b);
      ruchy.push({ a,c }); // animacja poprzedzająca
      ruchy.push({ a,c }); // krążek
      start(n - 1, b, a, c);
    }
  }
};
int main() {
  setlocale(LC_ALL, "");
  Hanoi H(4);
  program.W->setVerticalSyncEnabled(false);
  program.W->setFramerateLimit(1);
  // program.ustawPauze(true); // Enter uruchamia rysowanie. Możesz odkomentować instrukcję.
  program.start();
}
