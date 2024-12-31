// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <random>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr double PI = 3.14159265;
// Żółw, Turtle :)
class Dlugopis : public Baza {
  bool podniesiony = true;
  float kierunek = 0;
public:
  VertexArray va;
  Vector2f pozycja{ 0,0 };
  Dlugopis(Vector2f p={0,0}) : pozycja(p) {
    va.setPrimitiveType(sf::Lines); // rysuje po dwa punkty
  }
  void podnies() { podniesiony = true; }
  void opusc() { podniesiony = false; }
  void idz(float ile) {
    float radianyKierunek = PI / 180. * kierunek;
    float nowa_x = ile * cos(radianyKierunek);
    float nowa_y = ile * sin(radianyKierunek);
    if (!podniesiony) {
      va.append(Vertex(Vector2f(pozycja.x,pozycja.y), Color::Black));
      va.append(Vertex(Vector2f(pozycja.x+nowa_x, pozycja.y+nowa_y), Color::Black));
    }
    pozycja.x += nowa_x;
    pozycja.y += nowa_y;
  }
  void lewo(float k) { kierunek -= k; }
  void prawo(float k) { kierunek += k;  }

  void rysuj(){
    program.W->draw(va);
  }
  void progresuj(){}
};

class PlatekKocha : public Baza {
public:
  Dlugopis t;
  PlatekKocha(Vector2f p, float bok = 200, unsigned stopien = 4) {
    t.pozycja = p;
    t.opusc();
    platek(bok, stopien);

  }
  void koch(float bok, unsigned stopien) {        
    if (stopien <= 1) {            
      t.idz(bok);      
    }
    else {
      koch(bok / 3, stopien - 1);
      t.lewo(60);
      koch(bok / 3, stopien - 1);
      t.prawo(120);
      koch(bok / 3, stopien - 1);
      t.lewo(60);
      koch(bok / 3, stopien - 1);
    }
  }
  void platek(float bok, float stopien) {    
    for (unsigned i = 1; i < 4; i++) {
      koch(bok, stopien);
      t.prawo(120);
    }
  }  
  void rysuj() {
    t.rysuj();
  }
  void progresuj() {

  }
};
int main() {
  setlocale(LC_ALL, "");

  auto p1 = make_shared<PlatekKocha>(Vector2f(-100,0), 400, 4);
  auto p2 = make_shared<PlatekKocha>(Vector2f(-400,-300), 400, 3);
  auto p3 = make_shared<PlatekKocha>(Vector2f(-600,100), 400, 2);
  auto p4 = make_shared<PlatekKocha>(Vector2f(200,-300), 400, 5);
  
  
  program.obiekty.push_back(p1);
  program.obiekty.push_back(p2);
  program.obiekty.push_back(p3);
  program.obiekty.push_back(p4);
  // kamera wyśrodkowuje w punkcie 0,0
  program.W->setView(View(Vector2f(0, 0), Vector2f(WIDTH, HEIGHT)));
  program.start();
}
