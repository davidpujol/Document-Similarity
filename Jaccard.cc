
using namespace std;

typedef vector<vector<int> > Matriu;

double jaccard_index(set<string> s1, set<string> s2){
	int size = s2.size();
	int unio = s1.size();
	int interseccio = 0;
	
	for (auto s: s2){
		if(s1.count(s) == 1) interseccio++;
		else unio++;
	}
	return double(interseccio) / double(unio);
}

double jaccard_distance(set<string> s1, set<string> s2){
	return 1 - jaccard_index(s1,s2);
}


//Retorna la similitud de Jaccard de dos documents a partir de la matriu de signatures minHash.
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