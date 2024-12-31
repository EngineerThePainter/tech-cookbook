#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;
//////////////////////////////////////////////////////
constexpr auto KPORT = 10000;
void klient() {
  cout << "START KLIENTA\n";
  TcpSocket gniazdo_do_serwera;
  Packet dane_do_serwera;
  if (gniazdo_do_serwera.connect("127.0.0.1", KPORT) != Socket::Done) {
    cout << "Klient nie nawiązał połączenia z serwerem.\n";
  }
  else {
    while (true) {
      cout << "Wprowadź dane:";
      string dane;
      cin >> dane;
      if (dane == "koniec") {
        cout << "Kończenie pracy klienta.\n";
        gniazdo_do_serwera.disconnect();
        return;
      }
      dane_do_serwera << dane;      
      if (gniazdo_do_serwera.send(dane_do_serwera) != Socket::Done) {
        cout << "Nieudane wysyłanie danych na serwer.\n";
        gniazdo_do_serwera.disconnect();
        return;
      }
      dane_do_serwera.clear();
    }

  }
}
void serwer() {
  cout << "START SERWERA\n";
  TcpListener nasluchiwanie;
  if (nasluchiwanie.listen(KPORT) != Socket::Done) {
    cout << "Nieudane uruchomienie nasłuchiwania na porcie " << KPORT << endl;
  }
  else {
    TcpSocket gniazdo_do_klienta;
    Packet dane_od_klienta;
    if (nasluchiwanie.accept(gniazdo_do_klienta) != Socket::Done) {
      cout << "Nieudane połączenie z klientem.\n";
    }
    else {
      while (true) {
        cout << "Oczekuję na dane...\n";
        if (gniazdo_do_klienta.receive(dane_od_klienta) != Socket::Done) {
          cout << "Nie udało się odebrać danych od klienta.\n";
          gniazdo_do_klienta.disconnect();
          break;
        }
        else {
          string odebrane_dane;
          if (dane_od_klienta >> odebrane_dane) {
            cout << odebrane_dane << endl;
            dane_od_klienta.clear();
          }
          
        }
      }
    }

  }
}
int main() {
  setlocale(LC_ALL, "");
  srand(time(0));  
  // uruchom dwukrotnie skompilowany plik wynikowy *.exe,
  // najpierw uruchom [s]erwer, potem uruchom drugą instancję programu i odpal [k]lienta.
  cout << "Uruchom [k]lienta/[s]erwer:";
  char opcja;
  cin >> opcja; 
  if (opcja == 'k') { 
    klient();
  }
  else {
    serwer();
  }  
}
