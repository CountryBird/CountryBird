#include<iostream>
#include<fstream>
#include <algorithm>
using namespace std;

#define MAXDIGIT 500
#define PLUS 1
#define MINUS -1

ifstream fin("double.inp");
ofstream fout("double.out");

struct longDouble {
	int integer[MAXDIGIT]; // 정수 부분 (수의 방향 반대)
	int decimal[MAXDIGIT]; // 소수 부분 (원래 수의 방향)
	int signbit;
	int iLastdigit = 0; // 정수 자릿수
	int dLastdigit = 0; // 소수 자릿수
};

void init_longDouble(longDouble* c);
void zero_justify(longDouble* n);
int compare_longDouble(longDouble* a, longDouble* b);
void add_longDouble(longDouble* a, longDouble* b, longDouble* c);
void subtract_longDouble(longDouble* a, longDouble* b, longDouble* c);
void multiply_longDouble(longDouble* a, longDouble* b, longDouble* c);
void divide_longDouble(longDouble* a, longDouble* b, longDouble* c);

longDouble s2Ld(string num) {
	longDouble ld; init_longDouble(&ld);
	int point = num.size();
	int s = num[0] != '-'?0:1;
	if (!s)ld.signbit = PLUS;
	else ld.signbit = MINUS;

	for (int i = num.size()-1; i >=s ; i--) { // 소수점 찾기 및 모든 수 반영
		if (num[i] == '.')point = i;
	}

	for (int i = point - 1; i >= s; i--) { // 정수 
		ld.integer[ld.iLastdigit] = num[i] - '0';
		ld.iLastdigit++;
	}

	for (int i = point + 1; i < num.size(); i++) { // 소수
		ld.decimal[ld.dLastdigit] = num[i] - '0';
		ld.dLastdigit++;
	}

	zero_justify(&ld);

	return ld;
}

longDouble noPoint(longDouble* n) { // 소수점 없애기 (정수 쪽으로 옮김)
	longDouble noN;
	init_longDouble(&noN);
	noN.signbit = n->signbit;

	if (n->dLastdigit == 0 && n->decimal[0] == 0)return *n; // 원래부터 정수면 바로 리턴

	for (int i = n->dLastdigit; i >= 0; i--) {
		noN.integer[noN.iLastdigit] = n->decimal[i];
		noN.iLastdigit++;
	}

	for (int i = 0; i <= (n->iLastdigit); i++) {
		noN.integer[noN.iLastdigit] = n->integer[i];

		if (i != n->iLastdigit)noN.iLastdigit++;
	}

	return noN;
}

longDouble makePoint(longDouble* n, int point) { // 원하는 자리에 소수점 만들기
	longDouble pN;
	init_longDouble(&pN);
	pN.signbit = n->signbit;

	for (int i = point-1; i >= 0; i--) {
		pN.decimal[pN.dLastdigit] = n->integer[i];
		pN.dLastdigit++;
	}

	for (int i = point; i <= n->iLastdigit; i++) {
		pN.integer[pN.iLastdigit] = n->integer[i];
		if (i != n->iLastdigit)pN.iLastdigit++;
		else if (n->integer[i] == 0)pN.iLastdigit--;
	}

	return pN;
}

longDouble movePoint(longDouble* n, int point) { // 소수점 뒤로 옮기기
	if (point == 0)return *n;
	
	longDouble mp;
	init_longDouble(&mp);
	mp.signbit = n->signbit;

	for (int i = point-1; i >= 0; i--) {
		mp.integer[mp.iLastdigit] = n->decimal[i];
		mp.iLastdigit++;
	}

	if(!(n->iLastdigit == 0 && n->integer[0] == 0))
	for (int i = 0; i <= n->iLastdigit; i++) {
		mp.integer[mp.iLastdigit] = n->integer[i];
		if (i != n->iLastdigit)mp.iLastdigit++;
		else if (n->integer[i] == 0)mp.iLastdigit--;
	}

	return mp;
}

