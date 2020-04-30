// Elements having Maximum Digit Sum using Segment Tree
// 

#include<bits/stdc++.h>
using namespace std;

unordered_map <int, int> Map;


int digitSum(int n){

	int s = 0, r;

	while(n != 0){
		r = n % 10;
		s = s + r;
		n /= 10;
	}

	return s;
}


void buildTree(int *a, int *tree, int start, int end, int index){

	if(start == end){
		tree[index] = digitSum(a[start]);
		Map[tree[index]] = start;
		return;
	}

	int mid = start + (end - start) / 2;
	buildTree(a, tree, start, mid, 2 * index);
	buildTree(a, tree, mid + 1, end, 2 * index + 1);

	tree[index] = max(tree[2 * index], tree[2 * index + 1]);
}


int getQuery(int *tree, int start, int end, int l, int r, int index){

	if(start > end or l > end or r < start) return INT_MAX;
	if(l <= start and r >= end) return tree[index];

	int mid = start + (end - start) / 2;
	int s1 = getQuery(tree, start, mid, l, r, 2 * index);
	int s2 = getQuery(tree, mid + 1, end, l, r, 2 * index + 1);

	return max(s1, s2);
}


int main(){

	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	int a[] = {16, 12, 43, 55};
	int n = sizeof(a) / sizeof(int);

	int tree[4 * n];

	buildTree(a, tree, 0, n-1, 1);

	cout << a[Map[getQuery(tree, 0, n-1, 0, 2, 1)]];

	return 0;
}