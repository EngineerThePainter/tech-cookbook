// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
//////////////////////////////////////////////////////
class Kolo : public Baza {
public:
  CircleShape kolo;
  float kat;
  Kolo(float promien, float k) : kat(k) {
    kolo.setRadius(promien);
    kolo.setFillColor(Color::Black);
  }
  void rysuj() {
    if (program.klatkiDoKonca()==1) kolo.setFillColor(Color::Red);
    program.W->draw(kolo);
  }
  void progresuj() {    
    float katRad = (3.14159265 / 180.) * (kat - 90);
    float celx = 1 * cos(katRad); // bo prędkość kół to 10/s (1 na 1/10 sekundy)
    float cely = 1 * -sin(katRad);
    kolo.move(celx, -cely);
  }

  // są 'równe', gdy kolidują
  bool operator==(Kolo& k) {
    // √((x_2-x_1)²+(y_2-y_1)²)  (odległość dwóch punktów na płaszczyźnie)
    auto x2 = k.kolo.getPosition().x;
    auto x1 = kolo.getPosition().x;
    auto y2 = -k.kolo.getPosition().y;
    auto y1 = -kolo.getPosition().y;
    auto odleglosc = sqrt(abs((x2 - x1) * (x2 - x1) + (-y2 + y1) * (-y2 + y1)));
    return (odleglosc - (kolo.getRadius() + k.kolo.getRadius()) < 0.f);
  }
};
class Symulacja {
public:
  Symulacja() {
    ifstream dane("4_pozycje.txt");
    float x, y, promien, kat;
    while (dane >> x >> y >> promien >> kat) {
      auto k = make_shared<Kolo>(Kolo(promien, kat));
      k->kolo.setOrigin(promien, promien);
      k->kolo.setPosition(x, -y);
      program.obiekty.push_back(k);
    }
    cout << "Załadowano " << program.obiekty.size() << " obiektów.\n";
    dane.close();
  }
  void progresuj() {    
    for (auto it = program.obiekty.begin(); it != program.obiekty.end(); it++) {
      for (auto it2 = program.obiekty.begin(); it2 != program.obiekty.end(); it2++) {
        if (it != it2) {
          auto k1 = dynamic_pointer_cast<Kolo>(*it);
          auto k2 = dynamic_pointer_cast<Kolo>(*it2);
          if (*k1 == *k2) { // kolizja
            k1->skasuj = k2->skasuj = true;
          }
        }
      }
    }
    cout << "Zostało obiektów: " << program.obiekty.size() << endl;
  }
};
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  // ustaw kamerę na punkcie 0,0  
  program.pokazCzas = false;
  program.W->setView(View(Vector2f(0, 0), Vector2f(WIDTH, HEIGHT)));  
  // w każdej klatce koła ruszają się o 1, zatem przy prędkości 10/s
  // 10 klatek symuluje upływ czasu równy 1 sekundę
  program.ustawKlatki(10 * 30); // 300 klatek symuluje 30 sekund
  Symulacja S;
  program.dodaj_progres([&S]() { S.progresuj();  });
  program.start();
  // po wyjściu z okna graficznego zobaczymy, ile kół pozostało
  cout << "Zostało " << program.obiekty.size() << endl;
}
