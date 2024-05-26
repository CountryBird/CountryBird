#include<iostream>
#include<fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream fin("transform.inp");
ofstream fout("transform.out");

vector<int> number;
string bracket;

void num2Bracket(vector<int> number) {
	stack<int> s;
	int current = 1;

	for (int num : number) {
		while (current <= num) {
			fout<<'(';
			//cout<<'(';

			s.push(current);
			current++;
		}
		if (!s.empty() && s.top() == num) {
			fout<< ')';
			//cout<< ')';
			s.pop();
		}
	}
} 

void bracket2Num(int brac) {
	stack<int> s;
	int n = 1;
	while (brac<bracket.size()) {
		if (bracket[brac] == '(') {
			s.push(n);
			n++;
		}
		else {
			fout << s.top() << " ";
			//cout << s.top() << " ";

			s.pop();
		}
		brac++;
	}
}

int main() {
	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		int n, k; fin >> n >> k; // 개수, 정보
		if (k == 0) { // 이진 -> 괄호
			number = vector<int>(n + 1);
			for (int j = 1; j <= n; j++) {
				int b; fin >> b;
				number[j] = b;
			}
			fout << n << " ";
			//cout << n << " ";
			num2Bracket(number);
			fout << endl;
			//cout << endl;
		}
		else { // 괄호 -> 이진
			fin >> bracket;
			
			fout << n << " ";
			//cout << n << " ";

			bracket2Num(0);
			
			fout << endl;
			//cout << endl;
		}
	}

	fin.close();
	fout.close();
}
