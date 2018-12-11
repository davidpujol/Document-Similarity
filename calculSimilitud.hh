
#ifndef ALGORISMIA_CALCULSIMILITUD_H
#define ALGORISMIA_CALCULSIMILITUD_H
#endif //ALGORISMIA_CALCULSIMILITUD_H


#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include "calculSimilitud.cc"

using namespace std;

set<string> generateKShingles (int k, vector<string> paraules);

void calculaSimilitudTotesKs () ;


void calculSimilitud ();
