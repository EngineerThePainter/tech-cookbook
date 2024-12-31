// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <list>
#include <map>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Paint2D : public Baza {
  CircleShape pedzel;
  list<pair<Vector2f,Color>> narysowane;
  map<Keyboard::Key, Color> kolory = {
    {Keyboard::Num1,Color(255,0,0)},
    {Keyboard::Num2,Color(255,255,0)},
    {Keyboard::Num3,Color(255,0,255)},
    {Keyboard::Num4,Color(0,255,255)},
    {Keyboard::Num5,Color(200,0,200)},
    {Keyboard::Num6,Color(0,200,200)},
    {Keyboard::Num7,Color(200,200,0)},
    {Keyboard::Num8,Color(100,100,100)},
    {Keyboard::Num9,Color(0,0,0)}
  };
  Keyboard::Key klawisz = Keyboard::Num9;
  bool symetria = false;
  RectangleShape osSymetrii;
public:
  Paint2D() {
    pedzel.setRadius(3);
    pedzel.setFillColor(kolory[klawisz]);
    pedzel.setOrigin(2.5,0);

    osSymetrii.setSize(Vector2f(4,HEIGHT));
    osSymetrii.setFillColor(Color(210, 210, 210));
    osSymetrii.setPosition(WIDTH / 2, 0);

    // kontrola zdarzeń
    program.dodaj_test("czyszczenie ekranu",
      [&]() {
        if (program.event.type==Event::MouseButtonPressed and program.event.mouseButton.button == Mouse::Right)
          narysowane.clear();
        return false;
      });
    program.dodaj_test("symetria",
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Tab)
          symetria = bool(!symetria);
        return false;
      });
    program.dodaj_test("zmiany kolorów",
      [&]() {
        for (auto& [k,c] : kolory) {
          if (program.event.type == Event::KeyPressed and program.event.key.code == k) {
            pedzel.setFillColor(c);
            klawisz = k;
            break;
          }
        }          
        return false;
      });
  }
  void rysuj(){
    // oś
    if (symetria) program.W->draw(osSymetrii);
    // pędzelek do podglądu
    program.W->draw(pedzel);
    // istniejące narysowane obszary
    auto pomoc = pedzel.getPosition();
    for (auto& [v,c] : narysowane) {
      pedzel.setPosition(v);
      pedzel.setFillColor(c);
      program.W->draw(pedzel);
    }
    pedzel.setPosition(pomoc);
    pedzel.setFillColor(kolory[klawisz]);
  }
  void progresuj() {
    // pędzel za kursorem
    pedzel.setPosition(Vector2f(Mouse::getPosition(*(program.W))));
    // rysowanie
    if (Mouse::isButtonPressed(Mouse::Left) and !symetria)
      narysowane.push_back({ pedzel.getPosition(),pedzel.getFillColor() });
    else if (Mouse::isButtonPressed(Mouse::Left) and symetria) {
      narysowane.push_back({ pedzel.getPosition(),pedzel.getFillColor() });
      float x = WIDTH/2 +(WIDTH / 2 - pedzel.getPosition().x);
      float y = pedzel.getPosition().y;
      narysowane.push_back({Vector2f(x,y),pedzel.getFillColor()});
    }
  }
};


int main() {
  setlocale(LC_ALL, "");

  program.W->setFramerateLimit(300);
  program.W->setVerticalSyncEnabled(false);

  program.obiekty.push_back(make_shared<Paint2D>());
  program.start();
}
