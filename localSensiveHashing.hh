#ifndef ALGORISMIA_LOCALSENSIVEHASHING_H
#define ALGORISMIA_LOCALSENSIVEHASHING_H

#endif //ALGORISMIA_LOCALSENSIVEHASHING_H

#include "localSensiveHashing.cc"

using namespace std;


void calculaLocalSensitiveHashing ();

map<pair<int,int>, double> generateCandidates(Matriu & signatureMatrix);

void showMap (map<pair<int,int>,double> &a);