#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

/**
 * @param i Index del document a llegir
 * @return Document llegit en forma de string i amb un sol espai entre paraula i paraula
 */
 string llegirDocumentString(int i) {
     ifstream file;
	 file.open("/Users/david/Documents/UPC/Quatri5/SimilitudDocuments/generadorDocuments/fitxer"+to_string(i)+".txt");
	 string res = "";
     string str;
	 while (getline(file, str)) if(str.size() > 0) res += str + " ";
	 return res;
 }
