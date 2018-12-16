
#ifndef ALGORISMIA_CALCULSIMILITUD_H
#define ALGORISMIA_CALCULSIMILITUD_H

#include "calculSimilitud.cc"

set<string> generateKShingles (int k, string paraules);

void calculaSimilitudTotesKs () ;

void calculaSimilitud ();

void calculaSimilitudTots();

double calculSimilitudAux (int ind1, int ind2, int k);

double calculSimilitudAuxLSH (int ind1, int ind2, int k);

#endif //ALGORISMIA_CALCULSIMILITUD_H