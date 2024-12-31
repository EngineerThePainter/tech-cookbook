// Pojazd.hpp
#pragma once
#include "Program.hpp"
#include "Pocisk.hpp"

class Pojazd : public enable_shared_from_this<Pojazd>, public Baza, public ConvexShape {
private:
  Keyboard::Key Lewo;
  Keyboard::Key Prawo;
  Keyboard::Key Ruch;
  Color kolor;
  unsigned maksymalne_trafienia = 10; // tyle wytrzyma, potem siê nie rusza
  bool ruszanie = true;
public:
  inline static unsigned NR = 1;
  unsigned nr;
  Pojazd(Keyboard::Key wLewo, Keyboard::Key wPrawo, Keyboard::Key wRuch, Color k = Color::Red);
  void rysuj();
  void progresuj();
  void trafiony();
};
