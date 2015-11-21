#include <iostream>
#include <fstream>
#include <locale.h>
#include <algorithm>
#include <vector>
#include <ctime> 
#include <cstdlib>

using namespace std;

const int m = 5;
const int n = 7;

void createQuad(int **quad, string d);
int r(int i) { return rand() % i; }

void main() {
	setlocale(LC_ALL, "rus");
	std::srand(unsigned(std::time(0)));

	string dictionary = "אבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ .,"; //בוח ¸

	int **quad = new int*[m];
	for (int i = 0; i < m; i++) {
		quad[i] = new int[n];
	}
	
	createQuad(quad, dictionary);
	
	system("pause");
}

void createQuad(int **quad, string d) {
	vector<int> v;
	for (int i = 0; i < d.length(); i++) 
		v.push_back(i);
	random_shuffle(v.begin(), v.end(), r);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			quad[i][j] = v[i * n + j];
		}
	}

	ofstream of("key.txt");
	of << m << " " << n << endl;
	for (int i = 0; i < d.length(); i++)
	{
		of << v[i] << " ";
	}
	of.close();
}