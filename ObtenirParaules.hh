#ifndef OBTENIRPARAULES_HH
#define OBTENIRPARAULES_HH

#include <vector>
#include <string>
#include "ObtenirParaules.cc"

using namespace std;

//totes les paraules de tots els N documents
vector < vector<string> > getMatrixParaules(int n);

//totes les paraules d'un document i
vector <string> llegirDocument(int i);

//string amb totes les paraules del document i
string llegirDocumentString(int i);

#endif
