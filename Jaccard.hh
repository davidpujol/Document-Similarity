#ifndef JACCARD_HH
#define JACCARD_HH

#include <iostream>
#include <set>
#include "Jaccard.cc"

using namespace std;


double jaccard_index(set<string> s1, set<string> s2);


double jaccard_from_minHashMatrix (Matriu & m, int j1, int j2);

#endif
