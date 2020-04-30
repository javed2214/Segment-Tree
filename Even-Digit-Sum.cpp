// Even Digit Sum in a Range using Segment Tree
// https://www.geeksforgeeks.org/queries-for-the-count-of-even-digit-sum-elements-in-the-given-range-using-segment-tree/

#include<bits/stdc++.h>
using namespace std;


int digitSum(int n){

	int sum = 0, r;

	while(n != 0){
		r = n % 10;
		sum = sum + r;
		n /= 10;
	}
	return sum;
}


void buildTree(int *a, int *tree, int start, int end, int index){

	if(start == end){
		if(digitSum(a[start]) & 1) tree[index] = 0;
		else tree[index] = 1;
		return;
	}

	int mid = start + (end - start) / 2;
	buildTree(a, tree, start, mid, 2 * index);
	buildTree(a, tree, mid + 1, end, 2 * index + 1);

	tree[index] = tree[2 * index] + tree[2 * index + 1];
}


int query(int *tree, int start, int end, int l, int r, int index){

	if(start > end or l > end or r < start) return 0;
	if(l <= start and r >= end) return tree[index];

	int mid = start + (end - start) / 2;
	int s1 = query(tree, start, mid, l, r, 2 * index);
	int s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);

	return (s1 + s2);
}


int main(){

	int a[] = {7, 3, 19, 13, 5, 4};
	int n = sizeof(a) / sizeof(int);

	int tree[4 * n];

	buildTree(a, tree, 0, n-1, 1);

	int l = 1, r = 5;
	
	cout << query(tree, 0, n-1, l, r ,1);

	return 0;
}