int k = 5;
int N = 500; //number of hash functions
int b = 100; //number of bands
int r = 5;   //number of row per band
double t;    //threshold

void getParametres ()
{
    int bands;
    cout << "Introdueix el nombre de bands : (valor recomanat 100)" << endl
    cin >> bands;
}

void generateCandidates() {
    //Genera els candidat per al LSH
    hash<string> h; //to hash all rows of all bands.
    vector <vector<int> > buckets(b, vector<int> (ndocs)); //vector[i] -> vector<int> on cada int és el bucket de la fila r

    for (int band = 0; band < b; band++) {
        for (int c = 0; c < ndocs; c++) {
            char aux[r];
            for (int row = 0; row < r; row++) {
                aux[row] = SM[band*r+row][c];
            }
            //at this point, a single row is computed.
            string aux1 = aux;
            buckets[band][c] = h(aux1);
        }
    }

    //processing candidates;
    for (int band = 0; band < b; band++) {
        for (int c = 0; c < ndocs-1; c++) {
            for (int k = c+1; k < ndocs; k++) {
                if (buckets[band][c] == buckets[band][k]) {
                    pair<int,int> p;
                    p.first = c;
                    p.second = k;
                    candidates[p]= 0;
                }
            }
        }
    }

    std::map<pair<int,int>,double>::iterator it = candidates.begin();

    while (it != candidates.end()) {
        it->second = jaccardSimilarity(it->first.first, it->first.second);
        it++;
    }

}