#include "ObtenirParaules.hh"
#include <vector>
using namespace std;

#define N_DOCS 20
#define INF 10000000

typedef vector<vector<int>> Matriu;

int nShingles;


int randomNumber(int max, int min) {
	return rand()%(max-min + 1) + min;
}

/*
 * INPUT: v = res sera el vector amb els diferents numeros primers
 *        x = el nou numero primer que estem comprovant
 * La funcio comprovara que no hem seleccionat ja aquest numero primer.
 */
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
	return res;
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

int universalHashing(int a, int x, int b, int m){
    //h(x) = (ax+b) mod n
    return (a*x+b)%m;
}

int funcioHash(int a, int x) {
    return universalHashing(a, x, 1, nShingles);
}

Matriu signaturesMinHash(const vector<int> hash, const Matriu & mat) {
    Matriu sig = Matriu(hash.size(), vector<int>(mat[0].size(),INF));   //tenim una fila per cada funcio de hash i una columna per document

    for(int i = 0; i < mat.size(); ++i) {
        vector<int> hi; //tindra tants valors com funcions de hash tinguem

        for (auto h: hash) {
            hi.push_back(funcioHash(h,i));  //calculem el valor de hash per cadascun dels index, entre 0 i mat.size()
        }
        for(int j = 0; j < mat[0].size(); ++j) {    //per cada columna
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
    return sig;
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

	nShingles = shingles.size();
	/*for (auto const &e: shingles)
		cout << e << ' ';
	cout<< endl;
	*/

    Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
    for (int i = 0; i < N_DOCS; ++i) {
        mat[i] = calcularColumna(shingles, v[i]);
    }
    mat = signaturesMinHash(obtenirVectorA(1000, shingles.size()), transposada(mat));
    cout << "Hem calculat la matriu i ens ha donat" << endl;

    for (int i =0; i < mat.size(); ++i) {
        for (int j=0; j < mat[0].size();++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return mat;
}

void calculaMinHashSimilarity ()
{
	cout << "Introdueix els dos documents que vols comparar" << endl;
	int ind1, ind2;
	cin >> ind1 >> ind2;

	Matriu m = calculaMinHashMatrix();
	double similitud = jaccard_from_minHashMatrix(m, ind1, ind2);
	cout << "La similitud entre els dos documents es: " << similitud << endl;
}