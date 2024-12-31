#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class PPM {
public:
  vector<vector<bitset<24>>> pixels; // pixels[x][y]
  PPM(size_t sizeY, size_t sizeX = 0) {
    pixels.resize(sizeY, {});
    if (sizeX > 0)
      for (auto& v : pixels)
        v.resize(sizeX, this->rgb2bit24(255, 255, 255));
  }
  void createPPMFile(string fileName) {
    ofstream ppm(fileName + ".ppm");
    ppm << "P3" << endl;
    ppm << "# PPM::createPPMFile" << endl;
    if (pixels.size() > 0) {
      ppm << pixels[0].size() << " " << pixels.size() << endl;
      ppm << 256 << endl;
      // rysujemy
      for (auto& line : pixels) {
        for (bitset<24>&b : line) {
          string temp = b.to_string();
          ppm << bitset<8>(temp.substr(0, 8)).to_ullong() << " ";
          ppm << bitset<8>(temp.substr(8, 8)).to_ullong() << " ";
          ppm << bitset<8>(temp.substr(16, 8)).to_ullong() << " ";
        }
        ppm << endl;
      }
    }
    else {
      ppm << "0 0" << endl;
      ppm << 256 << endl;
    }
    ppm.close();
  }
  bitset<24>&& rgb2bit24(unsigned red, unsigned green, unsigned blue) {
    return bitset<24>(bitset<8>(red).to_string() + 
      bitset<8>(green).to_string() + bitset<8>(blue).to_string());
  }
  void insert(size_t position, unsigned red, unsigned green, unsigned blue) {
    this->pixels[position].push_back(this->rgb2bit24(red, green, blue));
  }
  void insert(vector<bitset<24>>& v, unsigned red, unsigned green, unsigned blue) {
    v.push_back(this->rgb2bit24(red, green, blue));
  }
};
class Kafelek {
public:
  // położenie xmy kafelka na powierzchni (zaczepienie, lewy górny kafelek)  
  unsigned rx = 0; // rozmiar x (ile kafelków na lewo od położenia x)
  unsigned ry = 0; // rozmiar y (ile kafelków do dołu od położenia y
  unsigned red = 0; // kolor czerwony
  unsigned green = 0; // kolor zielony
  unsigned blue = 0; // kolor niebieski  
  Kafelek(unsigned x, unsigned y, unsigned r, unsigned g, unsigned b) :
    rx(x), ry(y), red(r), green(g), blue(b) {}
  Kafelek(unsigned x, unsigned y) :rx(x), ry(y) {}
  Kafelek() {}
  unsigned pole() { return rx * ry; }
};

bool operator<(Kafelek a, Kafelek b) { return (a.pole() < b.pole()); }
bool operator>(Kafelek a, Kafelek b) { return (a.pole() > b.pole()); }

class Podloga {
public:
  unsigned x = 400; // cm
  unsigned y = 250; // cm
  // kafelki leżące na podłodze i ich położenie (lewy górny narożnik 1x1 cm)
  multimap<Kafelek, pair<unsigned, unsigned>> kafelki;
  set<pair<unsigned, unsigned>> cm_nieprzykryte; // współrzędne lewego górnego cm^2
  set<pair<unsigned, unsigned>> cm_przykryte;
  // czy można położyć Kafelek w punkcje x,y (czy nie wchodzi w konflikt z innym leżącym kaflem)
  bool czyMogePolozyc(Kafelek k, unsigned px, unsigned py) {
    // obliczam cm kwadratowe, które przykryłyby mój kafelek, gdybym mógł go położyć
    set<pair<unsigned, unsigned>> do_przykrycia;
    if (py + k.ry > y) return false; // poza podłogę
    if (px + k.rx > x) return false; // poza podłogę
    for (unsigned w = py; w < py + k.ry; w++) {
      for (unsigned s = px; s < px + k.rx; s++) {
        do_przykrycia.insert({ s,w });
      }
    }
    set<pair<unsigned, unsigned>> cz_wspolna;
    set_intersection(do_przykrycia.begin(), do_przykrycia.end(),
      cm_przykryte.begin(), cm_przykryte.end(), inserter(cz_wspolna, cz_wspolna.begin()));
    return !cz_wspolna.size();
  }
  // "kładzie" kafalek na podłodzie we wskazanym miejscu o ile może
  void poloz(Kafelek k, unsigned px, unsigned py) {    
      for (unsigned w = py; w < py + k.ry; w++) {
        for (unsigned s = px; s < px + k.rx; s++) {
          cm_przykryte.insert({ s,w }); // cm^2 przykryte...
          cm_nieprzykryte.erase({ s, w }); // ...nie są przykryte 
        }
      }
      kafelki.insert({ k, { px,py } }); // kafelki zużyte        
  }

