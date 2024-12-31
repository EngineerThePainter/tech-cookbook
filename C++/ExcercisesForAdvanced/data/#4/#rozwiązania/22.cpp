#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////
typedef unsigned long long int UL;
class Siec {
public:
  string bazowyIP;
  unsigned maska;
  Siec(string adres_maska){
    auto poz = adres_maska.find(" ");
    bazowyIP = adres_maska.substr(0, poz);
    maska = stoul(adres_maska.substr(poz + 2));
  }
  // zwraca IP jako liczbę 32-bitową
  bitset<32> stringIP_bitset() {
    string ip = bazowyIP;
    size_t poz = 0;
    string oktety;
    while ((poz = ip.find(".")) != string::npos) {
      oktety += bitset<8>(stoull(ip.substr(0, poz))).to_string();
      ip = ip.substr(poz + 1);
    }
    oktety += bitset<8>(stoull(ip)).to_string();
    return bitset<32>(oktety);
  }
  // zwraca adres sieci i broadcast
  pair<bitset<32>, bitset<32>> adres_boradcast() {
    string prefix = stringIP_bitset().to_string().substr(0, maska);
    return {
      bitset<32>(prefix + string(32 - maska,'0')),
      bitset<32>(prefix + string(32-maska,'1'))
    };
  }
  UL ileHostow() {
    auto [adres, broadcast] = adres_boradcast();
    return broadcast.to_ullong() - adres.to_ullong() - 1;
  }
  // zamienia biteset<32> na napis IP z uwzględnieniem oktetów 4 x 8-bit jak 123.21.131.234 itp.
  static string toString(bitset<32> b) {
    string b32 = b.to_string();
    return to_string(bitset<8>(string(b32.begin(), b32.begin() + 8)).to_ullong()) + "." +
    to_string(bitset<8>(string(b32.begin()+8, b32.begin() + 16)).to_ullong()) + "." +
    to_string(bitset<8>(string(b32.begin()+16, b32.begin() + 24)).to_ullong()) + "." +
    to_string(bitset<8>(string(b32.begin()+24, b32.begin() + 32)).to_ullong());
  }
  void info() {
    cout << bazowyIP << "=" << stringIP_bitset() << " /" << maska << endl;
    auto [adres, broadcast] = adres_boradcast();
    cout << "Adres sieci: " << Siec::toString(adres) << " " 
      << "Adres rozgłoszeniowy: " << Siec::toString(broadcast) << endl;    
    cout << "Hostów:" << ileHostow() << endl;
    cout << "Adresy hostów od: " <<
      Siec::toString(bitset<32>(adres.to_ullong() + 1)) << " do " <<
      Siec::toString(bitset<32>(broadcast.to_ullong() - 1)) << endl;

  }
};
int main() {
  setlocale(LC_ALL, "");
  vector<Siec> vs{
    Siec("172.10.10.10 /24"),
    Siec("108.2.2.240 /28"),
    Siec("11.12.13.14 /20"),
    Siec("200.100.150.0 /17"),
    Siec("245.11.12.188 /30")
  };
  for (auto& b : vs) {
    b.info();
    cout << endl << endl;
  }
}
