#include<iostream>
#include<fstream>
#include <vector>
using namespace std;

int idx,ans;
vector<int> nodeV;
vector<int> preorder;

struct node {
	node* left = NULL;
	node* right = NULL;
	int num = -1;
};

node* aboutTree(int left,int right) {
	node* n = new node();
	int leftValue = 0; int rightValue = 0;

	if (left > right)return NULL;
	n->num = preorder[idx]; idx++;

	n->left = aboutTree(left, n->num - 1);
	n->right = aboutTree(n->num+1, right);

	int nodeNum = nodeV[n->num];
	if (n->left == NULL && n->right == NULL) {
		if (ans < nodeNum)ans = nodeNum;
		n->num = nodeNum;
		return n;
	}

	if (n->left != NULL) leftValue = n->left->num;
	if (n->right != NULL) rightValue =n->right->num;

	int oneChild;
	if (n->left == NULL) oneChild = nodeNum + rightValue;
	else if (n->right == NULL) oneChild = nodeNum + leftValue;
	else oneChild = nodeNum + leftValue > nodeNum + rightValue ? nodeNum + leftValue : nodeNum + rightValue;

	int twoChild = nodeNum + leftValue + rightValue;

	if (n->left != NULL && n->right != NULL)
		if (ans < twoChild)ans = twoChild;

	n->num = oneChild;
	return n;
}

int main() {
	ifstream fin("path.inp");
	ofstream fout("path.out");

	int t; fin >> t;
	for (int i = 0; i < t; i++) {
		int nodeNum; fin >> nodeNum;
		nodeV = vector<int>(nodeNum);
		preorder = vector<int>(nodeNum);
		for (int j = 0; j < nodeNum; j++)fin >> nodeV[j];
		for (int j = 0; j < nodeNum; j++)fin >> preorder[j];

		idx = 0; ans = 0;
		aboutTree(0, nodeNum - 1);

		cout << ans << endl;
		fout << ans << endl;
	}

	fin.close();
	fout.close();
}
