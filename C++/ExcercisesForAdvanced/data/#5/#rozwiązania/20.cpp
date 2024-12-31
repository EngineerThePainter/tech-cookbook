// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////

int main() {
  setlocale(LC_ALL, "");
  Image image;
  image.loadFromFile("20_grafika.png");
  auto [szer, wys] = image.getSize();
  for (unsigned i = 0; i < szer; i++) {
    for (unsigned j = 0; j < wys; j++) {
      auto c = image.getPixel(i, j);
      if (c.r < 100) image.setPixel(i, j, Color(0, c.g, c.b));
      else image.setPixel(i, j, Color(255, c.g, c.b));
    }
  }
  image.saveToFile("20_grafika_rozwiazanie.png");
}
