#ifndef MINHASH_H
#define MINHASH_H

#include <set>
#include <vector>
#include "Minhash.cc"



#endif //ALGORISMIA_MINHASH_H

typedef vector<vector<int>> Matriu;

Matriu transposada(const Matriu & mat);

void calculSimilitudMinHash();

vector <int> calcularColumna(set <string> shingles, string cjtParaules);

