#include <vector>
#include <map>


typedef vector<vector<int> > Matriu;

vector<int> getParametres ()
{

    int bands, r,k;
    cout <<"Introdueix la k que vols utilitzar: " << endl;
    cin >> k:

    cout << "Introdueix el nombre de bands : (valor recomanat 100)" << endl
    cin >> bands;

    cout << "Introdueix el nombre de files per banda : (valor recomanat 5)" << endl;
    cin >> r;

    vector<int> result;
    result.push_back(k);
    result.push_back(bands);
    result.push_back(r);
}

map<pair<int,int>, double> generateCandidates(Matriu & signatureMatrix) {
    //calculem el nombre de bands i de files per band
    int bands, r,k;
    vector<int> a = getParametres();
    k = a[0];
    bands = a[1];
    r = a[2];

    map<pair<int,int>, double> candidates;  //map on anem guardant els diferents candidats

    vector<vector <bool> > CM;


    //Genera els candidat per al LSH

    hash<int> h; //to hash all rows of all bands.
    vector <vector<int> > buckets (bands, vector<int> (N_DOCS)); //Matriu on tenim tantes files com bands i tantes columnes com documents (per anar guardant el hash value correponent)

    for (int b = 0; b < bands; b++) {   //iterem sobre totes les bands
        for (int c = 0; c < N_DOCS; c++) {  //iterem sobre totes les columnes
            //char aux[r];
            int a = 0;  //es pot simplement anar sumant els valors i al final aplicarli una funcio de hash???

            for (int row = 0; row < r; row++) {
                a += signatureMatrix[band*r+row][c];  //accedim a la posicio correponent de la signature matriu
            }

            //ara ja tenim a 'a' tots els valors de les r files de el document de la columna c.
            //ara calcularem el seu hash value i el ficarem a la seva posicio de buckets.

            buckets[band][c] = h(a);
        }
    }

    //ens es igual que varios bands continguin candidats que siguin iguals, ja que al final calcularem al similitud de Jaccard per cadascun d'ells per
    //veure si realment el nombre de similars es superior o igual al threshold
    for (int b = 0; b < b; b++) {
        for (int c = 0; c < N_DOCS-1; c++) {    //processem tots els candidats possibles
            for (int k = c+1; k < N_DOCS; k++) {
                if (buckets[band][c] == buckets[band][k]) {
                    pair<int,int> p;
                    p.first = c;
                    p.second = k;   //creem el nostre pair amb els dos candidats
                    candidates[p]= 0;   //l'afegim al nostre map
                }
            }
        }
    }

    map<pair<int,int>,double>::iterator it = candidates.begin();    //no tindrem candidats repetits
    map<pair<int,int>,double> elements_similars;
    double t = pow((1/bands),(1/r));

    while (it != candidates.end()) {
        it->second = calculSimilitud(it->first.first, it->first.second, k);  //aqui calculem la similitud de dos documents

        if (it->second > t)
            elements_similars[it->first] = it->second;

        it++;
    }

    return elements_similars;

}

void showMap (map<pair<int,int>,double> &a)
{

}