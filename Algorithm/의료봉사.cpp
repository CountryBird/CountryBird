#include<iostream>
#include<fstream>
#include<vector>
#include<memory.h>
using namespace std;

int m;
#define team(i) i+1
#define team2L(team,L) team*50+ L +101
#define L(period,region) period*50 + region + 5201

#define SINK 7800
#define maxValue 7900

struct edge {
	int to,weight, rev;
	edge(int t, int w,int r) {
		to = t; weight = w; rev = r;
	}
};

vector<edge> graph[maxValue];

void add_edge(int from, int to,int weight) {
	graph[from].push_back({ to,weight,(int)graph[to].size() });
	graph[to].push_back({ from,0,(int)graph[from].size()-1 });
}

bool visited[maxValue];
pair<int,int> from[maxValue];
bool dfs(int x, int sink) {
	if (x == sink) return 1;
	if (visited[x])return 0;

	visited[x] = 1;
	int p = 0;
	for (int i = 0; i < graph[x].size(); i++) {
		edge next = graph[x][i];
		if (next.weight > 0 && dfs(next.to, sink)) {
			from[next.to] = { x,p };
			return 1;
		}
		p++;
	}
	return 0;
}

int volunteer(int sink) {
	int ret = 0;
	memset(visited, 0, sizeof(visited));
	while (dfs(0, sink)) {
		memset(visited, 0, sizeof(visited));
		int p = sink;
		while (p) {
			int rev = graph[from[p].first][from[p].second].rev;
			graph[from[p].first][from[p].second].weight--;
			graph[p][rev].weight++;
			p = from[p].first;
		}
		ret++;
	}
	return ret;
}

int main() {
	ifstream fin("service.inp");
	ofstream fout("service.out");

	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		int totalP = 0;
		
		for (int j = 0; j < maxValue; j++) { // 그래프 비우기
			graph[j].clear();
		}

		int n, p; fin >> n >> p >> m; // 팀 개수, 봉사기간 수, 팀 당 최대 참여 횟수
		
		for (int j = 0; j < p; j++) { // 봉사기간 각각에 봉사할 지역의 개수 기록
			int num;  fin >> num;
			
			for (int k = 0; k < num; k++) {
				totalP++;
				add_edge(L(j, k), SINK, 1);
			}
		}

		for (int j = 0; j < n; j++) { // 팀 당
			int listN; fin >> listN; // 리스트

			add_edge(0, team(j), m);

			for (int k = 0; k < listN; k++) {
				int wantP, wantR;
				fin >> wantP >> wantR; // 원하는 기간과 지역
				
				wantP--; wantR--; // 1부터 셈
				
				if(graph[team2L(j,wantP)].empty())add_edge(team(j), team2L(j,wantP),1);
				add_edge(team2L(j, wantP), L(wantP, wantR),1);
			}
		}

		int ans = volunteer(SINK);

		if (totalP <= ans) {
			fout << 1 << endl;
			cout << 1 << endl;
		}
		else {
			fout << 0 << endl;
			cout << 0 << endl;
		}
	}

	fin.close();
	fout.close();
}
