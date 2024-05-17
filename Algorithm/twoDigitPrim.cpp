#include<iostream>
#include<fstream>
#include<string>
#include<memory.h>
using namespace std;

long long num = 100000;
bool eratosthenes[100001];

void findPrime() {
	for (long long i = 2; i*i<= num; i++) {
		if (eratosthenes[i]) {
			for (long long k = i*i; k <= num; k+=i) {
				eratosthenes[k] = false;
			}
		}
	}
}

bool findTwoPrime(int num) {
	string sNum = to_string(num);
	int len = sNum.length();

	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			if (i != j) {
				int tNum = (sNum[i] - '0') * 10 + (sNum[j] - '0');
				if(tNum>=10 && tNum<=99)
				if (eratosthenes[tNum])return true;
			}
		}
	}

	return false;
}

int main() {
	ifstream fin("twoDigitPrime.inp");
	ofstream fout("twoDigitPrime.out");
	memset(eratosthenes, true, sizeof(eratosthenes));

	int t; fin >> t;
	eratosthenes[0] = false;
	eratosthenes[1] = false;
	findPrime();

	for (int i = 0; i < t; i++) {
		int a, b; fin >> a >> b;
		int cnt = 0;
		for (int j = a; j <= b; j++) {
			if (findTwoPrime(j))cnt++;
		}

		fout << cnt<<endl;
		cout << cnt<<endl;
	}

	fin.close();
	fout.close();
}
