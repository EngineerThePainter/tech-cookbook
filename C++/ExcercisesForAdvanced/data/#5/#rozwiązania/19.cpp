// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Obiekt : public Baza  {
  CircleShape korpus;
  Clock c;
public:
  Obiekt(float promien) {
    c.restart();
    korpus.setRadius(promien);
    korpus.setOrigin(promien,promien);
    korpus.setPointCount(rand() % 3 + 3);
    korpus.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));    
    korpus.setPosition({ float(rand() % WIDTH), float(rand() % HEIGHT) });
  }
  void rysuj() {
    program.W->draw(korpus);
  }
  void progresuj() {
    auto kursor = Mouse::getPosition(*program.W);
    auto obiekt = korpus.getPosition();
    Vector2f v(kursor.x - obiekt.x, kursor.y - obiekt.y);
    float odleglosc = sqrt(v.x * v.x + v.y * v.y);
    if (odleglosc > 100.) korpus.move(v.x / 10, v.y / 10);
    else if (odleglosc<90) korpus.move(-v.x / 20, -v.y / 20);
 
    if (c.getElapsedTime().asSeconds() > 30) this->skasuj = true;
  }
};

int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  program.dodaj_progres(    
    [&]() {
      if (Mouse::isButtonPressed(Mouse::Left))
        program.obiekty.push_back(make_shared<Obiekt>(rand()%25+10));
    });
  program.dodaj_test("kasuj wszystko",
    []() {
      if (program.event.type == Event::MouseButtonPressed and program.event.mouseButton.button == Mouse::Right) {
        program.obiekty.clear();
      }
      return false;
    });
  
  program.start();
}
