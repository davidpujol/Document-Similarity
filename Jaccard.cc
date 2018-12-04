#include <iostream>
#include <set>
#include <Jaccard.hh>
using namespace std;



double jaccard_index(set<string> s1, set<string> s2){
	int size = s2.size();
	int unio = s1.size();
	int interseccio = 0;
	
	for (auto s: s2){
		if(s1.count(s) == 1) interseccio++;
		else unio++;
	}
	cout << interseccio << ", " << unio << endl;
	return double(interseccio) / double(unio);
}

double jaccard_distance(set<string> s1, set<string> s2){
	return 1 - jaccard_index(s1,s2);
}
