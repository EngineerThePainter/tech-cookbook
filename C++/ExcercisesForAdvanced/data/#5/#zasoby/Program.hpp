// Program.hpp
#pragma once // gwarancja za³adowania jeden raz
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <list>
#include <iostream>
#include <typeinfo>
#define WIDTH 1920
#define HEIGHT 1080
#define FRAMELIMIT 60
using namespace std;
using namespace sf;
class mWindow : public RenderWindow {
public:
  mWindow() : RenderWindow(VideoMode(WIDTH, HEIGHT), L"SFML") {
    this->setPosition(Vector2i(0, 0));
    this->setKeyRepeatEnabled(false);
    this->setVerticalSyncEnabled(true);
  };
};
class Baza {
public:
  bool skasuj = false;
  virtual void progresuj() = 0;
  virtual void rysuj() = 0;
};

class Program {
public:
  inline static shared_ptr<mWindow> W = make_shared<mWindow>();
  inline static Event event;
  inline static list<shared_ptr<Baza>> obiekty;
  sf::Font czcionka;
  View kamera; // niekiedy chcemy innej kamery ni¿ domyœlna
  bool pokazCzas = true;
private:
  bool pauza = false;
  unsigned long long int pauzaPoMilisekundach = 0;  // po ilu milisekundach Pauza
  unsigned long long int pauzaPoKlatkach = 0; // po ilu klatkach Pauza
  sf::Clock zegar;
  sf::Text uplywCzasu;
  map <string, function<bool(void)>> testy = {
    {
      "zamkniêcie okna",
      [&]() {
          if (event.type == Event::Closed or
            event.type == Event::KeyPressed and event.key.code == Keyboard::Escape)
              W->close();
          return false;
      }
    }
  };
  list <function<void(void)>> progresy;
  list <function<void(void)>> rysowanie;
  list <function<void(void)>> progresy_po;
public:
  Program() {
    czcionka.loadFromFile("arial.ttf");
    uplywCzasu.setFont(czcionka);
    uplywCzasu.setCharacterSize(30);
    uplywCzasu.setFillColor(Color::Magenta);
    uplywCzasu.setOutlineColor(Color::Green);
    uplywCzasu.setOutlineThickness(1);
    uplywCzasu.setString("czas");
    uplywCzasu.setStyle(Text::Italic);
    kamera.setSize({ WIDTH,HEIGHT });
  }
  // g³ówna metoda uruchamiaj¹ca pêtlê rysuj¹c¹ kolejne klatki
  void start() {
    zegar.restart();
    while (W->isOpen())
    {
      testyWydarzen();
      W->clear(Color::White);

      if (!czyPauza())
        for (auto& o : obiekty) {
          o->progresuj();
        }
      if (!czyPauza()) progresja();

      for (auto& o : obiekty) {
        o->rysuj();
      }
      rysuj();
      rysujUplywCzasu();

      if (!czyPauza()) progresja_po();

      W->display();

      if (pauzaPoMilisekundach != 0 and zegar.getElapsedTime().asMilliseconds() > pauzaPoMilisekundach)
        pauza = true;

      if (!pauza and pauzaPoKlatkach > 0) {
        pauzaPoKlatkach--;
        if (pauzaPoKlatkach == 0) pauza = true;
      }

      for (auto it = obiekty.begin(); it != obiekty.end();) {
        if ((*it)->skasuj) {
          it = obiekty.erase(it);
        }
        else it++;
      }      
    }
  }
  // rysuje up³yw czasu w oknie 2D
  void rysujUplywCzasu() {
    uplywCzasu.setPosition(W->getView().getCenter().x + WIDTH / 3, W->getView().getCenter().y - HEIGHT / 2 + 40);
    uplywCzasu.setString(to_string(zegar.getElapsedTime().asMilliseconds()) + " milisek.");
    if (pokazCzas) W->draw(uplywCzasu);
  }
  template <typename T>
  // ustawia œrodowisko w tryb PAUZY (bool) lub pauzuje po up³ywie pewnego czasu w ms
  void ustawPauze(T parametr) {
    if (is_same_v<T, bool>) pauza = parametr;
    else pauzaPoMilisekundach = parametr;
  }
  // po ilu wyœwietlonych klatkach ma byæ w³¹czona pauza
  void ustawKlatki(unsigned long long int k) { pauzaPoKlatkach = k; }
  // ile klatek zosta³o do pauzy
  unsigned long long int klatkiDoKonca() { return pauzaPoKlatkach; }
  // test czy jest pauza
  bool czyPauza() { return pauza; }
  // dodawanie funkcji wykonuj¹cych progres obiektów (zmiany stanów, np. ruch, pozycjê, wielkoœci)
  void dodaj_progres(function<void(void)>&& funkcja) {
    progresy.push_back(funkcja);
  }
  // dodawanie funkcji wykonuj¹cych progres obiektów (zmiany stanów, np. ruch, pozycjê, wielkoœci)
  void dodaj_progres_po(function<void(void)>&& funkcja) {
    progresy_po.push_back(funkcja);
  }
  // dodawanie funkcji rysuj¹cych
  void dodaj_rysowanie(function<void(void)>&& funkcja) {
    rysowanie.push_back(funkcja);
  }
  // dodawanie funkcji zwi¹zanych z obs³ug¹ zdarzeñ
  void dodaj_test(string klucz, function<bool(void)>&& funkcja) {
    testy[klucz] = funkcja;
  }
  // uruchamianie funkcji rysowania
  void rysuj() {
    for (auto& f : rysowanie) f();
  }
  // uruchamianie funkcji progresji
  void progresja() {
    for (auto& f : progresy) f();
  }
  // uruchamianie funkcji progresji
  void progresja_po() {
    for (auto& f : progresy_po) f();
  }
  // przechwytywanie i obs³uga wydarzeñ w oknie
  void testyWydarzen() {
    while (Program::W->pollEvent(Program::event)) {
      for (auto it = testy.begin(); it != testy.end(); ) {
        if (it->second()) it = testy.erase(it);
        else it++;
      }
      // pauza po wciœniêciu p
      if (Program::event.type == Event::KeyPressed and event.key.code == Keyboard::P) pauza = !pauza;
    }
  }
};
inline Program program;
