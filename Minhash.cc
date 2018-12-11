#include "ObtenirParaules.hh"
#include <vector>
using namespace std;

#define N_DOCS 20

typedef vector<vector<int>> Matriu;

Matriu transposada(const Matriu & mat) {
    int cols = mat.size();
    int files = mat[0].size();
    Matriu m = Matriu(files,vector<int>(cols));
    for(int i = 0; i < cols; ++i) {
		for(int j = 0; j < files;++j) {
		    m[j][i] = mat[i][j];
		}
    }
    return m;
}

vector <int> calcularColumna(set <string> shingles, string cjtParaules) {
    vector <int> col(shingles.size(), 0);
    int pos = 0;
    for (auto s: shingles) {
        if(cjtParaules.find(s) < cjtParaules.size())
        {
            col[pos] = 1;
        }
        ++pos;
    }
    return col;
}


void calculSimilitudMinHash() {
	set<string> shingles;
	vector<string> v;
	for(int i = 0; i < N_DOCS; i++) {
        string paraules = llegirDocumentString(i);
        set<string> s = generateKShingles(4, paraules);
        shingles.insert(s.begin(), s.end());
        v.push_back(paraules);
    }
	for (auto const &e: shingles)
		cout << e << ' ';
	cout << endl;

	Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
	for(int i = 0; i < N_DOCS; ++i) {
	    mat[i] = calcularColumna(shingles,v[i]);
	}
	mat = transposada(mat);

}



