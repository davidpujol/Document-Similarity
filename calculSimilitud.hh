
#ifndef ALGORISMIA_CALCULSIMILITUD_H
#define ALGORISMIA_CALCULSIMILITUD_H



#include <iostream>
#include <string>
#include <vector>
#include "calculSimilitud.cc"

using namespace std;

set<string> generateKShingles (int k, string paraules);

void calculaSimilitudTotesKs () ;

void calculaSimilitud ();

void calculaSimilitudTots();

#endif //ALGORISMIA_CALCULSIMILITUD_H