  Podloga(unsigned rx, unsigned ry) : x(rx), y(ry) {
    for (unsigned w = 0; w < y; w++) {
      for (unsigned s = 0; s < x; s++) {
        cm_nieprzykryte.insert({ s,w });
      }
    }
  }
  // szukaj pierwszego nieprzykrytego cm kwadratowego od lewej do prawej i od góry do dołu
  pair<unsigned, unsigned> pozycja_pierwszego_nieprzykrytego() {
    if (cm_nieprzykryte.size() == 0) return { x,y };
    for (size_t pozy = 0; pozy < y; pozy++) {
      for (size_t pozx = 0; pozx < x; pozx++) {
        if (cm_nieprzykryte.find({ pozx,pozy }) != cm_nieprzykryte.end()) return { pozx,pozy };
      }
    }
  }
  // szukaj pierwszego nieprzykrytego cm kwadratowego od góry do dołu i od lewej do prawej
  pair<unsigned, unsigned> pozycja_pierwszego_nieprzykrytego_2() {
    if (cm_nieprzykryte.size() == 0) return { x,y };
    for (size_t pozx = 0; pozx < x; pozx++) {
      for (size_t pozy = 0; pozy < y; pozy++) {
        if (cm_nieprzykryte.find({ pozx,pozy }) != cm_nieprzykryte.end()) return { pozx,pozy };
      }
    }
  }
  // zamienia podłogę na grafikę PPM
  void wizualizacja(string plik) {
    PPM ppm(this->y, this->x);
    for (auto& [k, pos] : kafelki) {
      auto kx = pos.first;
      auto ky = pos.second;
      for (auto stepy = ky; stepy < k.ry + ky; stepy++) {
        for (auto stepx = kx; stepx < k.rx + kx; stepx++) {
          ppm.pixels[stepy][stepx] = ppm.rgb2bit24(k.red, k.green, k.blue);
        }
      }

    }
    ppm.createPPMFile(plik);
  }
};

int main() {
  setlocale(LC_ALL, ""); srand(time(0));
  // dostępne w piwnicy kafle
  map<Kafelek, unsigned, greater<Kafelek>> piwnica; // od największych kafelków
  piwnica[Kafelek(25, 35)] = 52;
  piwnica[Kafelek(100, 50)] = 8;
  piwnica[Kafelek(15, 25)] = 32;
  piwnica[Kafelek(40, 40)] = 19;
  piwnica[Kafelek(5, 5)] = 49;
  piwnica[Kafelek(5, 10)] = 89;
  cout << "W piwnicy przed pracą znajdują się: \n";
  for (auto& [k, ile] : piwnica) cout << "kafle rozmiar=" << k.rx << "x" << k.ry << " sztuk " << ile << endl;
  // moja powierzchnia podłogowa
  Podloga P(400, 250);
  // algorytm kładzenia, zachłanny sposób poszukiwania pokrycia podłogi
  // [mam nadzieję, że algorytm zachłanny + wymyślona metoda, wystarczą!]
  while (P.cm_nieprzykryte.size() > 0) { // o ile są jeszcze jakieś cm^2 wolne
    auto przed = P.cm_nieprzykryte.size();
    for (auto it = piwnica.begin(); it != piwnica.end(); it++) {
      // ile jest danego kafelka
      auto& [kaf, ile] = *it; // auto& kaf = it->first; auto& ile = it->second;
      while (ile > 0) { 
        auto wolnaPozycja = P.pozycja_pierwszego_nieprzykrytego();
        auto wolnaPozycja2 = P.pozycja_pierwszego_nieprzykrytego_2();
        // kopia kafelka x na y (będę stosował różne kolory)
        auto kc(kaf); 
        // kafelek w innej pozycji: y na x
        auto kcrev(Kafelek(kc.ry, kc.rx, kc.red, kc.green, kc.blue)); 
        // czy mogę położyć kafelek x na y
        if (P.czyMogePolozyc(kc, wolnaPozycja.first, wolnaPozycja.second)) {
          kc.red = kc.green = rand() % 256;
          kc.blue = rand() % 256;
          P.poloz(kc, wolnaPozycja.first, wolnaPozycja.second);
          ile--;
        }
        // czy mogę położyć kafelek y na x
        else if (P.czyMogePolozyc(kcrev, wolnaPozycja.first, wolnaPozycja.second)) {
          kcrev.red = kcrev.green = rand() % 256;
          kcrev.blue = rand() % 256;
          P.poloz(kcrev, wolnaPozycja.first, wolnaPozycja.second);
          ile--;
        }
        // czy mogę położyć kafelek x na y (inny algorytm kładzenia)
        else if (P.czyMogePolozyc(kc, wolnaPozycja2.first, wolnaPozycja2.second)) {
          kc.red = kc.green = rand() % 256;
          kc.blue = rand() % 256;
          P.poloz(kc, wolnaPozycja2.first, wolnaPozycja2.second);
          ile--;
        }
        // czy mogę położyć kafelek y na x (inny algorytm kładzenia)
        else if (P.czyMogePolozyc(kcrev, wolnaPozycja2.first, wolnaPozycja2.second)) {
          kcrev.red = kcrev.green = rand() % 256;
          kcrev.blue = rand() % 256;
          P.poloz(kcrev, wolnaPozycja2.first, wolnaPozycja2.second);
          ile--;
        }
        else break; // nie da się położyć, przejdę do mniejszego kafelka
      }
    }
    // nie udało się położyć żadnego kafelka, są za duże, nie ma ich, źle poukładała metoda
    // zachłanna
    if (przed == P.cm_nieprzykryte.size()) break; 
  }

  cout << "Pokryte cm kwadratowe: " << P.cm_przykryte.size() << endl;
  cout << "Niepokryte cm kwadratowe: " << P.cm_nieprzykryte.size() << endl;
  cout << "W piwnicy pozostało: \n";
  for (auto& [k, ile] : piwnica) cout << "kafle rozmiar=" << k.rx << "x" << k.ry << " sztuk " << ile << endl;

  P.wizualizacja("grafika"); // utworzy plik „grafika.ppm”
}
