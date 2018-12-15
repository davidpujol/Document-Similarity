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
//vector <int> f; //f[]: (ax + b)mod numShingles


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


map< pair<int,int> , double> generateCandidates (Matriu & signatureMatrix, int band, int r, int k) {
    cout << "Band: " << band <<" / Valor r: " << r << " / Valor k: " << k << endl;

    map<pair<int,int>, double> candidates;  //map on  guardant els diferents candidats

    //Genera els candidat per al LSH

    hash<int> h; //to hash all rows of all bands.
    //vector <vector<int> > buckets (band, vector<int> (N_DOCS)); //Matriu on tenim tantes files com bands i tantes columnes com documents (per anar guardant el hash value correponent)
    //vector <vector<int> > buckets (band, vector<int> (N_DOCS)); //Matriu on tenim tantes files com bands i tantes columnes com documents (per anar guardant el hash value correponent)
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
            //cout << "Anem a calcular la funcio de hash " << endl;
            //cout<< "Band: " << b << "  document: " << c;
            unsigned int valor = MyHash<V>()(vectorDunaBand);
            //cout << valor << endl;
            buckets[b][c] = valor;    //no funciona el calcul de el hash value !!!!!!!!!!!!!!!!!!! <---------
            //cout << " - Valor funció de hash mapejant vectors " << buckets[b][c] <<  endl;
        }
        //cout << "b"<<endl;
    }

    //cout << "Hem assignat els buckets" << endl;
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
                    //cout << "Band: " << b << " Doc1: " << c << " Doc2: " << k << "sameVector" << endl;
                }
            }
        }
    }

    //cout << "Hem calculat les funcions de hash" << endl;

    auto it = candidates.begin();    //no tindrem candidats repetits
    map<pair<int,int>,double> elements_similars;
    //cout << "Band:" << band << " R:" << r << endl;
    double base = (1.0/band);
    double exp = (1.0/r);
    double t = pow(base,exp);
    cout << "Base:" << base << "  Exp:"<< exp << endl;
    //double t = pow((1/band),(1/r));
    cout << "Valor de t: " << t << endl;

    while (it != candidates.end()) {
        it->second = calculSimilitudAuxLSH (it->first.first, it->first.second, k);  //aqui calculem la similitud de dos documents

        if (it->second >= t) {
            elements_similars[it->first] = it->second;
            //cout << "dins de t" << endl;
        }

        it++;
    }
    //cout << "Retornem"<<endl;
    return elements_similars;

}

void showMap (map<pair<int,int>,double> &a)
{
    for (auto it : a)
    {
        cout << "El pair " << it.first.first << " " << it.first.second << " es similar" << endl;
        cout << "Té similitud " << it.second << endl;
    }
}

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

    cout << "Anem a calcular la matriu" << endl;
    Matriu a = calculaMinHashMatrix(k,bands*r);
    cout << "Anem a calcularLSH" << endl;

    //Càlcul Funció Hash



    map<pair<int,int>, double> result = generateCandidates(a, bands, r , k);
    showMap(result);


}