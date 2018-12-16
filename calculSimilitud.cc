
#include "Jaccard.hh"
#include "ObtenirParaules.hh"
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include "calculSimilitud.hh"

using namespace std;

/**
 * Agafa un document en forma de string i el divideix en shingles de tamany k
 * @param k Tamany dels shingles
 * @param t Document en forma de string
 * @return Un set amb tots els k-shingles generats
 */
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

/**
 * Calcula la similitud de Jaccard de dos documents per tots els valors de k entre 1 i 10
 */
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

/**
 * Funcio que donat el index dels dos documents i la k, llegeix els documents,
 * genera els seus k shingles i finalment calcula la similitud de Jaccard.
 * @param ind1 Index del primer document
 * @param ind2 Index del segon document
 * @param k Tamany dels shingles
 * @return La similitud de Jaccard.
 */
double calculSimilitudAux (int ind1, int ind2, int k) {
    string d1 = llegirDocumentString (ind1);

    string d2 = llegirDocumentString (ind2);

    set<string> d1aux = generateKShingles (k, d1);

    set<string> d2aux = generateKShingles (k, d2);

    double similitud = jaccard_index (d1aux, d2aux);

    return similitud;
}


/**
 * Calcula la similitud de Jaccard de dos documents per un valord de k introduit per l'usuari.
 */
void calculaSimilitud () {    //inicial
    cout << "Introdueix els dos documents que vols comparar:" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;
    
    cout<< "Introdueix el valor k per al calcul dels k-shingles:" << endl;
    int k;
    cin >> k;

    double similitud = calculSimilitudAux(ind1, ind2, k);
    cout << "La teva similitud és : " << similitud << endl;
}


/**
 * Calcula la similitud de Jaccard de tots els parells possibles entre els 20 documents generats inicialment,
 * tot fent servir una k introduida per l'usuari.
 */
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
                    if ((i+1) / 10 == 0) cout << i+1 << "    ";
                    else cout << i+1 << "   ";
                }
                double result = jaccard_index(generateKShingles(k, llegirDocumentString(i+1)),generateKShingles(k,llegirDocumentString(j+1)));
                cout << " | " << std::fixed << std::setprecision(3) << result;
            }
        }
        cout << endl;
    }

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << endl << "El temps d'execucio en calcular totes les similituds per k = "<< k << " és " << time << " segons." << endl;

}
