#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
using namespace std;

int k;
vector <vector<int>> twoSat;
vector <vector<int>> rTwoSat;
vector <bool> visited;
vector<int> topology;
vector<vector<int>> scc;

#define no(i) ((i)<(k)?(i+k):(i-k))

void first_dfs(int now) {
	visited[now] = true;

	for (int i = 0; i < twoSat[now].size(); i++) {
		int next = twoSat[now][i];
		if (!visited[next])first_dfs(next);
	}
	topology.push_back(now);
}

void second_dfs(int now) {
	visited[now] = true;
	scc[scc.size() - 1].push_back(now);

	for (int i = 0; i < rTwoSat[now].size(); i++) {
		int next = rTwoSat[now][i];
		if (!visited[next])second_dfs(next);
	}
}

int main() {
	ifstream fin("show.inp");
	ofstream fout("show.out");

	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		int k, n; fin >> k >> n; // 전구의 수, 참가자 수
		twoSat = vector<vector<int>>(2*k,vector<int>()); // not은 k+i 값
		rTwoSat = vector<vector<int>>(2*k,vector<int>()); // not은 k+i 값
		visited = vector<bool>(2 * k);

		for (int j = 0; j < n; j++) { // 참가자마다 예측
			int bulb[3]; char color;
			for (int b = 0; b < 3; b++) {
				fin >> bulb[b] >> color;

				if (color == 'B')bulb[b] = no(bulb[b]); // Blue로 예측하면 False
			}

			twoSat[no(bulb[0])].push_back(bulb[1]); // not xa -> xb
			twoSat[no(bulb[1])].push_back(bulb[0]); // not xb -> xa
			rTwoSat[bulb[1]].push_back(no(bulb[0])); // not xa -> xb (r)
			rTwoSat[bulb[0]].push_back(no(bulb[1])); // not xb -> xa (r)

			twoSat[no(bulb[1])].push_back(bulb[2]); // not xb -> xc
			twoSat[no(bulb[2])].push_back(bulb[1]); // not xc -> xb
			rTwoSat[bulb[2]].push_back(no(bulb[1])); // not xb -> xc (r)
			rTwoSat[bulb[1]].push_back(no(bulb[2])); // not xc -> xb (r)

			twoSat[no(bulb[0])].push_back(bulb[2]); // not xa -> xc
			twoSat[no(bulb[2])].push_back(bulb[0]); // not xc -> xa
			rTwoSat[bulb[2]].push_back(no(bulb[0])); // not xa -> xc (r)
			rTwoSat[bulb[0]].push_back(no(bulb[2])); // not xc -> xa (r)
		}

		for (int j = 0; j < 2 * k; j++) {
			if (!visited[j])first_dfs(j);
		}

		visited = vector<bool>(2 * k);
		scc = vector<vector<int>>();
		reverse(topology.begin(), topology.end());
		for (int j = 0; j < 2 * k; j++) {
			int now = topology[j];
			if (!visited[now]) {
				scc.push_back(vector<int>());
				second_dfs(now);
			}
		}

		int ans = 1;
		for (int j = 0; j < scc.size(); j++) {
			for (int b = 0; b < scc[j].size(); b++) {
				if (find(scc[j].begin(), scc[j].end(), no(scc[j][b]) )!= scc[j].end()) {
					ans = -1;
					break;
				}
			}
			if (ans == -1)break;
		}

		fout << ans << endl;
		//cout << ans << endl;
	}

	fin.close();
	fout.close();
}
