#ifndef MINHASH_H
#define MINHASH_H


#include "Minhash.cc"

typedef vector<vector<int>> Matriu;

Matriu transposada(const Matriu & mat);

Matriu calculaMinHashMatrix();

vector <int> calcularColumna(set <string> shingles, string cjtParaules);

void calculaMinHashSimilarity();

#endif