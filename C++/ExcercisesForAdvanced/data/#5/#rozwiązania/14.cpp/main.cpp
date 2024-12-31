// main.cpp
#include "Program.hpp" // dostępny na początku rozwiązań do części #5
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Pocisk.hpp"
#include "Pojazd.hpp"
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
int main() {
  setlocale(LC_ALL, "");
  // Gracz-Pojazd 1
  program.obiekty.push_back(make_shared<Pojazd>(Keyboard::A, Keyboard::D, Keyboard::W, Color::Blue));
  // Gracz-Pojazd 2
  program.obiekty.push_back(make_shared<Pojazd>(Keyboard::Left, Keyboard::Right, Keyboard::Up));

  program.start();
}
