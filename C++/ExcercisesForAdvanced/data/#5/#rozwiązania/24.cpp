// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>
#include <list>
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
    move(WIDTH / 2, 0);
    program.W->draw(*this);
    move(-WIDTH / 2, 0);
  }
  void progresuj() {}
  // klasa zaprzyjaźniona
  friend class Gracz;
  // sekcja private Labiryntu będzie dostępna dla metod klasy Gracz
};
class Gracz : public Baza {
  bool ruch = false;
  CircleShape korpus;
  CircleShape korpusWroga;
  shared_ptr<Labirynt> lab;
  bool koniec = false; // czy doszedł do czerwonego
  Text czasTxt; // upływ czasu
  Clock zegar;
  bool czasPlynie = false;
  Vector2f pozycjaWroga;
public:
  TcpSocket polaczenie;
  Packet p;
  Gracz(shared_ptr<Labirynt> l) : lab(l) {
    // połączenie z serwerem
    polaczenie.setBlocking(true);
    if (polaczenie.connect("127.0.0.1", 55555) != Socket::Done) {
      cout << "Błąd połączenia.\n";
    }
    // korpus gracza
    korpus.setRadius(3);
    korpus.setFillColor(Color(100, 110, 164));
    korpus.setOrigin(3, 3);
    korpus.setPosition(50, 50);
    korpus.setOutlineColor(Color::Red);
    korpus.setOutlineThickness(1);
    korpusWroga = korpus;
    korpusWroga.setFillColor(Color::Red);
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
    program.W->draw(korpusWroga);
  }

  void progresuj() {
    // odbieranie i wysyłanie
    p.clear();
    float odebraneX, odebraneY;
    if (polaczenie.receive(p) == Socket::Done) {
      p >> odebraneX >> odebraneY;
      pozycjaWroga = { odebraneX, odebraneY };
      if (odebraneX < 1 and odebraneY < 1) czasPlynie = true;
      korpusWroga.setPosition(pozycjaWroga.x + WIDTH / 2, pozycjaWroga.y);
    }
    // wysyłanie, o ile wystartowano
    if (czasPlynie) {
      p.clear();
      p << korpus.getPosition().x << korpus.getPosition().y;
      if (polaczenie.send(p) == Socket::Done) {}
    }

    // aktualizacja czasu
    if (czasPlynie)
      czasTxt.setString(to_string(zegar.getElapsedTime().asMilliseconds() / 1000.) + " sek.");
    // test kolizji ze ścianami
    Vector2i pozycja = Vector2i(korpus.getPosition());
    // ponieważ lewy górny róg obrazu PNG labiryntu pokrywa się z punktem 0,0 lewego górnego punktu ekranu,
    // mogę pozycje gracza traktować jak współrzędne pikseli obrazu labiryntu
    for (int x = pozycja.x - 1 - 3; x <= pozycja.x - 1 + 3; x++)
      for (int y = pozycja.y - 1 - 3; y <= pozycja.y - 1 + 3; y++)
      {
        // kolor piksela obrazka, który przykrywa korpus gracza
        Color c = lab->i.getPixel(x, y);
        if (c == Color::Red) { // na końcu
          ustawRuch(false);
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
      korpus.move(x / 24., y / 24.);
    }
  }
};
int main() {
  setlocale(LC_ALL, "");
  cout << "[S]erwer czy [K]lient?";
  char opcja;
  cin >> opcja;
  ///////// KLIENT //////////////
  if (opcja == 'K' or opcja == 'k') { // klient
    shared_ptr<Labirynt> lab = make_shared<Labirynt>();
    program.obiekty.push_back(lab);
    program.obiekty.push_back(make_shared<Gracz>(lab));
    program.pokazCzas = false;
    program.start();
  }
  ///////// SERWER //////////////
  else { // serwer
    program.W->close();
    unsigned nr = 1;
    class Klient : public TcpSocket {
    public:
      unsigned id;
      Klient(unsigned n) :id(n) {}
    };

    sf::TcpListener nasluchiwanie; // Network.hpp
    nasluchiwanie.listen(55555); // nasłuch na porcie 55555
    list<shared_ptr<Klient>> klienci;
    SocketSelector ss;
    ss.add(nasluchiwanie);

    // informacje o pozycjach graczy będą przekazywane za pośrednictwem serwera
    map<unsigned, Vector2f> pozycje;
    map<unsigned, bool> odebrano;
    Packet p;
    while (true) {
      if (ss.wait()) {
        if (ss.isReady(nasluchiwanie) and klienci.size() < 2) {
          pozycje[nr] = { -1,-1 };
          shared_ptr<Klient> klient = make_shared<Klient>(nr++);
          if (nasluchiwanie.accept(*klient) == Socket::Done) {
            cout << "Połączenie z klientem nawiązane.\n";
            klienci.push_back(klient);
            ss.add(*klient);
          }
          if (klienci.size() == 2) {
            for (auto it = klienci.begin(); it != klienci.end(); it++) {
              p.clear();
              p << 0 << 0;
              (*it)->send(p);
            }
          }
        }
        else {
          if (klienci.size() == 2) {
            for (auto it = klienci.begin(); it != klienci.end(); it++) {
              auto& k = **it;
              float x, y;
              // aktywność na którymś z portów klienta
              if (ss.isReady(k)) {
                // odbieram, gdy przyszło
                p.clear();
                k.receive(p);
                p >> x >> y;
                if (k.id == 1) {
                  pozycje[1] = { x,y };
                  odebrano[1] = true;
                }
                else {
                  pozycje[2] = { x, y };
                  odebrano[2] = true;
                }
              }
              // wysyłam zawsze, ale pamiętaj, że
              // wysyłanie jest znacząco szybsze od otrzymywania (klienci mają ograniczenia w pętli)
              if (k.id == 1) {
                if (odebrano[2]) { // jeżeli odebrano raz, to wysyłam raz
                  p.clear();
                  p << pozycje[2].x << pozycje[2].y;
                  k.send(p);
                  odebrano[2] = false;
                }
              }
              else {
                if (odebrano[1]) { // jeżeli odebrano raz, to wysyłam raz
                  p.clear();
                  p << pozycje[1].x << pozycje[1].y;
                  k.send(p);
                  odebrano[1] = false;
                }
              }
            }
          }
        }
      }
    }
  }
}
