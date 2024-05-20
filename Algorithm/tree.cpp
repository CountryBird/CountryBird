#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>
#include <cmath>
#include <queue>
#include <map>
using namespace std;

int parent[2001]; // 부모
pair<int,int> generation[2001]; // ancestor의 n세대
queue<int> q;
vector<int> ancestor;
vector<int> familyTree[2001]; // 자식
map<string, int> name2num;

ifstream fin("tree.inp");
ofstream fout("tree.out");

void generationOrg(int ancestor) {
	q = queue<int>(); 
	q.push(ancestor);
	generation[ancestor] = { ancestor,0 };

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < familyTree[now].size(); i++) {
			int next = familyTree[now][i];
			q.push(next);
			generation[next] = { ancestor,generation[now].second + 1};
		}
	}
}

void findRelation(int pNum, int qNum,int anc) {

	int pGen = generation[pNum].second;
	int qGen = generation[qNum].second;

	int genGap = pGen - qGen;
	int gG = genGap;

	int removed = abs(pGen - qGen);

	while (genGap) {
		if (genGap > 0) {
			pNum = parent[pNum];
			genGap--;
		}
		else {
			qNum = parent[qNum];
			genGap++;
		}

	} // 세대 맞춰 주기

	if (pNum == qNum) { // 세대 차이를 메웠을 때 같음 => 부모 자녀 관계
		for (int i = 0; i < abs(gG)-1; i++) {
			if (i == abs(gG) - 2) {
				fout << "grand ";
				//cout << "grand ";
			}
			else {
				fout << "great ";
				//cout << "great ";
			}
		}
		if (gG > 0) {
			fout << "child" << endl;
			//cout << "child" << endl;
		}
		else {
			fout << "parent" << endl;
			//cout << "parent" << endl;
		}
	}
	else { // 사촌 또는 형재자매 관계
		int cousin = -1;
		while (pNum != qNum) { // 공통적인 최소한의 조상을 찾기
			pNum = parent[pNum];
			qNum = parent[qNum];
			cousin++;
		}

		if (cousin == 0 && removed == 0) {
			fout << "sibling" << endl;
			//cout << "sibling" << endl;
		}

		else {
			fout << cousin << " cousin ";
			//cout << cousin << " cousin ";

			if (removed != 0) {
				fout << "removed " << removed;
				//cout << "removed " << removed;
			}

			fout << endl;
			//cout << endl;
		}
	}
}

int main() {

	int num = 0;
	memset(parent, -1, sizeof(parent));
	string p, q;

	fin >> p >> q;
	while (p != "no.child" || q!="no.parent") { // 가계도 입력 (p는 q의 자식)
		auto result = name2num.insert({ p,num });
		if (result.second)num++;
		result = name2num.insert({ q,num});
		if (result.second)num++; // 이미 들어가 있는 이름이면 카운트 안 함

		int pNum = name2num[p];
		int qNum = name2num[q];
		parent[pNum] = qNum;
		familyTree[qNum].push_back(pNum);
		fin >> p >> q;
	}

	for (int i = 0; i < name2num.size(); i++) { // 그래프 상의 제일 위의 사람(조상)만 저장
		if (parent[i] == -1)ancestor.push_back(i);
	}

	for (int i = 0; i < ancestor.size(); i++) {
		generationOrg(ancestor[i]);
	}

	while (fin >> p >> q) { // 쿼리 문 입력 (p는 q의 무엇인가?)
		if (name2num.find(p) == name2num.end() || name2num.find(q) == name2num.end()) { // 기존 관계 정의에 없는 이름
			fout << "no relation"<<endl;
			//cout << "no relation"<<endl;
			continue;
		}

		int pNum = name2num[p];
		int qNum = name2num[q];

		if (generation[pNum].first != generation[qNum].first) { // 조상이 다름 => 관계 없음
			fout << "no relation" << endl;
			//cout << "no relation" << endl;
			continue;
		}

		findRelation(pNum, qNum, generation[pNum].first);
	}
	fin.close();
	fout.close();
}
