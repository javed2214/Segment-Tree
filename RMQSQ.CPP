// RMQSQ - SPOJ
// 

#include<bits/stdc++.h>
using namespace std;

#define MAX 1001
#define ll long long

void buildTree(int *a, int *tree, int start, int end, int index){

	if(start == end){
		tree[index] = a[start];
		return;
	}

	int mid = start + (end - start) / 2;
	buildTree(a, tree, start, mid, 2 * index);
	buildTree(a, tree, mid + 1, end, 2 * index + 1);

	tree[index] = min(tree[2 * index], tree[2 * index + 1]);
}

int query(int *tree, int start, int end, int l, int r, int index){

	if(start > end or l > end or r < start) return INT_MAX;
	if(l <= start and r >= end) return tree[index];
	int mid = start + (end - start) / 2;
	int s1 = query(tree, start, mid, l, r, 2 * index);
	int s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);

	return min(s1, s2);
}

int main(){

	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	int n;
	cin >> n;

	int a[n];
	for(int i=0;i<n;i++) cin >> a[i];

	int tree[4 * n];

	buildTree(a, tree, 0, n - 1, 1);

	int q;
	cin >> q;

	while(q--){

		int l, r;
		cin >> l >> r;

		cout << query(tree, 0, n - 1, l, r, 1) << "\n";
	}

	return 0;
}