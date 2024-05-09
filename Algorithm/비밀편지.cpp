#include <iostream>
#include <fstream>
using namespace std;

string letter[8] = { "000000A","001111B","010011C","011100D","100110E","101001F","110101G","111010H" };

char translator(char l[6]) {
	int cnt[8] = { 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (letter[i][j] == l[j])cnt[i]++;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (cnt[i] > 4) {
			return letter[i][6];
		}
	}
	return 'X';
}

int main() {
	ifstream fin("mail.inp");
	ofstream fout("mail.out");

	int t; fin >> t;

	for (int i = 0; i < t; i++) {
		int num; fin >> num;
		for (int j = 0; j < num; j++) { // 글자 개수
			char l[6];
			for (int k = 0; k < 6; k++) { // 글자는 6문자로 구성
				fin >> l[k];
			}
			fout<<translator(l);
			//cout<<translator(l);
		}
		fout << endl;
		//cout << endl;
	}

	fin.close();
	fout.close();
}
