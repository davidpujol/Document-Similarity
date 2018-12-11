#include "Minhash.h"

using namespace std;

#define N_DOCS 20

void transposada(vector<vector<int> &mat) {

}

void calculSimilitudMinHash() {
	set<string> shingles;
	vector<string> v;
	for(int i = 0; i < N_DOCS; i++) {
        vector<string> paraules = llegir_document(i);
        set<string> s = generateKShingles(4, paraules);
        shingles.insert(s.begin(), s.end());

        string cjtParaules = llegir_document(i);
        v.push(cjtParaules);

    }
	for (auto const &e: shingles)
		cout << e << ' ';
	cout << endl;

	vector<vector<int>> mat = vector<vector<int>>(vector<int>(shingles.size()),N_DOCS);
	for(int i = 0; i < N_DOCS; ++i) {
	    mat[i] = calcularColumna(shingles,v[i]);
	}

	
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

