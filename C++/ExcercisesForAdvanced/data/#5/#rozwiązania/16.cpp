// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <list>
#include <map>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr unsigned n = 50;
constexpr float R = 360. / (n+1.);
constexpr double PI = 3.14159265;
/* 
Funkcja dalej() pozwoli cyklicznie przechodzić po iteratorach kontenerów.
Założenia: 
- iterator kontenera może wykonać operację iterator++
- obiekt w kontenerze posiada funkcję czyZyje(). Chcemy bowiem przesuwać się 
o k-pozycji, uwzględniając tylko 'żywe' obiekty.
*/ 
template <typename KONTENER, typename ITERATOR>
ITERATOR dalej(KONTENER& kontener, ITERATOR it, unsigned oIle = 1) {    
  while (it != kontener.end() and oIle--) {    
    it++;
    if (it == kontener.end()) it = kontener.begin();
    if (it->czyZyje() == false) oIle++;
  }
  return it;
}

class Obiekt : public CircleShape {  
  bool zyje = true;
  float kat = 0; // kąt obrotu przy malowaniu
public:
  inline static unsigned NR = 1;  
  unsigned nr;
  Text nrtxt;  
  Obiekt(float r) : CircleShape(r) {
    nr = NR++;
    setFillColor(Color(nr * 5, 255, nr * 5));
    setOrigin(r, r);
    setOutlineColor(Color::Black);
    setOutlineThickness(2);
    setPosition(WIDTH/2, HEIGHT/2);    
    kat = nr * R;
    rotate(kat);
    float radianyKierunek = PI / 180. * getRotation();
    float nowa_x = HEIGHT/2.5 * cos(radianyKierunek);
    float nowa_y = HEIGHT/2.5 * sin(radianyKierunek);
    move(nowa_x, nowa_y);

    nrtxt.setFont(program.czcionka);
    nrtxt.setString(to_string(nr));
    nrtxt.setFillColor(Color::Red);
    nrtxt.setPosition(getPosition());
    nrtxt.setCharacterSize(12);
    nrtxt.setOrigin(6, 6);
  }
  bool czyZyje() { return zyje; }
  void zabij() {
    zyje = false;
    setFillColor(Color(45, 45, 45));
    nrtxt.setFillColor(Color::White);
    setOutlineColor(Color(100,100,100));
  }
  void ozyw() {
    zyje = true;
    setFillColor(Color(nr * 5, 255, nr * 5));
    nrtxt.setFillColor(Color::Red);
    setOutlineColor(Color::Black);
  }
  void rysuj() {
    program.W->draw(*this);
    program.W->draw(this->nrtxt);
  }
};

class Flawiusz : public Baza {
private:  
  unsigned zywi = n;
  unsigned k = 2; // co k  
public:
  list<Obiekt> obiekty;
  list<Obiekt>::iterator aktywny;
  Flawiusz(unsigned ustawk=2) : k(ustawk){
    for (unsigned i = 1; i <= n; i++) {
      obiekty.push_back(Obiekt(20));
    }
    aktywny = obiekty.end();
    program.dodaj_test("resetowanie_2", 
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Num2) {
          reset(2);
        }        
        return false;
      });
    program.dodaj_test("resetowanie_3",
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Num3) {
          reset(3);
        }
        return false;
      });
    program.dodaj_test("resetowanie_4",
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Num4) {
          reset(4);
        }
        return false;
      });
    program.dodaj_test("resetowanie_5",
      [&]() {
        if (program.event.type == Event::KeyPressed and program.event.key.code == Keyboard::Num5) {
          reset(5);
        }
        return false;
      });
  }

  void rysuj() {
    for (auto& e : obiekty) {
      e.rysuj();
    }
  }
  void progresuj() {
    usun();
  }
  bool usun() {
    if (zywi > 1) {
      if (aktywny == obiekty.end()) {        
        aktywny = dalej(obiekty, obiekty.begin(), k - 1);
      }
      else {
        aktywny = dalej(obiekty, aktywny, k);
      }
      aktywny->zabij();
      zywi--;
      return true;
    }
    return false;
  }
  void reset(unsigned noweK) {
    k = noweK;
    zywi = 0;
    for (auto& o : obiekty) {
      o.ozyw();
      zywi++;
    }
    aktywny = obiekty.end();
  }
};
int main() {
  setlocale(LC_ALL, "");
  program.obiekty.push_back(make_shared<Flawiusz>(2));
  program.W->setFramerateLimit(3); // 3 klatki na sekundę
  program.W->setVerticalSyncEnabled(false);
  program.start();
}
