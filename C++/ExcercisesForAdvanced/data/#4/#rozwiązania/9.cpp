#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
//////////////////////////////////////////////////////
enum struct kolor {trefl, pik, karo, kier};
enum struct rodzaj {dwojka, trojka, czworka, piatka, szostka, 
siodemka, osemka, dziewiatka, dziesiatka, walet, dama, krol, as};
map<rodzaj, string> translator_karty {
  {rodzaj::dwojka,"dwójka"}, {rodzaj::trojka, "trójka"}, {rodzaj::czworka,"czwórka"},
  {rodzaj::piatka,"piątka"}, {rodzaj::szostka, "szóstka"}, 
  {rodzaj::siodemka,"siódemka"}, {rodzaj::osemka,"ósemka"}, 
  {rodzaj::dziewiatka, "dziewiątka"}, {rodzaj::dziesiatka,"dziesiątka"},
  {rodzaj::walet, "walet"}, {rodzaj::dama,"dama"}, {rodzaj::krol,"król"},
  {rodzaj::as,"as"}

};
map<kolor, unsigned int> modyfikatory_punktowe = {  
  {kolor::trefl, 0}, {kolor::pik, 1}, {kolor::karo, 2}, {kolor::kier, 3}
};
map<kolor, string> translator_kolory {
  {kolor::trefl, "trefl"}, {kolor::pik, "pik"}, 
  {kolor::karo, "karo"}, {kolor::kier, "kier"}
};
class Karta {
public:  
  kolor kol;
  rodzaj rodz;
  Karta(kolor k, rodzaj r) : kol(k), rodz(r) {}
  unsigned int punkty() {
    return (modyfikatory_punktowe[kol] + unsigned int(rodz));      
  }
  void pokaz() {
    cout << translator_karty[rodz] << " " << translator_kolory[kol] 
      << "[" << punkty() << "pkt]";
  }
};
class Gracz {
public:
  string nr;
  vector<Karta> karty;
  // jakie karty ma gracz?
  void pokaz_karty() {    
    for (auto& k : karty) {
      k.pokaz();
      cout << endl;
    }
    cout << punkty() << " pkt.\n";
  }
  // suma punktów z kart
  unsigned punkty() {
    unsigned s = 0;
    for (auto& k : karty) s += k.punkty();
    return s;
  }
  Gracz(int n) { nr = to_string(n); }
  vector<Karta> odrzuc_karty() {
    auto odrzucone = karty;
    karty.clear();
    return odrzucone;
  }
};
class Stolik {
public:
  vector<Gracz> gracze;
  Stolik(int ilosc=0) {
    ilosc = (ilosc == 0) ? rand() % 3 + 2 : ilosc; // gracze 2-4
    for (unsigned i = 0; i < ilosc; i++) {
      gracze.push_back(Gracz(i));
    }
    cout << "Widzisz piękny stolik do gry, a przy nim "
      << gracze.size() << " graczy.\n";
  }
  // ilu graczy przy stoliku
  size_t ileGraczy() {
    return gracze.size();
  }
  // pokaż karty graczy
  void pokaz_karty_graczy() {
    for (auto& g : gracze) {
      cout << "Gracz nr: " << g.nr << endl;
      g.pokaz_karty();      
    }
  }
};
class Talia {
public:
  vector<Karta> karty;
  Talia() {
    for (int i=0; i < 4; i++) {      
      for (int k = 0; k < 13; k++) {
        karty.push_back(Karta(kolor(i),rodzaj(k)));        
      }
    }
    cout << "Utworzono nową talię złożoną z " << karty.size() << " kart.\n";
  }
  void pokaz() {
    for (auto& e : karty) {
      e.pokaz();
      cout << endl;
    }
  }
  void potasuj() {
    // wbudowana w bibliotekę funkcja mieszająca, oparta na silniku random,
    // ziarno mieszające oparte na odczycie czasu
    cout << "Rozpoczynam tasowanie talii kart. ";
    cout << "(czynnik mieszania: " <<
      chrono::system_clock::now().time_since_epoch().count() << ")\n";
    shuffle(karty.begin(), karty.end(),
      default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
    cout << "Kart w talii: " << karty.size() << endl;
  }
  // przekazuję kartę (np. zawsze ostatnią z listy kart) dla wskazanego gracza,
  // można podać kilka kart naraz
  void karta_dla_gracza(Stolik& s, unsigned nrGracza, unsigned nKart=1) {
    for (unsigned ile = 1; ile <= nKart and karty.size(); ile++) {
      s.gracze[nrGracza].karty.push_back(karty.back());
      karty.pop_back();
    }
  }
  // przekazuję kartę po iteratorze
  void karta_dla_gracza(Stolik& s, vector<Gracz>::iterator nrGracza, unsigned nKart = 1) {
    for (unsigned ile = 1; ile <= nKart and karty.size(); ile++) {
      nrGracza->karty.push_back(karty.back());
      karty.pop_back();
    }
  }
  // dodaję kartę do talii, nie sprawdzam, czy istnieje taka karta w talii
  void dodaj_karte(kolor k, rodzaj r) {
    karty.push_back(Karta(k, r));
  }
  // dodaje grupę kart, nie sprawdzam, czy istnieją ich kopie w talii
  void dodaj_karty(vector<Karta> grupaKart) {
    karty.insert(karty.end(), grupaKart.begin(), grupaKart.end());
  }
};

int main() {
  setlocale(LC_ALL, "");  
  Talia T;  
  T.potasuj();  
  // T.pokaz(); // możesz podglądnąć karty po potasowaniu, jeżeli usuniesz znaki komentarza //

  Stolik S;
  // przekaż z talii na stoliki graczy po 3 karty dla każdego  
  for (unsigned nrGracza = 0; nrGracza < S.ileGraczy(); nrGracza++) {
    T.karta_dla_gracza(S, nrGracza, 3);
  }
  S.pokaz_karty_graczy();
  cout << "Kart w talii zostało: " << T.karty.size() << endl;
  // wyłońmy zwycięzcę
  cout << "--- WYGRANY ---\n";
  auto pierwszy = S.gracze.begin();
  auto ostatni = S.gracze.end();
  do {
    // sortuję po liczbie punktów. Pamiętaj, że metoda sort działa na zakresie 
    // od zamkniętego do otwartego [pierwszy, ostatni) (bez ostatniego)
    cout << "Sortuję graczy wg. punktów: ";
    sort(pierwszy, ostatni,
      [](Gracz& g1, Gracz& g2) {        
        return (g1.punkty() > g2.punkty());
      });    
    // pierwszy wygrywa, drugi po nim i pozostali mają mniej
    if (S.gracze[0].punkty() > S.gracze[1].punkty()) break; 
    // konieczność dogrywki
    cout << " ... dogrywka ...\n";
    auto pierwszy = S.gracze.begin();
    auto ostatni = S.gracze.end();
    ostatni--; // potrzebuję iteratora na ostatni, a nie end();    
    // sprawdzam, ilu już przegrało, i już ich nie uwzględniam, 
    // gracze od pierwszy do ostatni będą tymi, którzy wymagają dogrywki, 
    // gdyż ich punkty są równe
    while (pierwszy->punkty() > ostatni->punkty()) ostatni--;
    ostatni++; // przesuwam się oczko dalej, by go nie uwzględniać
    // pokazuję, kto bierze udział w dogrywce
    for (auto p = pierwszy; p != ostatni; p++) {
      cout << "Dogrywka dla gracza: " << p->nr << ", pkt=" << p->punkty() << endl;
    }
    // zabieram karty zwycięzcom, by zrobić dogrywkę
    for (auto p = pierwszy; p != ostatni; p++) 
      T.dodaj_karty(p->odrzuc_karty()); // z ręki do talii    
    T.potasuj();    
    // rozdaj ponownie karty graczy biorącym udział w dogrywce
    for (auto p = pierwszy; p != ostatni; p++) T.karta_dla_gracza(S, p, 3);        
    ostatni++; // metoda sort działa [od : do) ale bez elementu do
    // wracam do początku pętli 
    // do sortowania, ale teraz już tylko graczy w dogrywce
  } while (true);
  // WYGRANY
  cout << "Gracz nr = " << S.gracze[0].nr << endl;
  S.gracze[0].pokaz_karty();

  // 3 karty mogę wylosować na 52!/(3!*(52-3)!) sposobów, czyli = 22100
  cout << "OBLICZANIE PRAWDOPODOBIEŃSTWA bez wzoru:\n";
  Talia Tsym;
  double wszystkieMozliweTrojkiKart = 0;
  double trojkiKartPonizej15 = 0;
  for (auto it1 = Tsym.karty.begin(); it1 != Tsym.karty.end(); it1++) {
    for (auto it2 = it1 + 1; it2 != Tsym.karty.end(); it2++) {
      for (auto it3 = it2 + 1; it3 != Tsym.karty.end(); it3++) {
        wszystkieMozliweTrojkiKart+=1;
        if (it1->punkty() + it2->punkty() + it3->punkty() < 15)
          trojkiKartPonizej15+=1;
      }
    }
  }
  cout << wszystkieMozliweTrojkiKart << " wszystkich trójek kart " << endl;
  cout << trojkiKartPonizej15 << " trójek kart nie przekracza sumy 15 " << endl;  
  double szansa = trojkiKartPonizej15 / wszystkieMozliweTrojkiKart;
  cout << szansa 
    << " = szansa na wybranie trójki kart, która nie ma 15 punktów." << endl; 
}