void init_longDouble(longDouble* c) {
	for (int i = 0; i < MAXDIGIT; i++)c->integer[i] = 0;
	for (int i = 0; i < MAXDIGIT; i++)c->decimal[i] = 0;
	c->iLastdigit = 0;
	c->dLastdigit = 0;
	c->signbit = PLUS;
}

void zero_justify(longDouble* n) {
	while ((n->iLastdigit > 0) && (n->integer[n->iLastdigit] == 0))
		n->iLastdigit--; // 정수
	while ((n->dLastdigit > 0) && (n->decimal[n->dLastdigit] == 0))
		n->dLastdigit--; // 소수

	if ((n->iLastdigit == 0) && (n->integer[0] == 0) && (n->dLastdigit == 0) )
		n->signbit = PLUS;
}

void digit_shift(longDouble* n, int d) {
	int i;

	if ((n->iLastdigit == 0 && (n->integer[0] == 0)))return;

	for (i = n->iLastdigit; i >= 0; i--)n->integer[i + d] = n->integer[i];
	for (i = 0; i < d; i++)n->integer[i] = 0;

	n->iLastdigit = n->iLastdigit + d;
}

int compare_longDouble(longDouble* a, longDouble* b) { // a가 크면 MINUS, b가 크면 PLUS 나옴
	if ((a->signbit == MINUS) && (b->signbit == PLUS))return(PLUS);
	if ((a->signbit == PLUS) && (b->signbit == MINUS))return(MINUS); // 부호에 따라 대소 구분

	if (b->iLastdigit > a->iLastdigit)return (PLUS * a->signbit);
	if (a->iLastdigit > b->iLastdigit)return (MINUS * a->signbit); // 자리 수에 대해 구분

	for (int i = a->iLastdigit; i >= 0; i--) {
		if (a->integer[i] > b->integer[i])return (MINUS * a->signbit);
		if (b->integer[i] > a->integer[i])return (PLUS* a->signbit); // 실제 수에 대해 구분 (정수)
	}

	int maxD = a->dLastdigit > b->dLastdigit ? a->dLastdigit : b->dLastdigit;
	for (int i = 0; i < maxD; i++) {
		if (a->decimal[i] > b->decimal[i])return (MINUS * a->signbit);
		if (b->decimal[i] > a->decimal[i])return (PLUS * a->signbit); // 실제 수에 대해 구분 (정수)
	}

	return (0);
}

void add_longDouble(longDouble* a, longDouble* b, longDouble* c) {
	int carry, i;

	init_longDouble(c);

	if (a->signbit == b->signbit) c->signbit = a->signbit;
	else {
		if (a->signbit == MINUS) {
			a->signbit = PLUS;
			subtract_longDouble(b, a, c);
			a->signbit = MINUS;
		}
		else {
			b->signbit = PLUS;
			subtract_longDouble(a, b, c);
			b->signbit = MINUS;
		}
		return;
	}

	c->iLastdigit = max(a->iLastdigit, b->iLastdigit) + 1;
	c->dLastdigit = max(a->dLastdigit, b->dLastdigit) + 1;
	carry = 0;

	for (int i = (c->dLastdigit); i >=0 ; i--) {
		c->decimal[i] = (carry + a->decimal[i] + b->decimal[i]) % 10;
		carry = (carry + a->decimal[i] + b->decimal[i]) / 10;
	}

	for (int i = 0; i <= (c->iLastdigit); i++) {
		c->integer[i] = (carry + a->integer[i] + b->integer[i]) % 10;
		carry = (carry + a->integer[i] + b->integer[i]) / 10;
	}

	zero_justify(c);
}

