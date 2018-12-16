
using namespace std;

typedef vector<vector<int> > Matriu;

/**
 * Calcula la interseccio i la unio dels dos conjunts i després en fa la divisio per trobar la similitud de Jaccard.
 * @param s1 Set dels k-shingles del primer document.
 * @param s2 Set dels k-shingles del segon document.
 * @return La similitud de jaccard d'aquests.
 */
double jaccard_index(set<string> s1, set<string> s2){
	int unio = s1.size();
	int interseccio = 0;
	
	for (auto s: s2){
		if(s1.count(s) == 1) interseccio++;
		else unio++;
	}
	return double(interseccio) / double(unio);
}

/**
 * Aproxima la similitud de Jaccard comparant les dues columnes dels dos documents i veient quin es el percentatge
 * de valors entre ells que coincideixen.
 * @param m La matriu de signatures minHash
 * @param j1 Index del primer document
 * @param j2 Index del segon document
 * @return La seva similitud de Jaccard.
 */
double jaccard_from_minHashMatrix (Matriu & m, int j1, int j2)
{
	//la matriu comença a 0 mentre que els documents estan numerats desde 1. Per tant els hi hem de restar 1
	int iguals = 0;
	for (int i=0; i < m.size(); ++i)
	{
		if (m[i][j1-1] == m[i][j2-1]) ++iguals;
	}
	return double(iguals) / double (m.size());
}