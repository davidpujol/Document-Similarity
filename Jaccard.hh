#ifndef JACCARD_HH
#define JACCARD_HH

#include <iostream>
#include <set>
#include "Jaccard.cc"

using namespace std;


double jaccard_index(set<string> s1, set<string> s2);


double jaccard_distance(set<string> s1, set<string> s2);

#endif
