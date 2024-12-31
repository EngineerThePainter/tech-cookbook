// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <chrono>
#include <format>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr double PI = 3.14159265;
class Zegar : public Baza {  
  CircleShape tarcza;
  vector<Text> godziny;
  vector<RectangleShape> kreskiMS; // kreseczki minut/sekund
  RectangleShape wskazowkaG; // godziny
  RectangleShape wskazowkaM; // minuty
  RectangleShape wskazowkaS; // sekundy
  Vector2f centrum; // pozycja centrum zegara
  float promien = HEIGHT / 2 - 20; // rozmiar zegara
public:
  Zegar() {
    centrum = { WIDTH / 2, HEIGHT / 2 };
    // tarcza
    tarcza.setFillColor(Color::Yellow);
    tarcza.setOutlineColor(Color::Black);
    tarcza.setOutlineThickness(2);
    tarcza.setRadius(promien);
    tarcza.setOrigin(promien, promien);
    tarcza.setPosition(centrum);
    tarcza.setPointCount(360); // bardziej koliste koło
    // godziny Text
    godziny.resize(12);
    for (int godz = 1; auto & t : godziny) {
      t.setCharacterSize(promien / 10);
      t.setFillColor(Color::Black);
      t.setFont(program.czcionka);
      t.setString(to_string(godz));
      t.setPosition(centrum);
      t.setOrigin(t.getGlobalBounds().width / 2, t.getGlobalBounds().height);
      // początkowy kąt obiektów w SFML to 0 i jest to kierunek "w prawo", -90 to "do góry"
      float kat = -90 + godz * 30;
      t.move(ruszWKierunku(kat, promien / 1.1));
      godz++;
    }
    // kreskiMS
    kreskiMS.resize(5 * 12);
    for (int ms = 1; auto & r : kreskiMS) {
      if (ms % 5 == 0) {
        r.setSize({ 6, 40 });
        r.setFillColor(Color::Magenta);
      }
      else {
        r.setSize({ 2,40 });        
        r.setFillColor(Color::Black);
      }
      r.setOrigin(r.getSize().x/2, 0);     
      r.setPosition(centrum);
      float kat = -90 + ms * 30 / 5.;
      r.rotate(ms * 30 / 5.);
      r.move(ruszWKierunku(kat, promien / 1.2));
      ms++;
    }
    // wskazówka minut
    wskazowkaM.setSize({ 4,promien * .8f });
    wskazowkaM.setOrigin({ 2, promien * .8f });
    wskazowkaM.setFillColor(Color(100, 100, 110));
    wskazowkaM.setPosition(centrum);
    // wskazówka sekund
    wskazowkaS.setSize({ 2,promien * .9f });
    wskazowkaS.setOrigin({ 1, promien * .9f });
    wskazowkaS.setFillColor(Color(255, 60, 60));
    wskazowkaS.setPosition(centrum);
    // wskazówka godzin
    wskazowkaG.setSize({ 10,promien * .6f });
    wskazowkaG.setOrigin({ 5, promien * .6f });
    wskazowkaG.setFillColor(Color(60, 80, 60));
    wskazowkaG.setPosition(centrum);
  }
  Vector2f ruszWKierunku(float kat, float dlugosc) {
    float radianyKierunek = PI / 180. * kat;
    float nowa_x = dlugosc * cos(radianyKierunek);
    float nowa_y = dlugosc * sin(radianyKierunek);
    return { nowa_x, nowa_y };
  }
  void rysuj() {
    program.W->draw(tarcza);
    for (auto& t : godziny)
      program.W->draw(t);
    for (auto& r : kreskiMS)
      program.W->draw(r);
    program.W->draw(wskazowkaG);
    program.W->draw(wskazowkaM);
    program.W->draw(wskazowkaS);
  }
  void progresuj() {    
    auto czas = chrono::current_zone()->to_local(chrono::system_clock::now());
    float godz = stof(format("{:%I}", czas));    
    wskazowkaG.setRotation((godz * 5 * 30 / 5.));
    float min = stof(format("{:%M}", czas));
    wskazowkaM.setRotation((min * 30 / 5.));
    float sek = stof(format("{:%S}", czas));
    wskazowkaS.setRotation((sek*30/5.));       
  }

};
int main() {
  setlocale(LC_ALL, "");
  program.obiekty.push_back(make_shared<Zegar>());
  program.start();
}
