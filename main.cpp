#include <iostream>
#include <vector>
#include "calculSimilitud.h"
#include "ObtenirParaules.hh"
#include <set>

#define N_DOCS 20

using namespace std;

void similitudMinHash() {
    set<string> shingles;
    set<string> s;
    for(int i = 0; i < N_DOCS; i++) {
        vector<string> paraules = llegirDocument(i);
        s = generateKShingles(4,paraules);
        shingles.insert(s.begin(), s.end());
    }

    for (auto const &e: s)
        cout << e << ' ';
    cout << endl;

}

int main() {
    cout << "1. Vols trobar la similitud de Jaccard de dos documents" << endl;
    cout << "2. Vols trobar una aproximació de la similitud de Jaccard amb minHash" << endl;

    int i;
    cin >> i;

    if (i == 1) {
        calculSimilitud();
    }

    else {

    }


}

