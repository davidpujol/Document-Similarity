#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define N_DOCS 20

int main() {
	<string> shingles;
	for(int i = 0; i < N_DOCS; i++) {
		vector<string> paraules = llegir_document(i);
		set<string> s = generateKShingles(4,paraules);
		shingles.insert(s.begin(), s.end());
	}
	for (auto const &e: s)
		cout << e << ' ';
	cout << endl;
	
}
