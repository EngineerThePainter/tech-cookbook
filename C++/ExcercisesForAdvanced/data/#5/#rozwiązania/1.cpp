// main.cpp
#include "Program.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>
#define SLEEP 300
using namespace std;
//////////////////////////////////////////////////////
class Kolo : public Baza, public sf::CircleShape {
public:
  Color org;
  Kolo(float f) : CircleShape(f) {
    org = Color(rand() % 256, rand() % 256, rand() % 256);
    setFillColor(org);
  }
  float r() { return getRadius(); }
  bool operator>(Kolo& inny) {
    return (this->r() > inny.r());
  }
  void zgas() {
    setFillColor(Color(org));
    setOutlineColor(Color::Transparent);
    setOutlineThickness(0);
    setPosition(getPosition().x, 300);
  }
  void zapal() {
    setFillColor(Color(255, 255, 255));
    setOutlineColor(Color(255, 0, 0));
    setOutlineThickness(5);
    setPosition(getPosition().x, 240);
  }
  void progresuj() { }

  void rysuj() {
    Program::W->draw(*this);
  }
};

class SortowanieBabelkowe {
public:
  size_t lewy = 0;
  size_t ostatni = 0;
  bool zmiana = false;
  vector<shared_ptr<Kolo>> do_posortowania;
  SortowanieBabelkowe() {
    vector<float> promienie;
    promienie.reserve(15);
    for (auto p = 10; p <= 100; p += 10) promienie.push_back(p);
    auto ile = rand() % 11 + 10;
    cout << "Sortujemy " << ile << " kółek.\n";
    float xpoz = 100;
    for (auto k = 1; k <= ile; k++) {
      auto r = promienie[rand() % promienie.size()];
      do_posortowania.push_back(make_shared<Kolo>(Kolo(r)));
      do_posortowania.back()->setOrigin(r, r);
      do_posortowania.back()->setPosition(xpoz, 300);
      Program::obiekty.push_back(do_posortowania.back()); // to się będzie rysowało
      xpoz += 100;
    }
    ostatni = do_posortowania.size() - 1;
    program.dodaj_progres(
      [&]() {
        this->krok();
      });
  }
  void krok() {
    for (auto& k : do_posortowania) k->zgas(); // zgaś wszystkie
    if (ostatni == 0) return;
    if (lewy == ostatni) {
      lewy = 0;
      ostatni--;
      sf::sleep(sf::milliseconds(SLEEP));
    }

    auto& k1 = do_posortowania[lewy];
    auto& k2 = do_posortowania[lewy + 1];
    k1->zapal();
    k2->zapal();
    if (lewy < ostatni) {
      if (*k1 > *k2) {
        if (!zmiana) {
          zmiana = true;
          sf::sleep(sf::milliseconds(SLEEP));
          return;
        }
        else zmiana = false;
        auto poz = k1->getPosition();
        k1->setPosition(k2->getPosition());
        k2->setPosition(poz);
        swap(k1, k2);
      }
      lewy++;
    }
    sf::sleep(sf::milliseconds(SLEEP / 2));
  }
};

int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  SortowanieBabelkowe S;
  program.start();
}
