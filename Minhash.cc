#include "Minhash.h"

using namespace std;

#define N_DOCS 20

void calculSimilitudMinHash() {
	<string> shingles;
	for(int i = 0; i < N_DOCS; i++) {
		vector<string> paraules = llegir_document(i);
		set<string> s = generateKShingles(4,paraules);
		shingles.insert(s.begin(), s.end());
	}
	for (auto const &e: s)
		cout << e << ' ';
	cout << endl;
	
}


vector <int> calcularColumna(set <string> shingles, string cjtParaules) {
	vector <int> col(shingles.size(), 0);
	int pos = 0;
	for (auto s: shingles) {
		if(cjtParaules.find(s) < cjtParaules.size()){ col[pos] = 1;  }
		++pos;
	}
	return col;
}