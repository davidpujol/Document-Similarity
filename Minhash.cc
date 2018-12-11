#include "ObtenirParaules.hh"
#include <vector>
using namespace std;

#define N_DOCS 20

#include <set>
#include <vector>

typedef vector<vector<int>> Matriu;


int randomNumber(int max, int min) {
	return rand()%(max-min + 1) + min;
}

bool conteValor(vector<int> v, int x) {
	for(int i = 0; i<v.size(); ++i) {
		if(v[i] == x)return true;
	}
	return false;
}

/*
	INPUT: n= num de funcions que es vol
	       numSH = num de shingles
*/
vector <int> obtenirVectorA(int n, int numSH) {
	vector <int> res(n, -1);
	for (int i = 0; i < n; ++i) {
		bool acabat = false;
		int x;
		while (not acabat) {
			x = randomNumber(numSH, 0);
			if((x % 2 != 0) && (not conteValor(res, x))) acabat = true;
		}
		res[i] = x;
	}
}


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


Matriu calculaMinHashMatrix() {
    set<string> shingles;
    vector<string> v;    //un vector en el que anem guardant les strings que representen la totalitat dels documents
    for (int i = 1; i <= N_DOCS; i++) {
        string paraules = llegirDocumentString(i);
        set<string> s = generateKShingles(4, paraules);
        shingles.insert(s.begin(), s.end());
        v.push_back(paraules);
    }

    for (auto const &e: shingles)
        cout << e << ' ';
    cout << endl;

    Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
    for (int i = 0; i < N_DOCS; ++i) {
        mat[i] = calcularColumna(shingles, v[i]);
    }
    mat = signaturesMinHash(obtenirVectorA(5, shingles.size())), transposada(mat);
    return mat;
}

void calculaMinHashSimilarity ()
{
	cout << "Introdueix els dos documents que vols comprar" << endl;
	int ind1, ind2;
	cin >> ind1 >> ind2;

	Matriu m = calculaMinHashMatrix();
	double similitud = jaccard_from_minHashMatrix(m, ind1, ind2);
	cout << "La similitud entre els dos documents es: " << similitud << endl;
}


Matriu signaturesMinHash(const vector<int> hash, const Matriu & mat) {

}
