#include <iostream>
#include <random>
#include <list>
#include <ctime>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
const UL LIMIT = 250000;
int main() {
  setlocale(LC_ALL, "");    
  cout.precision(15);
  default_random_engine(rng);
  rng.seed(time(0));
  uniform_real_distribution<double> podajnik(0, 1);  
  list<int> kolejka; // taka częściowa symulacja, gdzie klient to dowolna liczba
  for (double szansa = 0.53; szansa < 0.96; szansa += 0.01) {    
    kolejka.clear();
    UL opuscilo = 0;
    while (kolejka.size() <= LIMIT) {
      if (podajnik(rng) < szansa) {
        kolejka.push_back(1);        
      }
      else if (kolejka.size()) {
        kolejka.pop_front();
        opuscilo++;        
      }
    }        
    cout << szansa << "\t" 
      << (opuscilo * 1.0) / (kolejka.size() * 1.0) << endl;
  }  
}
