#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int ans = 0;
vector<vector<int>> graph;
vector<vector<int>> rGraph;
vector<bool> visited;
vector<int> topology;

void first_dfs(int node) {
	visited[node] = true;
	for (int i = 0; i < graph[node].size(); i++) {
		int nextNode = graph[node][i];
		if (!visited[nextNode])first_dfs(nextNode);
	}
	topology.push_back(node);
}

void second_dfs(int node) {
	visited[node] = true;
	for (int i = 0; i < rGraph[node].size(); i++) {
		int nextNode = rGraph[node][i];
		if (!visited[nextNode])second_dfs(nextNode);
	}
}

int main() {
	ifstream fin("scc.inp");
	ofstream fout("scc.out");

	int m, n; fin >> m >> n;
	graph.resize(m, vector<int>());
	rGraph.resize(m, vector<int>());
	visited.resize(m);

	for (int k = 0; k < n; k++) {
		int i, j; fin >> i >> j;
		graph[i].push_back(j);
		rGraph[j].push_back(i);
	}

	for (int k = 0; k < m; k++) {
		if(!visited[k])first_dfs(k);
	}
	
	reverse(topology.begin(), topology.end());

	visited = vector<bool>(m);
	for (int k = 0; k < m; k++) {
		int kNode = topology[k];
		if (!visited[kNode]) {
			second_dfs(kNode);
			ans++;
		}
	}

	fout << ans;
	//cout << ans;

	fin.close();
	fout.close();
}
