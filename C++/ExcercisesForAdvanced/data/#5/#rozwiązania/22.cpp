// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <ctime>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Obiekt : public Sprite, public Baza {
  Texture tx;
  Image png;
  bool koliduje = false;
  Vector2f kierunek;
  Clock czasZycia;
public:
  static inline RectangleShape czWspolna;
  Obiekt(string plikPNG, Vector2f pozycja, Vector2f kierunekRuchu={0,0}) : kierunek(kierunekRuchu) {
    png.loadFromFile(plikPNG);
    tx.loadFromImage(png);
    setTexture(tx);
    setOrigin(png.getSize().x, png.getSize().y);
    setPosition(pozycja);
  }
  ~Obiekt() { cout << "Obiekt z pamięci " << &(*this) << " skasowany." << endl; }
  void ustawKolizje(bool v) { koliduje = v; }
  bool czyKoliduje() { return koliduje; }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {
    move(kierunek);
    if (czasZycia.getElapsedTime().asSeconds() > 30) {
      skasuj = true;      
    }
  }
  IntRect czWspolnaObrazka(FloatRect& czWspolna) {
    IntRect i = IntRect(
      czWspolna.left, czWspolna.top,  // lewy,górny
      czWspolna.width, czWspolna.height); // szer, wys
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
      return false; // niemożliwa kolizja
    }
    else {
      // x, y lewy górny róg obszaru wspólnego
      float x = cz_wspolna.left; 
      float y = cz_wspolna.top;
      // szer, wys rozmiar obszaru wspólnego
      float szer = cz_wspolna.width;
      float wys = cz_wspolna.height;      
      
      auto piksele = czWspolnaObrazka(cz_wspolna);
      auto piksele_o = o.czWspolnaObrazka(cz_wspolna);      
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
class GeneratorObiektow {
public:
  float t = 50; 
  Clock zegar;
  unsigned long long int iloscKolizji = 0;
  Text iloscKolizjiText;
  GeneratorObiektow() {
    iloscKolizjiText.setFont(program.czcionka);
    iloscKolizjiText.setCharacterSize(30);
    iloscKolizjiText.setFillColor(Color::Black);
    iloscKolizjiText.setPosition({ WIDTH * 0.8, HEIGHT * 0.8 });
    
    program.dodaj_rysowanie(
      [this]() {
        iloscKolizjiText.setString(to_string(iloscKolizji/2));
        program.W->draw(iloscKolizjiText);
      });
    program.dodaj_progres(
      [this]() {
        if (zegar.getElapsedTime().asMilliseconds() > t + (rand()%2000/100.) * t) {
          string plikpng = vector<string>({ 
            "21_obrazek_2.png","21_obrazek_3.png","21_obrazek_4.png"
            })[rand()%3];
          // obiekt pojawia się 
          size_t los = rand() % 4;
          auto pozycje = vector<Vector2i>({ 
            {rand() % WIDTH, -500} , // nad górną krawędzią ekranu
            {rand()% WIDTH, HEIGHT + 500}, // pod dolna krawędzią ekranu
            {-500, rand()%HEIGHT}, // z lewej
            {WIDTH+500, rand()%HEIGHT}, // z prawej
            {rand()%4-2, 3}, // kierunek w dół
            {rand()%4-2, -3}, // kierunek w górę
            {3, rand()%4-2}, // kierunek w prawo
            {-3, rand()%4-2} // kierunek w lewo
          });
          auto pozycja = pozycje[los];
          auto kierunek = pozycje[los + 4];
          
          shared_ptr<Obiekt> o = make_shared<Obiekt>(plikpng,Vector2f(pozycja),Vector2f(kierunek));
          program.obiekty.push_back(o);
          zegar.restart();          
        }
      });
    program.dodaj_progres(
      [this]() {
        for (auto& o1 : program.obiekty) {
          auto obiekt1 = dynamic_pointer_cast<Obiekt>(o1);
          for (auto& o2 : program.obiekty) {
            auto obiekt2 = dynamic_pointer_cast<Obiekt>(o2);
            if (o1 == o2) continue; // szkoda testować kolizję z sobą samym...
            if (*obiekt1 == *obiekt2) { // kolizja
              obiekt1->ustawKolizje(true);
              obiekt2->ustawKolizje(true);
              obiekt1->skasuj = true;
              obiekt2->skasuj = true;
              iloscKolizji++; // zliczy się podwójnie (uważaj)
            }
          }
        }
      }
    );
    zegar.restart();
  }
};
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));
  GeneratorObiektow G;
  program.start();
}
