#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <Jaccard.hh>
#include <funcionsObtenirParaules.cc>

using namespace std;


set<string> generateKShingles (int k, vector<string> paraules)
{
    set<string> shingles;
    string t = "";
    for (string paraula : paraules) {
        t += paraula + " ";
    }
    cout << t << endl;
    cout << t.size() << endl;
    int counter = 0;
    while (counter <= t.size()) {
        string newWord;
        if ((counter + k) <= t.size()) {
            newWord = t.substr(counter, k);
        }
        else   //es la ultima paraula
            newWord = t.substr (counter);
            
        counter += k+1;
        shingles.insert(newWord);
    }
    return shingles;
}

void calculaTotesKs () {
    cout << "Introdueix els dos documents que vols comprar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    
    vector<string> d1 = llegirDocument (ind1);
    vector<string> d2 = llegirDocument (ind2);
    
    
    for (int k=0; k < 10; ++k) {
        set<string> d1aux = generateKShingles (k, d1);
        set<string> d2aux = generateKShingles (k, d2);
        
        double similitud = jacardIndex (d1aux, d2aux);
        cout << "La teva similitud amb la k " << k << " és : " << similitud << endl;
    
    }
    
}


int main() {    //inicial
    cout << "Introdueix els dos documents que vols comprar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    
    cout<< "Introdueix el valor k per al calcul dels k-shingles" << endl;
    int k;
    cin >> k;
    
    
    vector<string> d1 = llegirDocument (ind1);
    vector<string> d2 = llegirDocument (ind2);
    
    set<string> d1aux = generateKShingles (k, d1);
    set<string> d2aux = generateKShingles (k, d2);
    
    double similitud = jacardIndex (d1aux, d2aux);
    
    cout << "La teva similitud és : " << similitud << endl;
}
