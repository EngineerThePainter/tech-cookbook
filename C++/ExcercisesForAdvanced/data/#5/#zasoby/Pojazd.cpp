// Pojazd.cpp
#include "Program.hpp"
#include "Pojazd.hpp"
#include "Pocisk.hpp"

Pojazd::Pojazd(Keyboard::Key wLewo, Keyboard::Key wPrawo, Keyboard::Key wRuch, Color k)
  : Lewo(wLewo), Prawo(wPrawo), Ruch(wRuch), kolor(k), ConvexShape() {
  nr = NR++;
  setFillColor(kolor);
  setPointCount(5);
  setPoint(0, { 0,0 });
  setPoint(1, { 120,0 });
  setPoint(2, { 200,40 });
  setPoint(3, { 120,80 });
  setPoint(4, { 0,80 });
  setOutlineColor(Color::Black);
  setOutlineThickness(3);
  setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
  if (nr == 1) setPosition(100, 500);
  else {
    setPosition(1700, 500); rotate(180);
  }

  program.dodaj_test("strzelanie" + to_string(this->nr),
    [&]() {
      if (!ruszanie) return true;
      if (this->nr == 1 and program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Space) {
        program.obiekty.push_back(make_shared<Pocisk>(shared_from_this()));
      }
      if (this->nr == 2 and program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::RShift) {
        program.obiekty.push_back(make_shared<Pocisk>(shared_from_this()));
      }
      return false;
    });
}
void Pojazd::rysuj() {
  program.W->draw(*this);
}
void Pojazd::progresuj() {
  if (!ruszanie) return;
  // ruch (lewo/prawo/przód)
  if (Keyboard::isKeyPressed(Lewo)) rotate(-2);
  else if (Keyboard::isKeyPressed(Prawo)) rotate(2);
  if (Keyboard::isKeyPressed(Ruch)) {
    float radianyKierunek = PI / 180. * getRotation();
    float nowa_x = 5 * cos(radianyKierunek);
    float nowa_y = 5 * sin(radianyKierunek);
    move(nowa_x, nowa_y);
  };
}

void Pojazd::trafiony() {
  if (maksymalne_trafienia > 0) maksymalne_trafienia--;
  else ruszanie = false; // przegra³
}
