#include <vector>
#include <map>
#include "calculSimilitud.hh"
#include "Minhash.hh"
#include <cmath>
#include <functional>

typedef vector<uint32_t> V;
typedef vector<vector<int> > Matriu;

template<class T> class MyHash;

#define N_DOCS 20


int numShingles;
int valorA;

/**
 * Classe que ens permet calcular un hash value a partir de un valor genèric.
 */
template<> class MyHash<V> {
    public:
        std::size_t operator()(std::vector<uint32_t> const& vec) const {
            std::size_t seed = vec.size();
            for(auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
};


/**
 * Fa servir l'algorisme de LSH per a calcular els parells que son semblants, i que per tant tenen una similitud major
 * al threshold calculat. A més a més, calcula la seva similitud, pels parells trobats.
 * @param signatureMatrix Matriu de signatures minHash
 * @param band Numero de bands en els que la dividirem
 * @param r Nombre de funcions de minHash que ha de tenir cada band
 * @param k Tamany que té cada shingle.
 * @return Retorna un map de parells de enters que representaran els parells de documents que son semblands,
 * aixi com un double que representa la seva similitud.
 */
map< pair<int,int> , double> generateCandidates (Matriu & signatureMatrix, int band, int r, int k) {
    cout << "Band: " << band <<" / Valor r: " << r << " / Valor k: " << k << endl;

    map<pair<int,int>, double> candidates;  //map on  guardant els diferents candidats

    //Genera els candidat per al LSH

    hash<int> h; //to hash all rows of all bands.
    Matriu buckets (band, vector<int> (N_DOCS));
    vector<vector<vector<int> > > memLSH;
    memLSH.resize(band);
    for(int i= 0; i < band; ++i) {
        memLSH[i].resize(N_DOCS);
        for(int j = 0; j < N_DOCS; ++j) {
            memLSH[i][j].resize(r);
        }
    }

    for (int b = 0; b < band; b++) {   //iterem sobre totes les bands

        for (int c = 0; c < N_DOCS; c++) {  //iterem sobre totes les columnes
            //int a = 0;  //es pot simplement anar sumant els valors i al final aplicarli una funcio de hash???
            V vectorDunaBand;
            for (int row = 0; row < r; row++) {
                vectorDunaBand.push_back(signatureMatrix[b*r+row][c]);  //accedim a la posicio correponent de la signature matriu
            }

            //ara ja tenim a 'a' tots els valors de les r files de el document de la columna c.
            //ara calcularem el seu hash value i el ficarem a la seva posicio de buckets.
            unsigned int valor = MyHash<V>()(vectorDunaBand);

            buckets[b][c] = valor;
        }
    }

    //ens es igual que varios bands continguin candidats que siguin iguals, ja que al final calcularem al similitud de Jaccard per cadascun d'ells per
    //veure si realment el nombre de similars es superior o igual al threshold
    for (int b = 0; b < band; b++) {
        for (int c = 0; c < N_DOCS-1; c++) {    //processem tots els candidats possibles
            for (int k = c+1; k < N_DOCS; k++) {
                if (buckets[b][c] == buckets[b][k]) {
                    pair<int,int> p;
                    p.first = c;
                    p.second = k;   //creem el nostre pair amb els dos candidats
                    candidates[p]= 0;   //l'afegim al nostre map
                }
            }
        }
    }

    auto it = candidates.begin();    //no tindrem candidats repetits
    map<pair<int,int>,double> elements_similars;

    double base = (1.0/band);
    double exp = (1.0/r);
    double t = pow(base,exp);   // t = pow ((1/band), (1/r))
    cout << "Base:" << base << "  Exp:"<< exp << endl;

    cout << "Valor de t: " << t << endl;

    while (it != candidates.end()) {
        it->second = calculSimilitudAuxLSH (it->first.first, it->first.second, k);  //aqui calculem la similitud de dos documents

        if (it->second >= t) {
            elements_similars[it->first] = it->second;
        }

        it++;
    }
    return elements_similars;

}

/**
 * Els mostra per pantalla.
 * @param a El map amb els parells candidats i la seva similitud de Jaccard.
 */
void showMap (map<pair<int,int>,double> &a)
{
    for (auto it : a)
    {
        cout << "El document " << it.first.first << " és similar al document " << it.first.second << endl;
        cout << "La seva similitud és de " << it.second << endl << endl;
    }
}

/**
 * Menu principal on l'usuari introdueix els valors de k, el nombre de bands i de r que vol fer servir per a l'algorisme.
 * A continuacio es calculen els parells similars i finalment es mostren per pantalla amb la seva similitud concreta.
 */
void calculaLocalSensitiveHashing ()
{
    int bands, r,k;
    cout <<"Introdueix la k que vols utilitzar: " << endl;
    cin >> k;
    numShingles = k;

    cout << "Introdueix el nombre de bands : (valor recomanat 100)" << endl;
    cin >> bands;

    cout << "Introdueix el nombre de files per banda \"r\" : (valor recomanat 5)" << endl;
    cin >> r;

    Matriu a = calculaMinHashMatrix(k,bands*r);

    //Càlcul Funció Hash

    map<pair<int,int>, double> result = generateCandidates(a, bands, r , k);
    showMap(result);


}