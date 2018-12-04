#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 
using namespace std;

int myrandom (int i) { return std::rand()%i;}

int main () {
	ifstream file;
  	file.open("input.txt");
	string str;
	vector <string> cjtParaules;
	while (getline(file, str)) if(str.size() > 0) cjtParaules.push_back(str);

	for (int i = 0; i < 20; ++i) {
		 // using built-in random generator:
  		random_shuffle (cjtParaules.begin(), cjtParaules.end());
  		// using myrandom:
  		random_shuffle (cjtParaules.begin(), cjtParaules.end(), myrandom);
		string nom = "fitxer" + to_string(i+1)+ ".txt";
		ofstream file(nom);
		for(int i = 0; i < cjtParaules.size(); ++i) {
			file << cjtParaules[i] << endl;
		}
		file.close();
	}
	
	return 0;
}
