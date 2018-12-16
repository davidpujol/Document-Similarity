#include <iostream>
#include <vector>
#include "calculSimilitud.hh"
#include "ObtenirParaules.hh"
#include "localSensiveHashing.hh"
#include "Minhash.hh"
#include <set>

#define N_DOCS 20

using namespace std;

/**
 * Submenu amb les diferent opcions per a executar el primer algorisme de la similitud de Jaccard.
 */
void similitudJaccard() {
    cout << "1. Vols trobar la similitud de Jaccard de dos documents per una K donada" << endl;
    cout << "2. Vols trobar la similitud de Jaccard de dos documents per Ks entre 1 i 10" << endl;
    cout << "3. Vols trobar la similitud de Jaccard dels N documents per una K donada" << endl;

    cout << "Introdueix la teva opcio:" << endl;

    int i;
    cin >> i;
    if (i == 1) {
        calculaSimilitud();
    } else if (i == 2) {
        calculaSimilitudTotesKs();
    } else if (i == 3) {
        calculaSimilitudTots();
    }

}

/**
 * Submenu amb les diferents opcions per a executar el segon algorisme de la similiud de Jaccard a partir de signatures MinHash.
 */
void similitudJaccardMinHash() {
    cout << "1. Vols trobar una aproximació de la similitud de Jaccard de dos documents per una K donada" << endl;
    cout << "2. Vols trobar una aproximació de la similitud de Jaccard de dos documents per Ks entre 1 i 10" << endl;
    cout << "3. Vols trobar una aproximació de la similitud de Jaccard dels N documents per una K donada" << endl;

    cout << "Introdueix la teva opcio:" << endl;
    int i;
    cin >> i;
    if (i == 1) {
        calculaMinHashSimilarity();
    } else if (i == 2) {
        calculaMinHashSimilarityTotesKs();
    } else if (i == 3) {
        calculaMinHashSimilarityTots();
    }
}

/*
 * Submenú amb les diferents opcions per executar el tercer algorisme de LSH.
 */
void similitudJaccardLSH(){
    calculaLocalSensitiveHashing();
}

int main() {
    while (true){
        cout << endl;
        cout << "1. Trobar la similitud de Jaccard" << endl;
        cout << "2. Trobar la similitud de Jaccard amb MinHash" << endl;
        cout << "3. Trobar la similitud de Jaccard Local Sensitive Hashing amb MinHash" << endl;

        cout << "Introdueix la teva opcio:" << endl;
        int i;
        cin >> i;
        if (i == 1) {
            similitudJaccard();
        } else if (i == 2) {
            similitudJaccardMinHash();
        } else if (i == 3) {
            similitudJaccardLSH();
        }
    }

}

