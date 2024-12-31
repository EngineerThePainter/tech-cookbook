// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////
double Horner(vector<double> wspolczynniki, double x) {
  if (wspolczynniki.size() == 1) return wspolczynniki.front();
  vector<double> kopia = wspolczynniki;
  auto ostatni = kopia.back();
  kopia.pop_back();
  return x * Horner(kopia, x) + ostatni;
}
class Wielomian : public Baza {
public:
  vector<double> wspolczynniki;  
  double x0=0; 
  double x1=0; // x0 : x1 -> zakres
  VertexArray va;
  RectangleShape osX;
  RectangleShape osY;
  Color c = Color::Black;  
  Wielomian(vector<double>wsp,double zakres_x0, double zakres_x1) : 
    wspolczynniki(wsp), x0(zakres_x0), x1(zakres_x1) {
    va.resize(abs(x1 - x0) + 1);
    va.setPrimitiveType(PrimitiveType::LineStrip);
    for (unsigned long long int poz = 0; poz < va.getVertexCount(); poz++) {
      va[poz].color = Color::Black;
      va[poz].position = Vector2f(x0,-Horner(wspolczynniki, x0));
      x0 += 1.;
    }
    osX.setFillColor(Color::Red);
    osX.setSize(Vector2f(WIDTH, 2));
    osX.setOrigin(Vector2f(WIDTH / 2, 1));
    osX.setPosition(0, 0);

    osY.setFillColor(Color::Red);
    osY.setSize(Vector2f(2,HEIGHT));
    osY.setOrigin(Vector2f(1,HEIGHT/2));
    osY.setPosition(0, 0);
  }
  auto&& ustawKolor(Color color) { 
    c = color; 
    for (auto poz = 0; poz < va.getVertexCount(); poz++) {
      va[poz].color = c;
    }
    return *this;
  }
  void rysuj() {
    program.W->draw(osX);
    program.W->draw(osY);
    program.W->draw(va);
    // dla pogrubienia va jego kopia "piksel niżej"
    auto vacopy = va;
    for (auto p = 0 ; p<vacopy.getVertexCount() ; p++ ) {
      vacopy[p].position = Vector2f(vacopy[p].position.x, vacopy[p].position.y + 1);
    }
    program.W->draw(vacopy);
  }
  void progresuj() {}
};
int main() {
  setlocale(LC_ALL, "");
  
  program.W->setView(View(Vector2f(0, 0),Vector2f(WIDTH,HEIGHT)));  
  
  program.obiekty.push_back(make_shared<Wielomian>(
    Wielomian({ -1,120 }, -500, 500).ustawKolor(Color::Black)
  ));
  program.obiekty.push_back(make_shared<Wielomian>(
    Wielomian({ 0.1,-4,-44 }, -500, 500).ustawKolor(Color::Magenta)
  ));
  program.obiekty.push_back(make_shared<Wielomian>(
    Wielomian({ 0.05, .5, -2, -140 }, -500, 500).ustawKolor(Color::Green)
  ));
  
  program.start();
}
