#ifndef MINHASH_H
#define MINHASH_H

#include <set>
#include <vector>
#include "Minhash.cc"

typedef vector<vector<int>> Matriu;

int randomNumber(int max, int min);
bool conteValor(vector<int> v, int x);
vector <int> obtenirVectorA(int n, int numSH);

Matriu transposada(const Matriu & mat);

void calculSimilitudMinHash();

vector <int> calcularColumna(set <string> shingles, string cjtParaules);

#endif
