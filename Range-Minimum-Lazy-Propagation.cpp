// Range Minimum Query Using Lazy Propagation

#include<bits/stdc++.h>
using namespace std;
#define MX 101

int tree[MX] = {0};
int lazy[MX] = {0};

void buildTree(int *a, int start, int end, int index){

	if(start == end){
		tree[index] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	buildTree(a, start, mid, 2 * index);
	buildTree(a, mid + 1, end, 2 * index + 1);
	tree[index] = min(tree[2 * index], tree[2 * index + 1]);
}

void lazyUpdate(int start, int end, int l, int r, int index, int val){

	if(lazy[index] != 0){

		tree[index] += lazy[index];

		if(start != end){
			lazy[2 * index] += lazy[index];
			lazy[2 * index + 1] += lazy[index];
		}
		lazy[index] = 0;
	}

	if(start > end or l > end or r < start)
		return;

	if(start >= l and end <= r){

		tree[index] += val;
		
		if(start != end){
			lazy[2 * index] += val;
			lazy[2 * index + 1] += val;
		}
		return;
	}

	int mid = (start + end) / 2;
	lazyUpdate(start, mid, l, r, 2 * index, val);
	lazyUpdate(mid + 1, end, l, r, 2 * index + 1, val);
	tree[index] = min(tree[2 * index], tree[2 * index + 1]);
}

int query(int start, int end, int l, int r, int index){

	if(start > end or l > end or r < start)
		return INT_MAX;

	if(lazy[index] != 0){

		tree[index] += lazy[index];

		if(start != end){
			lazy[2 * index] += lazy[index];
			lazy[2 * index + 1] += lazy[index];
		}
		lazy[index] = 0;
	}

	if(start >= l and end <= r)
		return tree[index];

	int mid = (start + end) / 2;
	int s1 = query(start, mid, l ,r, 2 * index);
	int s2 = query(mid + 1, end, l, r, 2 * index + 1);

	return min(s1, s2); 
}

int main(){

	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++) cin>>a[i];

	buildTree(a,0,n-1,1);  		// Build Segment Tree

	lazyUpdate(0,n-1,1,3,1,5);	// Increment Range [1,3] by 5
	cout<<query(0,n-1,1,3,1);	// Query to Find Minimum in the Range [1,3]

	return 0;
}