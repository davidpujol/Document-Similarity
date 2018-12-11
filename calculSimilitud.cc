
#include "Jaccard.hh"
#include "ObtenirParaules.hh"

using namespace std;


set<string> generateKShingles (int k, string t)
{
    set<string> shingles;

    int counter = 0;
    while (counter <= t.size()) {
        string newWord;
        if ((counter + k) <= t.size()) {
            newWord = t.substr(counter, k); //agafem de counter a k-1
        }
        else   //es la ultima paraula
            newWord = t.substr (counter);
            
        counter += k;
        shingles.insert(newWord);
    }
    return shingles;
}

void calculaSimilitudTotesKs () {
    cout << "Introdueix els dos documents que vols comprar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    cout << ind1 << " " << ind2 << endl;
    string d1 = llegirDocumentString (ind1);
    cout << "b"<<endl;
    string d2 = llegirDocumentString (ind2);
    cout << "a" << endl;

    for (int k=0; k < 10; ++k) {
        cout << k << endl;
        set<string> d1aux = generateKShingles (k, d1);
        cout << "b" << endl;
        set<string> d2aux = generateKShingles (k, d2);
        cout << "hola" << endl;
        double similitud = jaccard_index (d1aux, d2aux);
        cout << "La teva similitud amb la k " << k << " és : " << similitud << endl;
    }
    
}


void calculSimilitud () {    //inicial
    cout << "Introdueix els dos documents que vols comprar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    
    cout<< "Introdueix el valor k per al calcul dels k-shingles" << endl;
    int k;
    cin >> k;
    
    
    string d1 = llegirDocumentString (ind1);

    string d2 = llegirDocumentString (ind2);
    
    set<string> d1aux = generateKShingles (k, d1);

    set<string> d2aux = generateKShingles (k, d2);
    
    double similitud = jaccard_index (d1aux, d2aux);
    
    cout << "La teva similitud és : " << similitud << endl;
}
