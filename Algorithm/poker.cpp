#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

string ranking[9] = { "Top","One Pair","Two Pair","Triple","Straight","Flush","Full House","Four Card","Straight Flush" };
int numCheck[14];
int shapeCheck[4];
bool cardCheck[4][14];

void draw(string card) {
	int shape, num;
	if (card[0] == 'S')shape = 0;
	else if (card[0] == 'D')shape = 1;
	else if (card[0] == 'H')shape = 2;
	else shape = 3;

	if (card[1] == 'T')num = 9;
	else if (card[1] == 'J')num = 10;
	else if (card[1] == 'Q')num = 11;
	else if (card[1] == 'K')num = 12;
	else if (card[1] == 'A' || card[1] == '1') {
		numCheck[0]++;
		cardCheck[shape][0] = true;
		num = 13;
	}
	else num = card[1] - '1';

	numCheck[num]++;
	shapeCheck[shape]++;
	cardCheck[shape][num] = true;
}

string check() {
	int nowRank = 0;
	int pairCnt = 0;
	int triCnt = 0;

	int sCnt = 0;
	
	for (int i = 0; i < 4; i++) {
		int ssCnt = 0;
		for (int j = 0; j < 14; j++) {
			if (cardCheck[i][j] > 0)ssCnt++;
			else ssCnt = 0;

			if (ssCnt == 5) return ranking[8];
		}
	}

	for (int i = 0; i < 14; i++) { // 숫자 관련
		if (numCheck[i] > 0) {
			sCnt++;

			if (numCheck[i] == 2 && i != 13) pairCnt++; // 원 페어 추가
			else if (numCheck[i] == 3 && i != 13)triCnt++; // 트리플 추가
			else if (numCheck[i] == 4)nowRank = 7; // 포 카드
		}
		else sCnt = 0;

		if (sCnt == 5 && nowRank < 4) {
			nowRank = 4; // 스트레이트
		}
	}

	if (nowRank < 4) { // 스트레이트 이하 족보
		if (triCnt)nowRank = 3;
		else if (pairCnt > 1)nowRank = 2;
		else if (pairCnt > 0)nowRank = 1;
	}

	if (nowRank < 6)
		if (triCnt > 1 || (triCnt > 0 && pairCnt > 0))nowRank = 6; // 풀하우스

	for (int i = 0; i < 4; i++) {
		if (shapeCheck[i] > 4) { // 플러쉬
			if (nowRank < 5)nowRank = 5;
		}
	}

	return ranking[nowRank];
}

int main() {
	ifstream fin("poker.inp");
	ofstream fout("poker.out");

	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		memset(numCheck, 0, sizeof(numCheck));
		memset(shapeCheck, 0, sizeof(shapeCheck));
		memset(cardCheck, false, sizeof(cardCheck));

		for (int j = 0; j < 7; j++) {
			string card; fin >> card;
			draw(card);
		}

		fout << check() << endl;
		//cout << check() << endl;
	}

	fin.close();
	fout.close();
}
