#ifndef MINHASH_H
#define MINHASH_H

#include "Minhash.cc"

typedef vector<vector<int> > Matriu;

int universalHashing(int x);

Matriu transposada(const Matriu & mat);

Matriu calculaMinHashMatrix();

vector <int> calcularColumna(set <string> shingles, string cjtParaules);

void calculaMinHashSimilarity();

void calculaMinHashSimilarityTotesKs ();

void calculaMinHashSimilarityTots ();

#endif