// main.cpp
#include "Program.hpp" // udostępniony na początku rozwiązań do części #5
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
class Trojkat : public ConvexShape, public Baza {
public:
  bool KOLIDUJE = false;
  Trojkat(vector<float>& wierzcholki) : ConvexShape() {
    setPointCount(3);
    setPoint(0, { wierzcholki[0],wierzcholki[1] });
    setPoint(1, { wierzcholki[2],wierzcholki[3] });
    setPoint(2, { wierzcholki[4],wierzcholki[5] });
    setFillColor(Color::Black);
    setOutlineThickness(2);
    setOutlineColor(Color::Magenta);
  }
  void rysuj() {
    program.W->draw(*this);
  }
  void progresuj() {}
};
// poniżej: seria funkcji opartych na ALGORYTM SAT do kolizji trójkątów na płaszczyźnie
Vector2f operator-(Vector2f& w1, Vector2f& w2) {
  return { w1.x - w2.x, w1.y - w2.y };
}
Vector2f prostopadly(Vector2f w) {
  return { -w.y, w.x };
}
bool zachodzenieNaSiebie(float min1, float max1, float min2, float max2) {
  return ((min1 <= max2) && (min2 <= max1));
}
bool zachodzenieAxis(Trojkat& t1, Trojkat& t2, Vector2f axis) {
  double min1 = INFINITY, max1 = -INFINITY;
  double min2 = INFINITY, max2 = -INFINITY;
  for (Vector2f p : vector<Vector2f>({ t1.getPoint(0), t1.getPoint(1), t1.getPoint(2) })) {
    double proj = p.x * axis.x + p.y * axis.y;
    min1 = min(min1, proj);
    max1 = max(max1, proj);
  }
  for (Vector2f p : vector<Vector2f>({ t2.getPoint(0),t2.getPoint(1), t2.getPoint(2) })) {
    double proj = p.x * axis.x + p.y * axis.y;
    min2 = min(min2, proj);
    max2 = max(max2, proj);
  }
  return zachodzenieNaSiebie(min1, max1, min2, max2);
}
// kolizja dwóch trójkątów
bool operator==(Trojkat& t1, Trojkat& t2) {
  
  vector<Vector2f> axes = {
    prostopadly(t1.getPoint(1) - t1.getPoint(0)),
    prostopadly(t1.getPoint(2) - t1.getPoint(1)),
    prostopadly(t1.getPoint(0) - t1.getPoint(2)),
    prostopadly(t2.getPoint(1) - t2.getPoint(0)),
    prostopadly(t2.getPoint(2) - t2.getPoint(1)),
    prostopadly(t2.getPoint(0) - t2.getPoint(2)) };
  for (const auto& axis : axes) {
    if (!zachodzenieAxis(t1, t2, axis)) {
      return false;
    }
  }
  return true;
}


int main() {
  setlocale(LC_ALL, "");
  ifstream plik("18_trojkaty.txt");
  vector<float> wiersz;
  string txtwiersz;
  while (getline(plik, txtwiersz)) {
    wiersz.reserve(6); // unikam realokacji i zmiany wartości iteratorów
    istringstream s(txtwiersz); // napis-strumień do odczytywania
    copy(istream_iterator<float>(s), istream_iterator<float>(), back_inserter(wiersz));
    program.obiekty.push_back(make_shared<Trojkat>(wiersz));
    wiersz.clear();
  }
  plik.close();

  for (auto& wsk1 : program.obiekty) {
    auto t1 = dynamic_pointer_cast<Trojkat>(wsk1);
    if (t1->KOLIDUJE) continue;
    for (auto& wsk2 : program.obiekty) {
      if (wsk1 == wsk2) continue;
      auto t2 = dynamic_pointer_cast<Trojkat>(wsk2);
      if (t2->KOLIDUJE) continue;
      if (*t1 == *t2) {
        t1->setFillColor(Color::Yellow);
        t2->setFillColor(Color::Yellow);
        t1->KOLIDUJE = true;
        t2->KOLIDUJE = true;
      }
    }
  }
  for (int nr = 1; auto & wsk1 : program.obiekty) {
    auto t1 = dynamic_pointer_cast<Trojkat>(wsk1);
    if (!t1->KOLIDUJE) {
      cout << nr << " nie koliduje: ";
      for (auto i : { 0,1,2 }) cout << "[" << t1->getPoint(i).x << ":" << t1->getPoint(i).y << "] ";      
      cout << endl;
    }
    nr++;
  }
  program.start();
}
