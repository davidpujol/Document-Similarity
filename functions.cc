#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

vector <int> calcularColumna(set <string> shingles, string cjtParaules) {
    vector <int> col(shingles.size(), 0);
    int pos = 0;
     for (auto s: shingles) {
        if(cjtParaules.find(s) < cjtParaules.size()){ col[pos] = 1;  }
        ++pos;    
    }
    return col;
}

int main() {
    string par = "sheldon";
    set<string> s1 = {"yyy", "she", "w", "do","ww"};
    vector <int> res = calcularColumna(s1, par);
    for (int i = 0; i < res.size(); ++i) cout << res[i]<< endl;

}