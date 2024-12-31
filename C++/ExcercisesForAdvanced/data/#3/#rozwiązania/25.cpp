#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
typedef long long int L;
typedef unsigned long long int UL;
using namespace std;
//////////////////////////////////////////////////////
double dzialanie(double x, double y, string d) {
  if (d == "+") return x + y;
  else if (d == "-") return x - y;
  else if (d == "*") return x * y;
  else if (d == "/") {
    if (y != 0.) return x / y;
    cout << " [nie dzielimy przez 0] ";
    return 0;
  }
  else {
    cout << "\n!nierozpoznana operacja: " << d << "\n";
  }
}
int main() {
  setlocale(LC_ALL, "");
  ifstream ponp("25_wyrazenia_onp.txt");
  string wyr;
  stringstream ss;
  vector<string> elementy;

  while (getline(ponp, wyr)) {    
    cout << wyr << "\t=>";
    elementy.clear();
    stack<double> operandy;
    size_t poz;
    // wycinam elementy
    while ((poz = wyr.find(" ")) != string::npos) {
      elementy.push_back(wyr.substr(0, poz));
      wyr = wyr.substr(poz + 1);
    }
    if (wyr.size()) elementy.push_back(wyr);

    for (auto& e : elementy) {
      ss.clear();
      ss.str(e);
      double x;  string operacja;
      ss >> x; // pobierz liczbę
      if (ss.fail()) { // nie udało się...
        ss.clear(); // czyszczę stan błędów...
        ss.str(e);
        ss >> operacja; // i czytam znak
        double b = operandy.top();
        operandy.pop();
        double a = operandy.top();
        operandy.pop();
        operandy.push(dzialanie(a, b, operacja));
      }
      else { // udało się pobrać liczbę
        operandy.push(x);
      }
    }
    cout << operandy.top() << endl;
  }
  ponp.close();
}
