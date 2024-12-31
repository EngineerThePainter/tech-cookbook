#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <regex>
using namespace std;
//////////////////////////////////////////////////////
void pokaz(vector<wstring>& v) {
  for (auto e : v) wcout << e << " ";
  cout << endl;
}
int main() {
  setlocale(LC_ALL, nullptr);
  system("chcp 65001"); // UTF-8 w mojej konsoli
  wifstream teryt("teryt.csv");
  vector<vector<wstring>> Teryt;
  wstring linia;
  // wyszukuje dopasowania ciągu tekstu do średnika lub końca napisu
  wregex szukaj(L"([^;]*?)(;|$){1}");
  wsmatch dopasowania; // tu przechowa dopasowania wyszukiwania
  while (getline(teryt, linia)) {    
    Teryt.push_back({});    
    while (regex_search(linia, dopasowania, szukaj) and linia!=L"") {
      // [0] to całe dopasowanie, a [1] to tekst w pierwszym nawiasie 
      Teryt.back().push_back(dopasowania[1]);
      linia = dopasowania.suffix(); // linia traci znalezioną część
    }        
  }
  teryt.close();
  
  auto ilosc = count_if(Teryt.begin(), Teryt.end(),
    [](auto& vec) {            
      if (vec[1] == L"" and vec[2] == L"") {
        wcout << vec[4] << " " << vec[0] << endl;
        return true;
      }
      else {
        return false;
      }
    });    
  setlocale(LC_ALL, "");
  wcout << L"\nLiczba województw: " << ilosc << endl;

  ilosc = count_if(Teryt.begin(), Teryt.end(),
    [](auto& vec) {
      return (vec[2] == L"" and vec[5] == L"powiat");
    });
  wcout << L"\nLiczba powiatów: " << ilosc << endl;

  ilosc = count_if(Teryt.begin(), Teryt.end(),
    [](auto& vec) {
      return (vec[5] == L"gmina wiejska" or vec[5]==L"gmina miejska"
      or vec[5] == L"gmina miejsko-wiejska"
      );
    });
  wcout << L"\nLiczba gmin wiejskich: " << ilosc << endl;

  wifstream miejscowosci("miejscowosci.csv");
  vector<vector<wstring>> Miejscowosci;
  while (getline(miejscowosci, linia)) {
    Miejscowosci.push_back({});
    while (regex_search(linia, dopasowania, szukaj) and linia != L"") {
      // [0] to całe dopasowanie, a [1] to tekst w pierwszym nawiasie 
      Miejscowosci.back().push_back(dopasowania[1]);
      linia = dopasowania.suffix(); // linia traci znalezioną część
    }
  }
  miejscowosci.close();

  ilosc = count_if(Miejscowosci.begin(), Miejscowosci.end(),
    [](auto& vec) {      
      return (vec[0] == L"28" and vec[1] == L"10");
    });
  
  wcout << L"\nLiczba miejscowości w powiecie mrągowskim: " << ilosc << endl;

  ilosc = count_if(Miejscowosci.begin(), Miejscowosci.end(),
    [](auto& vec) {
      return (vec[3].find(L"Piecki")!=wstring::npos or vec[3].find(L"piecki") != wstring::npos);
    });
  wcout << L"\nLiczba miejscowości z -pieckami- w nazwie: " << ilosc << endl;
}
