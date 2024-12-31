// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Labirynt : public Sprite, public Baza {
  Texture tx;
  Image i;
public:
  Labirynt() :Sprite() {
    i.loadFromFile("23_labirynt.png");
    tx.loadFromImage(i);
    setTexture(tx);
  }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {}
  // klasa zaprzyjaźniona
  friend class Gracz;
  // sekcja private Labiryntu będzie dostępna dla metod klasy Gracz
};
class Gracz : public Baza {
  bool ruch = false;
  CircleShape korpus;
  shared_ptr<Labirynt> lab;
  bool koniec = false; // czy doszedł do czerwonego
  Text czasTxt; // upływ czasu
  Clock zegar;
  bool czasPlynie = true;
public:
  Gracz(shared_ptr<Labirynt> l) : lab(l) {
    // korpus gracza
    korpus.setRadius(3);
    korpus.setFillColor(Color(100, 110, 164));
    korpus.setOrigin(3, 3);
    korpus.setPosition(50, 50);
    korpus.setOutlineColor(Color::Red);
    korpus.setOutlineThickness(1);
    // ustawienie zegara
    zegar.restart();
    czasTxt.setFillColor(Color(255, 150, 150, 200));
    czasTxt.setPosition(WIDTH / 4, HEIGHT - 40);
    czasTxt.setFont(program.czcionka);

    program.dodaj_test("aktywacja ruchu",
      [this]() {
        if (program.event.type == Event::MouseButtonPressed and program.event.mouseButton.button == Mouse::Left) {
          ustawRuch(true);
        }
        if (program.event.type == Event::MouseButtonReleased and program.event.mouseButton.button == Mouse::Left) {
          ustawRuch(false);
        }
        return false;
      });
  }
  void ustawRuch(bool wartosc) { ruch = wartosc; }
  bool czyRuch() { return ruch; }

  void rysuj() {

    program.W->draw(czasTxt);
    program.W->draw(korpus);
  }

  void progresuj() {
    // aktualizacja czasu
    if (czasPlynie)
      czasTxt.setString(to_string(zegar.getElapsedTime().asMilliseconds() / 1000.) + " sek.");

    // test kolizji ze ścianami
    Vector2i pozycja = Vector2i(korpus.getPosition());
    // ponieważ lewy górny róg obrazu PNG labiryntu pokrywa się z punktem 0,0 lewego górnego punktu ekranu,
    // mogę pozycję gracza traktować jak współrzędne pikseli obrazu labiryntu
    for (int x=pozycja.x-1-3; x<=pozycja.x-1+3; x++ )
      for (int y = pozycja.y - 1 - 3; y <= pozycja.y - 1 + 3; y++)         
      {
        // kolor piksela obrazka, który przykrywa korpus gracza
        Color c = lab->i.getPixel(x, y); 
        if (c == Color::Red) { // na końcu
          czasPlynie = false;
        }
        else if (c == Color::Green) {} // na starcie
        else if (c == Color::Black) { // ściana!
          korpus.setPosition(50, 50);
          ustawRuch(false);
        }
      }
    // przesuwanie
    if (czyRuch() and czasPlynie) {
      auto x = Vector2f(Mouse::getPosition(*program.W)).x - korpus.getPosition().x;
      auto y = Vector2f(Mouse::getPosition(*program.W)).y - korpus.getPosition().y;
      korpus.move( x / 24., y / 24.);
    }
  }
};
int main() {
  setlocale(LC_ALL, "");
  shared_ptr<Labirynt> lab = make_shared<Labirynt>();
  program.obiekty.push_back(lab);
  program.obiekty.push_back(make_shared<Gracz>(lab));
  program.pokazCzas = false;
  program.start();
}
