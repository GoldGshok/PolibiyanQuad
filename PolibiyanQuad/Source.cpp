#include <iostream>
#include <fstream>
#include <locale.h>
#include <algorithm>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>

using namespace std;

const int m = 5;
const int n = 7;

string readFile();
void writeFile(string &text);
void createQuad(char **quad, string d);
string toLower(string &text);
string delSymbol(string &text);
string polibiyan(string &text, char **quad);
int r(int i) { return rand() % i; }

void main() {
	setlocale(LC_ALL, "rus");
	std::srand(unsigned(std::time(0)));

	//русский алфавит + '.' ',' ' '
	string dictionary = "абвгдежзийклмнопрстуфхцчшщъыьэюя .,"; //без ё
	string text;

	//создание квадрата m*n
	char **quad = new char*[m];
	for (int i = 0; i < m; i++) {
		quad[i] = new char[n];
	}
	
	//заполняем квадрат
	createQuad(quad, dictionary);

	/*for (int i = 0; i < m; i++) // просмотр квадрата (для отладки)
	{
		for (int j = 0; j < n; j++) {
			cout << quad[i][j] << " ";
		}
		cout << endl;
	}*/
	
	//читаем исходный текст из файла
	text = readFile();
	
	//убираем лишние символы приводим регистр букв
	text = delSymbol(text);
	text = toLower(text);

	//шифруем текст
	text = polibiyan(text, quad);
	
	//write text in File
	writeFile(text);
	
	//system("pause");
}

void createQuad(char **quad, string d) {
	vector<int> v;
	for (int i = 0; i < d.length(); i++) 
		v.push_back(i);
	random_shuffle(v.begin(), v.end(), r);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			quad[i][j] = d[v[i * n + j]];
		}
	}

	ofstream of("key.txt");
	of << m << " " << n << endl;
	for (int i = 0; i < d.length(); i++)
	{
		of << v[i] << " ";
	}
	of << endl << d;
	of.close();
}

string readFile() {
	// read text
	string text;
	ifstream f("input.txt");
	f.seekg(0, ios_base::end);
	text.resize(f.tellg());
	f.seekg(0, ios_base::beg);

	f.read((char*)text.data(), text.size());
	f.close();
	return text;
}

string toLower(string &text) {
	string temp;
	for (int i = 0; i < text.length(); i++) {
		temp += tolower(text[i]);
	}
	return temp;
}

string delSymbol(string &text) {
	string temp;
	for (int i = 0; i < text.length(); i++)
		if (text[i] == '\n' || text[i] == '?' || text[i] == '!' || text[i] == ':' || text[i] == '"') //text[i] == '.' || text[i] == ',' || text[i] == ' '
			continue;
		else
			temp += text[i];
	return temp;
}

string polibiyan(string &text, char **quad) {
	string temp;
	int k = 0;
	while (k < text.length()) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (quad[i][j] == text[k]) {
					if (i != m - 1) {
						temp += quad[i + 1][j];
						break;
					}
					else {
						temp += quad[0][j];
						break;
					}
				}
			}
		}
		k++;
	}
	return temp;
}

void writeFile(string &text) {
	ofstream of("output.txt");
	of << text;
	of.close();
}