#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <chrono>
#include <thread>

typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
const string red("\033[91m"); // czerwony
const string reset("\033[0m"); // RESET koloru
map<string, double> planety = { {"Ziemia",9.8}, {"Merkury",3.7}, {"Wenus",8.9},
  {"Mars",3.7}, {"Jowisz",25.9}, {"Saturn",11.2}, {"Uran",8.6}, {"Neptun",11.2} };
// droga w metrach, przyśpieszenie w m/s*s, czas w sekundach
double oblicz_czas(double droga, double przyspieszenie) {
  return sqrt((2.0 * droga) / przyspieszenie);
}
double oblicz_droga(double s, double przyspieszenie) {
  return (przyspieszenie * s * s) / 2.;
}
struct P {
  bool leci = true;
  double droga = 0;
  double czas = 0;
};

int main() {
  setlocale(LC_ALL, "");
  map<string, P> przedmioty;
  for (auto& p : planety) przedmioty[p.first] = P{};
  auto start = chrono::system_clock::now();
  auto cooldoown = chrono::system_clock::now();
  bool leca = true; // lecą 
  while (leca) {
    // upływ czasu w sekundach
    auto s = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count();
    leca = false;
    for (auto& p : planety) {
      if (przedmioty[p.first].leci) {
        leca = true;
        auto m = oblicz_droga(s / 1000., p.second);
        przedmioty[p.first].czas = s / 1000.; // sek
        przedmioty[p.first].droga = m;
        if (m >= 1500) {
          przedmioty[p.first].leci = false;
          cout << red << "\nPrzedmiot upadł na " << p.first << " po czasie " << przedmioty[p.first].czas
            << "s i przebył drogę " << przedmioty[p.first].droga << "m" << reset << endl;
        }
      }
    }
    this_thread::sleep_for(chrono::microseconds(5)); // czekaj sekundę
    auto c = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - cooldoown).count();
    if (c >= 750) {
      for (auto& p : planety) {
        if (przedmioty[p.first].leci)
          cout << p.first << przedmioty[p.first].droga << "m  ";
      }
      cooldoown = chrono::system_clock::now();
      cout << endl;
    }
  }

  // wyliczenie bez symulacji
  for (auto& pl : planety) {
    cout << pl.first << "\t\tczas = " << oblicz_czas(1500, pl.second) << endl;
  }
}