void subtract_longDouble(longDouble* a, longDouble* b, longDouble* c) {
	int borrow;
	int v;
	int i;

	init_longDouble(c);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
		b->signbit = -1 * b->signbit;
		add_longDouble(a, b, c);
		b->signbit = -1 * b->signbit;
		return;
	}
	if (compare_longDouble(a, b) == PLUS) {
		subtract_longDouble(b, a, c);
		c->signbit = MINUS;
		return;
	}

	c->iLastdigit = max(a->iLastdigit, b->iLastdigit);
	c->dLastdigit = max(a->dLastdigit, b->dLastdigit);
	borrow = 0;

	for (i = (c->dLastdigit); i >= 0; i--) {
		v = (a->decimal[i] - borrow - b->decimal[i]);
		if (a->decimal[i] > 0)borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}

		c->decimal[i] = v % 10;
	}

	for (i = 0; i <= (c->iLastdigit); i++) {
		v = (a->integer[i] - borrow - b->integer[i]);
		if (a->integer[i] > 0)borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
		c->integer[i] = v % 10;
	}
	zero_justify(c);
}

void multiply_longDouble(longDouble *a,longDouble *b,longDouble *c) {
	longDouble row;
	longDouble tmp;
	int i, j;

	int decimalPoint = a->dLastdigit + b->dLastdigit; // 곱셈 후 소수점의 위치
	if (!((a->dLastdigit == 0) && (a->decimal[0] == 0)))decimalPoint++;
	if (!((b->dLastdigit == 0) && (b->decimal[0] == 0)))decimalPoint++; // 소수점 이후 수가 없는 것만 아니면 ++

	*a = noPoint(a);
	*b = noPoint(b);

	init_longDouble(c);
	row = *a;
	for (i = 0; i <= b->iLastdigit; i++) {
		for (j = 1; j <= b->integer[i]; j++) {
			add_longDouble(c, &row, &tmp);
			*c = tmp;
		}
		digit_shift(&row, 1);
	}

	if(decimalPoint!=0)*c = makePoint(c,decimalPoint);

	c->signbit = a->signbit * b->signbit;
	zero_justify(c);
}

void divide_longDouble(longDouble* a, longDouble* b, longDouble* c) {
	longDouble row;
	longDouble tmp;

	int asign, bsign;
	int decimalPoint = 0;
	int i, j;
	
	init_longDouble(c);
	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
	b->signbit = PLUS;

	int oriB = b->iLastdigit;
	
	*b = noPoint(b);
	decimalPoint += b->iLastdigit - oriB;
	
	*a = movePoint(a, decimalPoint);

	init_longDouble(&row); init_longDouble(&tmp);
	zero_justify(a); zero_justify(b);

	c->iLastdigit = a->iLastdigit;

	for (i = a->iLastdigit; i >= 0; i--) {
		digit_shift(&row, 1);
		row.integer[0] = a->integer[i];
		c->integer[i] = 0;
		while (compare_longDouble(&row, b) != PLUS) {
			c->integer[i]++;
			subtract_longDouble(&row, b, &tmp);
			row = tmp;
		}
	}

	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}

void print_longDouble(longDouble* n) {
	if (n->signbit == MINUS) {
		fout << '-';
		cout << '-';
	}

	for (int i = n->iLastdigit; i >= 0; i--) {
		fout << n->integer[i];
		cout << n->integer[i];
	}

	if (!(n->dLastdigit == 0 && n->decimal[0] == 0)) {
		fout << '.';
		cout << '.';

		for (int i = 0; i <= n->dLastdigit; i++) {
			fout << n->decimal[i];
			cout << n->decimal[i];
		}
	}
	fout << endl;
	cout << endl;
}

int main() {
	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		char op;string a, b; 
		fin >> a >> op >> b;
		longDouble ldA = s2Ld(a);
		longDouble ldB = s2Ld(b);
		longDouble answer;

		switch (op)
		{
			case '+':
				add_longDouble(&ldA, &ldB, &answer);
				break;
			case '-':
				subtract_longDouble(&ldA, &ldB, &answer);
				break;
			case '*':
				multiply_longDouble(&ldA, &ldB, &answer);
				break;
			case '/':
				divide_longDouble(&ldA, &ldB, &answer);
				break;
		}

		print_longDouble(&answer);
	}

	fin.close();
	fout.close();
}
