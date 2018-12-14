#include <iostream>
#include <vector>
#include "calculSimilitud.hh"
#include "ObtenirParaules.hh"
#include "Minhash.hh"
#include <set>

#define N_DOCS 20

using namespace std;


int main() {
    cout << "1. Vols trobar la similitud de Jaccard de dos documents per un K donada" << endl;
    cout << "2. Vols trobar la similitud de Jaccard de dos documents per Ks entre 1 i 10" << endl;
    cout << "3. Vols trobar una aproximació de la similitud de Jaccard amb minHash" << endl;

    int i;

    cout << "Introdueix la teva opcio:" << endl;
    while (cin >> i) {
        if (i == 1) {
            calculSimilitud();

        } else if (i == 2) {
            calculaSimilitudTotesKs();
        } else if (i == 3) {
            calculaMinHashSimilarity();
        }

        cout << "Introdueix la teva opcio:" << endl;
    }


}

