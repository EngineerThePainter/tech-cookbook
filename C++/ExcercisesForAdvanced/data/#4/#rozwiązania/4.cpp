#include <iostream>
using namespace std;
typedef long long int L;
//////////////////////////////////////////////////////
/*
Korzystam z:
(A * B) mod C = ((A mod C) * (B mod C)) mod C
*/
/*
   Obliczamy rekurencyjnie f(a, b, x) = (a^x%b) ==
   (a*a^(x-1))%b == ((a%b) * (a^(x-1)%b))%b ==
   (a%b*f(a, b, x-1))%b  -> tu widać mechanizm rekurencji
*/
L funkcja(L a, L b, L x) {
  // bo a do potęgi 0 to 1, a 1%b == 1 (warunek stopu rekurencji)
  if (x == 0) return 1;
  auto w = ((a % b) * funkcja(a, b, x - 1)) % b;
  return w;
  // Uwaga! Głęboka rekurencja może spowodować wyjątek przepełnienia stosu.
  // W opcjach konsolidatora może istnieć potrzeba zwiększenia domyślnej 
  // wartości z 1MB na więcej (polecenie /STACK: reserve, comit)
  // Na ten problem natknąłem się w VS 2022. W CodeBlocks podczas korzystania
  // z Cygwin GCC nie było takiej potrzeby.
}
bool istnieje(L a, L b, L c, L& x) { // istnieje 0<=x<b, że a^x%b == c
  for (x = 0; x < b; x++) {
    if (funkcja(a, b, x) == c) return true;
  }
  return false;
}
int main() {
  setlocale(LC_ALL, "");
  L x;
  if (istnieje(551, 6634, 457, x)) cout << x << endl; else cout << "-\n";  
  if (istnieje(78, 11, 3, x)) cout << x << endl; else cout << "-\n";
  if (istnieje(2280, 3045, 660, x)) cout << x << endl; else cout << "-\n";  
  if (istnieje(4568, 9065, 1505, x)) cout << x << endl; else cout << "-\n";
}
