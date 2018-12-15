#include "ObtenirParaules.hh"
#include <vector>

using namespace std;

#define N_DOCS 20
#define INF 10000000

typedef vector<vector<int> > Matriu;

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
            if(mat[i][j] == 1) {
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


Matriu calculaMinHashMatrix(int k, int f) {
    set<string> shingles;
    vector<string> v;    //un vector en el que anem guardant les strings que representen la totalitat dels documents

    for (int i = 1; i <= N_DOCS; i++) {
        string paraules = llegirDocumentString(i);
        set<string> s = generateKShingles(k, paraules);
        shingles.insert(s.begin(), s.end());
        v.push_back(paraules);
    }

	nShingles = shingles.size();
//<<<<<<< HEAD
    /*
	for (auto const &e: shingles)
		cout << e << ' ';
	cout<< endl;
    */
//=======
//>>>>>>> d427fd1f96ff3c080ea58caefa9af812449c776d

    Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
    for (int i = 0; i < N_DOCS; ++i) {
        mat[i] = calcularColumna(shingles, v[i]);
    }

    mat = signaturesMinHash(obtenirVectorA(f, shingles.size()), transposada(mat));
    /*cout << "Hem calculat la matriu i ens ha donat" << endl;

    for (int i =0; i < mat.size(); ++i) {
        for (int j=0; j < mat[0].size();++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }*/

    return mat;
}


void calculaMinHashSimilarity ()
{
    cout << "Introdueix el numero k de k-shingles:" << endl;
    int k,f;
    cin >> k;
    cout << "Introdueix el numero de funcions de minHash a utilitzar:" << endl;
	cin >> f;
    cout << "Introdueix els dos documents que vols comparar" << endl;
	int ind1, ind2;
	cin >> ind1 >> ind2;

	Matriu m = calculaMinHashMatrix(k,f);
	double similitud = jaccard_from_minHashMatrix(m, ind1, ind2);
	cout << "La similitud entre els dos documents es: " << similitud << endl;
}


void calculaMinHashSimilarityTotesKs ()
{
    int f;
    cout << "Introdueix el numero de funcions de minHash a utilitzar: " << endl;
    cin >> f;

    cout << "Introdueix els dos documents que vols comparar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;

    for (int i=1; i <= 10; ++i)
    {
        Matriu m = calculaMinHashMatrix (i, f);
        double similitud = jaccard_from_minHashMatrix (m, ind1, ind2);
        cout << "La similitud entre els dos documents amb k = " << i << " es: " << similitud << endl;
    }
}


void calculaMinHashSimilarityTots () {
    cout<< "Introdueix el valor k per al calcul dels k-shingles:" << endl;
    int k;
    cin >> k;

    cout << "Introdueix el numero de funcions de minHash que vols usar: "<<endl;
    int f;
    cin >> f;

    unsigned t0, t1;
    t0 = clock();

    cout << "DOCS";
    for (int i = -1; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(i == -1) {   //la primera fila
                if (j==0) cout << "  | " << j+1;
                else if (j/10 == 0) cout << "     | " << j+1;
                else cout << "    | " << j+1;
            }
            else {  //la primera columna
                if (j == 0) {
                    if (i / 10 == 0) cout << i << "    ";
                    else cout << i << "   ";
                }
                Matriu m = calculaMinHashMatrix (k, f);
                double similitud = jaccard_from_minHashMatrix(m, i+1, j+1);
                cout << " | " << std::fixed << std::setprecision(3) << similitud;
            }
        }
        cout << endl;
    }

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "El temps d'execucio en calcular totes les similituds per k = "<< k << " és " << time << " segons." << endl;


}