
#include "Jaccard.hh"
#include "ObtenirParaules.hh"
#include <iomanip>
#include <ctime>


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

        counter += 1;
        shingles.insert(newWord);
    }
    return shingles;
}

void calculaSimilitudTotesKs () {
    cout << "Introdueix els dos documents que vols comprar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;

    string d1 = llegirDocumentString (ind1);
    string d2 = llegirDocumentString (ind2);
    for (int k=1; k <= 10; ++k) {
        set<string> d1aux = generateKShingles (k, d1);
        set<string> d2aux = generateKShingles (k, d2);
        double similitud = jaccard_index (d1aux, d2aux);
        cout << "La teva similitud amb la k " << k << " és : " << similitud << endl;
    }
    
}

double calculSimilitudAux (int ind1, int ind2, int k) {
    string d1 = llegirDocumentString (ind1);

    string d2 = llegirDocumentString (ind2);

    set<string> d1aux = generateKShingles (k, d1);

    set<string> d2aux = generateKShingles (k, d2);

    double similitud = jaccard_index (d1aux, d2aux);

    cout << "La teva similitud és : " << similitud << endl;
    return similitud;
}

double calculSimilitudAuxLSH (int ind1, int ind2, int k) {
    string d1 = llegirDocumentString (ind1);

    string d2 = llegirDocumentString (ind2);

    set<string> d1aux = generateKShingles (k, d1);

    set<string> d2aux = generateKShingles (k, d2);

    double similitud = jaccard_index (d1aux, d2aux);

    return similitud;
}

void calculaSimilitud () {    //inicial
    cout << "Introdueix els dos documents que vols comparar:" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    
    cout<< "Introdueix el valor k per al calcul dels k-shingles:" << endl;
    int k;
    cin >> k;

    calculSimilitudAux(ind1, ind2, k);

}

void calculaSimilitudTots() {
    cout<< "Introdueix el valor k per al calcul dels k-shingles:" << endl;
    int k;
    cin >> k;

    unsigned t0, t1;
    t0 = clock();

    cout << "DOCS";
    for (int i = -1; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(i == -1) {   //la primera fila
                if (j==0) cout << "  | " << j+1;
                else if (j/10 == 0) cout << "     | " << j+1;
                else cout << "    | " << j+1;
            }
            else {  //la primera columna
                if (j == 0) {
                    if (i / 10 == 0) cout << i << "    ";
                    else cout << i << "   ";
                }
                double result = jaccard_index(generateKShingles(k, llegirDocumentString(i+1)),generateKShingles(k,llegirDocumentString(j+1)));
                cout << " | " << std::fixed << std::setprecision(3) << result;
            }
        }
        cout << endl;
    }

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "El temps d'execucio en calcular totes les similituds per k = "<< k << " és " << time << " segons." << endl;

}
