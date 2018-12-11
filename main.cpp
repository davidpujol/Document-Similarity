#include <iostream>
#include <vector>
#include "calculSimilitud.h"
#include "ObtenirParaules.hh"
#include "Minhash.h"
#include <set>

#define N_DOCS 20

using namespace std;


int main() {
    cout << "1. Vols trobar la similitud de Jaccard de dos documents" << endl;
    cout << "2. Vols trobar una aproximació de la similitud de Jaccard amb minHash" << endl;

    int i;
    cin >> i;

    if (i == 1) {
        calculSimilitud();
    }

    else {
        calculSimilitudMinHash();
    }


}

