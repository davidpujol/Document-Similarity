#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 
using namespace std;

vector < vector<string> > getMatrixParaules() {
	vector < vector<string> > cjtParDoc;
	for (int i=0; i < 20; ++i) {
		string nom = "fitxer" + to_string(i+1) + ".txt";
		ifstream file;
		file.open(nom);
		string str;
		while (getline(file, str)) if(str.size() > 0) cjtParDoc[i].push_back(str);

	}
	return cjtParDoc;
 }

 vector <string> llegirDocument(int i) {
	 ifstream file;
	 file.open("fitxer"+to_string(i)+".txt");
	 string str;
	 vector <string> cjtParaules;
	 while (getline(file, str)) if(str.size() > 0) cjtParaules.push_back(str);
	 return cjtParaules;
 }