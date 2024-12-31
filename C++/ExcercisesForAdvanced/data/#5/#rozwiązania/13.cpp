// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr double PI = 3.14159265;
class Pojazd : public Baza, public ConvexShape {  
private:
  Keyboard::Key Lewo;
  Keyboard::Key Prawo;
  Keyboard::Key Ruch;
public:  
  Pojazd(Keyboard::Key wLewo, Keyboard::Key wPrawo, Keyboard::Key wRuch) 
    : Lewo(wLewo), Prawo(wPrawo), Ruch(wRuch), ConvexShape() {    
    setFillColor(Color::Red);
    setPointCount(5);
    setPoint(0, { 0,0 });
    setPoint(1, { 120,0 });
    setPoint(2, { 200,40 });
    setPoint(3, { 120,80 });
    setPoint(4, { 0,80 });
    setOutlineColor(Color::Black);
    setOutlineThickness(3);
    setPosition(500, 500);
    setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);    
  }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {
    if (Keyboard::isKeyPressed(Lewo)) rotate(-2);
    else if (Keyboard::isKeyPressed(Prawo)) rotate(2);
    if (Keyboard::isKeyPressed(Ruch)) {
      float radianyKierunek = PI / 180. * getRotation();
      float nowa_x = 5 * cos(radianyKierunek);
      float nowa_y = 5 * sin(radianyKierunek);           
      move(nowa_x, nowa_y);     
    };
  }
};
int main() {
  setlocale(LC_ALL, "");    
  program.obiekty.push_back(make_shared<Pojazd>(Keyboard::A, Keyboard::D, Keyboard::W));
  program.start();
}
