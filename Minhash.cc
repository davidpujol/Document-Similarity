#include "ObtenirParaules.hh"
#include <vector>
using namespace std;

#define N_DOCS 20
#define INF 10000000

typedef vector<vector<int>> Matriu;

int nShingles;

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
	nShingles = shingles.size();
	for (auto const &e: shingles)
		cout << e << ' ';
	cout << endl;

	Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
	for(int i = 0; i < N_DOCS; ++i) {
	    mat[i] = calcularColumna(shingles,v[i]);
	}
	mat = signaturesMinHash(obtenirVectorA(5,shingles.size())),transposada(mat);

}
int universalHashing(int a, int x, int b, int m){
    //h(x) = (ax+b) mod n
    return (a*x+b)%m;
}

int funcioHash(int a, int x) {
    return universalHashing(a, x, 1, nShingles);
}

Matriu signaturesMinHash(const vector<int> hash, const Matriu & mat) {
    Matriu sig = Matriu(hash.size(), vector<int>(mat[0].size(),INF));

    for(int i = 0; i < mat.size(); ++i) {
        vector<int> hi;
        for (auto h: hash) {
            hi.push_back(funcioHash(h,i));
        }
        for(int j = 0; j < mat[0].size(); ++j) {
            int c = mat[i][j];
            if(c == 1) {
                for(int h = 0; h < hi.size(); ++h) {
                   if(hi[h] < sig[h][j]) {
                        sig[h][j] = hi[h];
                   }
                }
            }
        }
    }
}
