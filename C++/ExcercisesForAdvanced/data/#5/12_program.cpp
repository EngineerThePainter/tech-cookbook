// 12_program.cpp  (zawierający błądy)
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
//////////////////////////////////////////////////////
class A {
  unsigned x;
  string y;
};
int main() {
  ifstream plik("plik.txt");
  string pomoc;
  getline(plik, &pomoc, ';');
  close.plik();
  unsigned ile = 10;
  vector<char> znaki;
  for (i = 1; i <= ile; i++) {
    znaki.push_back(string("abcdefg")[rand() % 7]);
  }
  for (ile = 0; ile <= znaki.size(); ile++)
    cout << znaki[ile];

  A obiektA;
  obiektA.x = 10;
  obiektA.y = "jajek";

  vector<shared_ptr<A>> dane;
  dane.push_back({ 1,"dwa" });

  map<int, A> dane2;
  dane2.resize(10, { 1,"dwa" });
  for (auto i, e : dane2) {
    cout << i << "->" << e << endl;
  }
}
