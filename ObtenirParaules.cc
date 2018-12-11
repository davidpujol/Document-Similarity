#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

vector < vector<string> > getMatrixParaules(int numDocuments) {
	vector < vector<string> > cjtParDoc;
	for (int i=0; i < numDocuments; ++i) {
		string nom = "./generadorDocuments/fitxer" + to_string(i+1) + ".txt";
		ifstream file;
		file.open(nom);
		string str;
		while (getline(file, str)) if(str.size() > 0) cjtParDoc[i].push_back(str);

	}
	return cjtParDoc;
 }

 vector <string> llegirDocument(int i) {
	 ifstream file;
	 file.open("./generadorDocuments/fitxer"+to_string(i)+".txt");

	 string str;
	 vector <string> cjtParaules;
	 while (getline(file, str)) if(str.size() > 0) cjtParaules.push_back(str);
	 return cjtParaules;
 }

 string llegirDocumentString(int i) {
     ifstream file;
	 file.open("./generadorDocuments/fitxer"+to_string(i)+".txt");
	 if (file.is_open()) cout << "hem pogut obrir el document index" << i << endl;
	 else cout << "No l'hem pogut obrir" << endl;

	 string res = "";
     string str;
	 while (getline(file, str)) if(str.size() > 0) res += str + " ";
	 return res;
 }
