// Pocisk.hpp
#pragma once
#include "Program.hpp"
#include "Pojazd.hpp"
class Pojazd;
inline constexpr double PI = 3.14159265;

class Pocisk : public Baza, public CircleShape {
public:
  unsigned rodzic_nr = 0;
  Pocisk(shared_ptr<Pojazd>);
  void rysuj();
  void progresuj();
};
