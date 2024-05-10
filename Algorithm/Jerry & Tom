#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int k;
vector<vector<int>> miceSeeHole;
vector<vector<int>> capacity;
vector<bool> hidden;

struct Point {
	long long x, y;
};

long long ccw(Point r, Point p, Point q) {
	return (p.x - r.x) * (q.y - r.y) - (p.y - r.y) * (q.x - r.x);
}

int direction(Point a, Point b, Point c) {
	if (ccw(a, b, c) < 0) return -1;
	if (ccw(a, b, c) > 0) return 1;
	return 0;
}

bool intersect(Point a, Point b, Point c, Point d) {
	return (direction(a, b, c) * direction(a, b, d)<=0)
		&& (direction(c, d, a) * direction(c, d, b)<0);
}

bool findHole(int mouse) {
	if (hidden[mouse]) return false;

	for (int p = 0; p < miceSeeHole[mouse].size(); p++) {
		int hide = miceSeeHole[mouse][p]; // 들어갈 구멍
		hidden[mouse] = true;

		if (capacity[hide].size() < k) { // 자리 있음
			capacity[hide].push_back(mouse);
			return true;
		}
		else { // 만석
			for (int l = 0; l < k; l++) {
				int kickOut = capacity[hide][l]; // 쫒겨날 후보 쥐
				
				if (findHole(kickOut)) {
					capacity[hide][l] = mouse;
					return true; // 쫒겨난 쥐는 새로운 구멍을 찾아 떠납니다...
				}
			}
		}
	}
	return false;
}

int main() {
	ifstream fin("mice.inp");
	ofstream fout("mice.out");

	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		long long n,h, m;
		fin >> n >> k >> h >> m;

		Point* house = new Point[n];

		Point* hole = new Point[h];
		capacity = vector<vector<int>>();

		Point* mice = new Point[m];
		
		for (int j = 0; j < n; j++) { // 집의 모서리
			int x, y; fin >> x >> y;
			house[j] = { x,y };
		}
		for (int j = 0; j < h; j++) { // 쥐구멍
			int x, y; fin >> x >> y;
			hole[j] = { x,y };

			capacity.push_back(vector<int>());
		}
		for (int j = 0; j < m; j++) { // 쥐
			int x, y; fin >> x >> y;
			mice[j] = { x,y };
		}

		miceSeeHole = vector<vector<int>>();
		for (int j = 0; j < m; j++) { // 쥐가
			miceSeeHole.push_back(vector<int>());
			for (int p = 0; p < h; p++) { // 구멍을
				for (int l = 0; l < n; l++) { // 벽에 막히지 않고 볼 수 있는가
					int nextl = (l + 1) % n; // 마지막 점은 첫 점이랑

					if (intersect(mice[j], hole[p], house[l], house[nextl]))break;

					if(l==n-1)miceSeeHole[j].push_back(p); // 구멍이 아무 벽에도 가려지지 않음
				}
			}
		}

		int answer = 0;
		for (int j = 0; j < m; j++) {
			hidden = vector<bool>();
			hidden.resize(m);
			if (findHole(j))answer++;
		}

		if (answer < m) {
			fout << "Impossible" << endl;
			//cout << "Impossible" << endl;
		}
		else {
			fout << "Possible" << endl;
			//cout << "Possible" << endl;
		}
	}

	fin.close();
	fout.close();
}
