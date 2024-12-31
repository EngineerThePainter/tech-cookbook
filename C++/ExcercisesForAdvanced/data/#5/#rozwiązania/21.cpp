// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Obiekt : public Sprite, public Baza {
  Texture tx;
  Image png;
  bool koliduje = false;
public:
  static inline RectangleShape czWspolna;
  Obiekt(string plikPNG, Vector2f pozycja) {
    png.loadFromFile(plikPNG);
    tx.loadFromImage(png);
    setTexture(tx);
    setOrigin(png.getSize().x, png.getSize().y);
    setPosition(pozycja);
  }
  void ustawKolizje(bool v) { koliduje = v; }
  bool czyKoliduje() { return koliduje; }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {}
  IntRect czWspolnaObrazka() {
    IntRect i = IntRect(
      czWspolna.getGlobalBounds().left, czWspolna.getGlobalBounds().top,  // lewy,górny
      czWspolna.getGlobalBounds().width, czWspolna.getGlobalBounds().height); // szer, wys
    auto prawy_dolny_obrazka = Vector2i(getPosition());
    int x = prawy_dolny_obrazka.x - i.left;
    int y = prawy_dolny_obrazka.y - i.top;
    // punkt startx piksela wewnątrz obrazka to lewy górny róg części wspólnej
    int startx = png.getSize().x - x;
    int starty = png.getSize().y - y;
    return { startx , starty , i.width, i.height };
  }
  // test kolizji dla operatora ==
  bool operator==(Obiekt& o) {
    FloatRect cz_wspolna;
    if (!getGlobalBounds().intersects(o.getGlobalBounds(), cz_wspolna)) {
      czWspolna.setPosition(0,0);
      czWspolna.setSize({ 0,0 });
      return false; // niemożliwa kolizja
    }
    else {
      // x, y lewy górny róg obszaru wspólnego
      float x = cz_wspolna.left; 
      float y = cz_wspolna.top;
      // szer, wys rozmiar obszaru wspólnego
      float szer = cz_wspolna.width;
      float wys = cz_wspolna.height;
      // rysujemy obszar wspólny
      czWspolna.setPosition(x, y);
      czWspolna.setSize({ szer,wys });      
      
      auto piksele = czWspolnaObrazka();
      auto piksele_o = o.czWspolnaObrazka();      
      for (int pozx = piksele.left, pozx_o = piksele_o.left; pozx < piksele.width + piksele.left -1; pozx++, pozx_o++) {
        for (int pozy = piksele.top, pozy_o = piksele_o.top; pozy < piksele.height + piksele.top -1; pozy++, pozy_o++) {
          // punkty leżące na sobie NIE są przeźroczyste (oba są widoczne i ich przeźroczystość nie jest pełna)
          if (png.getPixel(pozx, pozy).a != 0 and o.png.getPixel(pozx_o, pozy_o).a != 0) {
            this->ustawKolizje(true);
            o.ustawKolizje(true);
            return true; // kolizja
          }
        }
      }      
      return false; // nie kolidują żadne piksele nieprzeźroczyste
    }
  }
};
int main() {
  setlocale(LC_ALL, "");

  Obiekt::czWspolna.setFillColor(Color(255,255,0,75));
  program.dodaj_rysowanie(
    []() {
      program.W->draw(Obiekt::czWspolna);
    });

  shared_ptr<Obiekt> o1 = make_shared<Obiekt>("21_obrazek_1.png", Vector2f(WIDTH / 4, HEIGHT / 3));
  program.obiekty.push_back(o1);
  shared_ptr<Obiekt> o2 = make_shared<Obiekt>("21_obrazek_2.png", Vector2f(WIDTH / 2, HEIGHT / 2));
  program.obiekty.push_back(o2);
  program.dodaj_progres(
    [&o2,&o1]() {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        o2->setPosition(Vector2f(Mouse::getPosition(*program.W)));
        o2->czWspolnaObrazka();
      }
      if (*o1 == *o2) {
        Obiekt::czWspolna.setFillColor(Color(255, 0, 0, 75));
      } else Obiekt::czWspolna.setFillColor(Color(255, 255, 0, 75));
    });
  program.start();
}
