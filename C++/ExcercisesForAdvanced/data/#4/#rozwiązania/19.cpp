#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;
//////////////////////////////////////////////////////
int main() {
  setlocale(LC_ALL, "");
  ifstream plik("19_dane.txt");
  string linia, pomoc;
  vector<string> linie;
  while (getline(plik, pomoc)) {
    linia += pomoc;
    linie.push_back(pomoc);
  }
  plik.close();
  regex szukaj("R.(X|F)");  
  smatch dopasowania;
  unsigned long long int ile = 0;
  while (regex_search(linia, dopasowania, szukaj) and linia!="") {    
    // usuwam wszystko od początku napisu do pozycji, gdzie znalazłem podciąg
    linia = linia.substr(dopasowania.position()+1); 
    ile++;
  }          
  cout << "Podciągów R*X lub R*F znaleziono: " << ile << endl;

  ile = 0;
  szukaj.assign("^[^EZ]*X[^EZ]*$");
  for (auto& ln : linie) {
    if (regex_match(ln, dopasowania, szukaj)) {
      ile++;
    }
  }
  cout << "Wierszy bez E i Z, które zawierają X, jest " << ile << endl;

  ile = 0;
  string wzorzec = "";
  for (int znak = 65; znak <= 65 + 25; znak++) wzorzec += string(1, char(znak)) + "{0,1}";
  // cout << wzorzec << endl; // możesz przywrócić instrukcję, by sprawdzić wzorzec regex (podgląd)
  szukaj.assign(wzorzec);
  for (auto ln : linie) {
    while (ln != "" and regex_search(ln, dopasowania, szukaj)) {
      if (dopasowania[0].str().size() >= 5) {
        // cout << dopasowania[0].str() << endl; // podciągi
        ile++;        
        break;
      }
      ln = dopasowania.suffix();            
    }
  }
  cout << "Wierszy zawierających podciąg przynajmniej 5 rosnących znaków: " << ile << endl; 
}
