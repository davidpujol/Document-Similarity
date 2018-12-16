#include "ObtenirParaules.hh"
#include <vector>

using namespace std;

#define N_DOCS 20
#define INF 10000000

typedef vector<vector<int> > Matriu;

int nShingles;  //numero de shingles que tenim

/**
 *
 * @param mat Matriu de la que partim.
 * @return La matriu transposada.
 */
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

/**
 *
 * @param shingles Set amb la unio de tots els shingles de tots els documents.
 * @param cjtParaules Document que ara volem comparar
 * @return Un vector on cada posicio pot tenir 1 o 0. 0 si el document no conte aquell shingle, i 1 altrament.
 */
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

/**
 * Fa el calcul de una funcio de Universal Hashing i calcula el hash value per un valor x amb aquesta funcio
 * @param x Valor inicial que volem transformar
 * @return Hash value.
 */
int universalHashing(int x){
    //h(x) = ((ax+b) mod p) mod m
    int a = rand();
    int b = rand();
    long r = a*x + b;
    r = r % 8713;   //modul per un primer >= m
    return r % nShingles;
}

/**
 * Crida una funcio que calculara el hash value pel valor x.
 * @param x Valor inicial que volem transformar.
 * @return Hash value
 */
int funcioHash(int x) {
    return universalHashing(x);
}

/**
 * Fa el calcul de la matriu de signatures minHash pels nostres documents.
 * @param f Nombre de funcions de minHash que volem que faci servir la nostre taula.
 * @param mat La matriu caracteristica dels nostres documents
 * @return La matriu de signatures minHash.
 */
Matriu signaturesMinHash(int f, const Matriu & mat) {
    Matriu sig = Matriu(f, vector<int>(mat[0].size(),INF));   //tenim una fila per cada funcio de hash i una columna per document

    for(int i = 1; i <= mat.size(); ++i) {
        vector<int> hi; //tindra tants valors com funcions de hash tinguem

        for (int j=0; j < f; ++j){
            hi.push_back(funcioHash(i));  //calculem el valor de hash per cadascun dels index, entre 1 i mat.size()
        }

        for(int j = 0; j < mat[0].size(); ++j) {    //per cada columna
            if(mat[i-1][j] == 1) {
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

/**
 * Fa el calcul de la matriu de signatures minHash pels nostres documents.
 * @param k Tamany dels shingles.
 * @param f Nombre de funcions de minHash que volem usar per a construir la matriu.
 * @return La matriu de signatures minHash
 */
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

    Matriu mat = Matriu(N_DOCS, vector<int>(shingles.size()));
    for (int i = 0; i < N_DOCS; ++i) {
        mat[i] = calcularColumna(shingles, v[i]);
    }

    mat = signaturesMinHash(f, transposada(mat));

    return mat;
}

/**
 * Calcula una aproximacio de la similitud de Jaccard per a dos documents donats, per una k donada i un nombre de funcions donat.
 */
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

/**
 * Calcula una aproximacio de la similitud de Jaccard per a dos documents donats, per un nombre de funcions donat
 * i per valors de k que estiguin entre 1 i 10.
 */
void calculaMinHashSimilarityTotesKs ()
{
    int f;
    cout << "Introdueix el numero de funcions de minHash a utilitzar: " << endl;
    cin >> f;

    cout << "Introdueix els dos documents que vols comparar" << endl;
    int ind1, ind2;
    cin >> ind1 >> ind2;

    for (int k=1; k <= 10; ++k)
    {
        Matriu m = calculaMinHashMatrix (k, f);
        double similitud = jaccard_from_minHashMatrix (m, ind1, ind2);
        cout << "La similitud entre els dos documents amb k = " << k << " es: " << similitud << endl;
    }
}

/**
 * Calcula una aproximacio de la similitud de Jaccard per una k donada i un nombre de funcions donat,
 * pero per tots els parells de documents possibles donats els 20 documents calculats inicialment.
 */
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