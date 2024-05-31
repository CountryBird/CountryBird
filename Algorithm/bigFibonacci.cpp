#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<long long>> matrix = { { 0,1 }, {1,1} };

vector<vector<long long>> matrix_prod(vector<vector<long long>> a, vector<vector<long long>> b) {
	vector<vector<long long>> ans = vector<vector<long long>>(2, vector<long long>(2));
	ans[0][0] = ((a[0][0] * b[0][0]) % 1000000007 + (a[0][1] * b[1][0]) % 1000000007) % 1000000007;
	ans[0][1] = ((a[0][0] * b[0][1]) % 1000000007 + (a[0][1] * b[1][1]) % 1000000007) % 1000000007;
	ans[1][0] = ((a[1][0] * b[0][0]) % 1000000007 + (a[1][1] * b[1][0]) % 1000000007) % 1000000007;
	ans[1][1] = ((a[1][0] * b[0][1]) % 1000000007 + (a[1][1] * b[1][1]) % 1000000007) % 1000000007;

	return ans;
}

long long big_fibo(long long n) {
	vector<vector<long long>> fValue = matrix;
	vector<vector<long long>> answer = { { 1,0 }, {0,1} };

	while (n>0) {
		if (n % 2 == 1)answer = matrix_prod(answer, fValue);

		n/=2;
		fValue = matrix_prod(fValue, fValue);
	}
	return answer[0][1];
}

int main() {
	ifstream fin("bigFibonacci.inp");
	ofstream fout("bigFibonacci.out");

	long long t; fin >> t;

	for (long long i = 0; i < t; i++) {
		long long n; fin >> n;
		fout << n << " "<<big_fibo(n)<<endl;
		//cout << n << " "<<big_fibo(n)<<endl;
	}

	fin.close();
	fout.close();
}
