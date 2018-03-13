/* 
 * QAP problem for benchmarking GHOST framework
 * to use your own files, be sure to use following syntax :
 * nbWarehouse
 * optimal value
 * 
 * Flux matrix (value separated with tabs and newline)
 *
 * Distance matrix
 */

#include <vector>
#include <string>
#include <ifstream>
#include <iostream>
#include <algorithm>

using namespace ghost;
using namespace std;

void loadQAP(ifstream& file, int[][] flux, int[][] distances) {

}

int main(int argc, char **argv) {

	string filename = "char12.dat";
	int sat = 20;
	int opt = 30;
	
	if( argc > 1 )
		filename = argv[1];
	if( argc > 2 )
		sat = stoi(argv[2]);
	if( argc > 3 )
		opt = stoi(argv[3]);

	ifstream file("data/"+filename, ios::in);

	int nbWare = file.getline();
	int optimum = file.getline();
	int[nbWare][nbWare] flux, distances;

	for (int i = 0; i < nbWare, ++i) {
		for (int j = 0; j < nbWare, ++j) {
			
		}
	}

}