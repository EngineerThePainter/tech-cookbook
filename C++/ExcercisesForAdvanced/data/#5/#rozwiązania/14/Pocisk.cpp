// Pocisk.cpp
#include "Program.hpp"
#include "Pocisk.hpp"
#include "Pojazd.hpp"

Pocisk::Pocisk(shared_ptr<Pojazd> r) {
  rodzic_nr = r->nr;
  setRadius(5);
  setFillColor(r->getFillColor());
  setPosition(r->getPosition());
  setOutlineColor(Color::Black);
  setOutlineThickness(2);
  setRotation(r->getRotation());
}
void Pocisk::rysuj() {
  program.W->draw(*this);
}
void Pocisk::progresuj() {
  // Ruch (lewo/prawo/przód)
  float radianyKierunek = PI / 180. * getRotation();
  float nowa_x = 15 * cos(radianyKierunek);
  float nowa_y = 15 * sin(radianyKierunek);
  move(nowa_x, nowa_y);

  // test kolizji
  for (auto& b : program.obiekty) {
    if (typeid(*b) == typeid(Pojazd)) { // kolizja tylko z Pojazdami
      auto pojazd = dynamic_pointer_cast<Pojazd>(b);
      // Kolizja nie jest najdokładniejsza (ograniczam się do obszaru prostokąta okalającego pojazd)
      if (this->rodzic_nr != pojazd->nr and this->getGlobalBounds().intersects(pojazd->getGlobalBounds())) {  
        this->skasuj = true;
        pojazd->trafiony();
      }
    }
  }
  // test wyjścia za ekran
  if (!this->skasuj and this->getPosition().x<0 or this->getPosition().y<0 or this->getPosition().x > WIDTH or
    this->getPosition().y > HEIGHT)
  {
    this->skasuj = true;
  }
}
