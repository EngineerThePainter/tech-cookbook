#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <map>
#include <algorithm>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
const string reset("\033[0m"); // RESET koloru
const string bgred("\033[101m"); // szare na czerwonym
const string bggreen("\033[102m"); // szare na zielonym
const string bgyellow("\033[103m"); // szare na żółtym
map<char, vector<UL>> paliki;
void start(UL ile_krazkow = 3) {
  // górny krążek to 1, dolny to ile_krazkow 
  // (koniec wektora to jakby wierzchołek palika)
  paliki['A'] = {};
  paliki['B'] = {};
  paliki['C'] = {};
  for (UL i = ile_krazkow; i >= 1; i--)
    paliki['A'].push_back(i);  
}

void pokaz() {
  UL poziom = (paliki['A'].size() > paliki['B'].size()) ?
    paliki['A'].size() :
    (paliki['B'].size() > paliki['C'].size()) ?
    paliki['B'].size() : paliki['C'].size();
  for (UL i = poziom; i >= 1; i--) {
    if (paliki['A'].size() >= i) {
      cout << paliki['A'][i - 1] << "\t";
    }
    else cout << " " << "\t";

    if (paliki['B'].size() >= i) {
      cout << paliki['B'][i - 1] << "\t";
    }
    else cout << " " << "\t";

    if (paliki['C'].size() >= i) {
      cout << paliki['C'][i - 1] << "\t";
    }
    else cout << " " << "\t";

    cout << endl;
  }
  cout << bgred << "A\tB\tC" << reset << endl;
}

void hanoi(int n, char A, char B, char C) {
  static int i = 1;
  if (n > 0) {
    hanoi(n - 1, A, C, B);
    // A na C
    this_thread::sleep_for(chrono::seconds(1)); // tutaj możesz zmienić czas oczekiwania między ruchami
    paliki[C].push_back(paliki[A].back());
    paliki[A].pop_back();
    cout << bggreen << "KROK " << i++ << reset << endl;    
    pokaz();
    hanoi(n - 1, B, A, C);
  }
}
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));

  start(4); 
  pokaz();
  hanoi(4, 'A', 'B', 'C');  
}
