#include <iostream>
#include <vector>
using namespace std;
typedef long long int L;
typedef unsigned long long int UL;
//////////////////////////////////////////////////////
struct Vertex {
  int dane;
  Vertex* L = nullptr; // potomek lewy
  Vertex* P = nullptr; // potomek prawy  
  // pomoc przy przeglądaniu
  bool odwiedzony = false;
};
void dodaj(Vertex*& v, int d) {
  if (v == nullptr) {
    v = new Vertex;
    v->dane = d;
  }
  else if (v->dane < d) dodaj(v->P, d);
  else dodaj(v->L, d);
}
void dodaj(Vertex*& v, vector<int> ds) {
	// kopia od "prawej do lewej"
  vector<int> dscopy(ds.rbegin(), ds.rend()); 
  while (dscopy.size()) {
		// dodaj ostatni z odwróconej kopii
    dodaj(v, dscopy.back()); 
		// i usuń ostatni po dodaniu
    dscopy.pop_back(); 
  }
}
void pokazVLR(Vertex* v) {
  if (v != nullptr) {
    if (!v->odwiedzony) {
      cout << v->dane << " ";
      v->odwiedzony = true;
    }
    pokazVLR(v->L);
    pokazVLR(v->P);
    // czyszczę po sobie, by można było ponownie przeglądać
    v->odwiedzony = false;
  }
}
void usun(Vertex*& v) {
  if (v->L != nullptr) {
    usun(v->L);
  }
  if (v->P != nullptr) {
    usun(v->P);
  }
  // cout << "Usuwam " << v->dane << endl;
  delete v;
  v = nullptr;
}
int main() {
  setlocale(LC_ALL, "");

  Vertex* Drzewo = nullptr;
  dodaj(Drzewo, { 1,2,3,2,1,5,4,3,5,7,5,3 });
  pokazVLR(Drzewo);
  cout << endl;
  usun(Drzewo);
  pokazVLR(Drzewo);
  cout << endl << "---" << endl;
}