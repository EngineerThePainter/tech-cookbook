// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <vector>
#include <list>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr float BOK = 20; // wielkość boku komórek
class Komorka : public RectangleShape {
  bool martwa = true;
public:
  Komorka(Vector2f rozmiar) : RectangleShape(rozmiar) {
    setOutlineColor(Color::Black);
    setOutlineThickness(1);
    setFillColor(Color::Yellow);
  }
  bool czyMartwa() { return martwa; }
  bool czyZywa() { return !martwa; }
  void ozyw() {
    martwa = false;
    setFillColor(Color::Green);
  }
  void usmierc() {
    martwa = true;
    setFillColor(Color::Yellow);
  }
  void metamorfoza() {
    if (czyZywa()) usmierc();
    else ozyw();
  }
};
class Gra : public Baza {
public:
  vector<vector<Komorka>> plansza;
  size_t ileX;
  size_t ileY;
  Gra() {
    ileX = WIDTH / BOK;
    ileY = HEIGHT / BOK;
    plansza.resize(ileY + 1);
    for (auto& w : plansza) w.resize(ileX + 1, move(Komorka(Vector2f(BOK, BOK))));
    for (size_t w = 0; w <= ileY; w++) {
      for (size_t k = 0; k <= ileX; k++) {
        plansza[w][k].setPosition(k * BOK, w * BOK);
      }
    }
    program.dodaj_test( "zmiana stanu komórki: przycisk myszki",
      [&]() {
        if (program.event.type == Event::MouseButtonPressed) {
          for (auto& w : plansza) {
            for (auto& k : w) {
              auto x = Mouse::getPosition(*program.W).x;
              auto y = Mouse::getPosition(*program.W).y;
              if (k.getGlobalBounds().contains(Vector2f(x,y))) {
                k.metamorfoza();
              }
            }
          }
          
        }
        return false;
      } );
    program.dodaj_test("czyszczenie planszy: BackSpace",
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::BackSpace) {
          for (auto& w : plansza) {
            for (auto& k : w) {
              k.usmierc();
            }
          }

        }
        return false;
      });
  }

  unsigned policzZywychSasiadow(size_t w, size_t k) {
    unsigned n = 0;
    // komórki na krawędzi mapy zawsze uśmiercę (wbrew regułom gry)
    if (w == 0 or w == ileY or k == 0 or k == ileX) return n;
    for (auto [modw, modk] : vector<pair<int, int>>({ {-1,0},{-1,-1},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} })) {
      if (plansza[w + modw][k + modk].czyZywa()) {
        n++;
      }
    }
    return n;
  }
  void rysuj() {
    for (auto& w : plansza) {
      for (auto& k : w) {
        program.W->draw((k));
      }
    }
  }
  /* REGUŁY:
* Martwa komórka, która ma dokładnie 3 żywych sąsiadów, staje się żywa w następnej jednostce czasu.
* Żywa komórka z 2 albo 3 żywymi sąsiadami pozostaje żywa.
* Żywa komórka przy innej niż ww. liczbie sąsiadów umiera (z „samotności” albo „zatłoczenia”).
  */
  void progresuj() {
    if (!sf::Keyboard::isKeyPressed(Keyboard::Space)) return; // progres dokonuje się tylko przy wciśniętej spacji
    list<pair<size_t, size_t>> doZmiany;
    for (size_t w = 0; w <= ileY; w++) {
      for (size_t k = 0; k <= ileX; k++) {
        auto zywi = policzZywychSasiadow(w, k);
        if ((plansza[w][k].czyMartwa() and zywi == 3) or
          (plansza[w][k].czyZywa() and (zywi <= 1 or zywi >= 4))) doZmiany.push_back({ w,k });
      }
    }
    for (auto& [w, k] : doZmiany) plansza[w][k].metamorfoza();
  }
};
int main() {
  setlocale(LC_ALL, "");

  program.W->setFramerateLimit(10); // 10 klatek na sekundę
  program.W->setVerticalSyncEnabled(false);
  program.obiekty.push_back(make_shared<Gra>());
  program.start();
}
