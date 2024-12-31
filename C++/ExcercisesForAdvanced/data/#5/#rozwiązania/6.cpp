// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <random>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
default_random_engine rng;
uniform_real_distribution<float> podajnik(0, 360);
uniform_real_distribution<float> losowa_pozycja(-HEIGHT / 2.2, HEIGHT / 2.2);
uniform_real_distribution<float> losowy_promien(10, 30);
constexpr double PI = 3.14159265;
class Czasteczka : public Baza, public enable_shared_from_this<Czasteczka> {
public:
  inline static unsigned nr = 0;
  unsigned id = 0;
  float ruch = 1;
  CircleShape k;
  Czasteczka() {}
  Czasteczka(float promien) {
    id = ++nr;
    k.setRadius(promien);
    k.setFillColor(Color::Black);
    k.setOrigin(promien / 2, promien / 2);    
  }
  void rysuj() {
    program.W->draw(k);
  }
  void progresuj() {
    if (this->skasuj) return;

    float kierunek = podajnik(rng);
    float radianyKierunek = PI / 180. * kierunek;
    float nowa_x = ruch * cos(radianyKierunek);
    float nowa_y = ruch * -sin(radianyKierunek);
    k.move(nowa_x, nowa_y);
    
    shared_ptr<Czasteczka> ta = shared_from_this();
    bool kolizja = false;
    for (auto& cz : program.obiekty) {
      if (ta.get() == cz.get()) continue;
      auto czasteczka = dynamic_pointer_cast<Czasteczka>(cz);
      if (*czasteczka == *ta) {
        czasteczka->skasuj = true;
        kolizja = true;
      }
    }
    if (kolizja) ta->skasuj = true;

  }
  bool operator==(Czasteczka& inne) {
    // √((x_2-x_1)²+(y_2-y_1)²)  (odległość dwóch punktów na płaszczyźnie)
    auto x2 = inne.k.getPosition().x;
    auto x1 = k.getPosition().x;
    auto y2 = -inne.k.getPosition().y;
    auto y1 = -k.getPosition().y;
    auto odleglosc = sqrt(abs((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
    return (odleglosc - (k.getRadius() + inne.k.getRadius()) < 0.f);
  }
};

class Symulacja {
public:
  Symulacja(unsigned ile) {
    for (unsigned i = 1; i <= ile;) {
      auto nowa = make_shared<Czasteczka>(losowy_promien(rng));
      while (true) {
        nowa->k.setPosition(losowa_pozycja(rng), losowa_pozycja(rng));
        bool kolizja = false;
        for (auto& stara : program.obiekty) {
          auto s = static_pointer_cast<Czasteczka>(stara);
          if (nowa->k.getGlobalBounds().intersects(s->k.getGlobalBounds())) {
            kolizja = true;
            break;
          }
        }
        if (!kolizja) {
          program.obiekty.push_back(nowa);
          i++;
          break;
        }
      }
    }
  }
};
int main() {
  setlocale(LC_ALL, "");
  program.W->setView(View(Vector2f(0, 0), Vector2f(WIDTH, HEIGHT))); // Kamera wyśrodkowuje w punkcie 0,0  
  Symulacja(50);
  program.start();
}
