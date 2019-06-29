// Segment Tree Lazy Propagation
// Lazy Propagation is used to Optimize Range Updation

#include<bits/stdc++.h>
using namespace std;
#define MX 101

int tree[MX]={0};
int lazy[MX]={0};

void lazyPropagation(int start, int end, int l, int r, int val, int index){

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
	lazyPropagation(start, mid, l, r, val, 2 * index);
	lazyPropagation(mid+1, end, l, r, val, 2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index+1];
}

int queryRange(int start, int end, int l, int r, int index){

	if(start > end or r < start or l > end)
		return 0;

	if(lazy[index] != 0){

		tree[index] += lazy[index];
		if(start != end){

			lazy[2 * index] += lazy[index];
			lazy[2 * index+1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if(start >= l and end <= r)
		return tree[index];

	int mid = (start + end) / 2;
	int s1 = queryRange(start, mid, l, r, 2*index);
	int s2 = queryRange(mid+1, end, l, r, 2*index+1);

	return (s1 + s2);
}

void buildTree(int *a, int start, int end, int index){

	if(start == end){
		tree[index] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	buildTree(a,start,mid,2 * index);
	buildTree(a,mid+1,end,2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index+1];
}

int main(){

	int a[]={4,5,2,1,8,7,9,4,5};
	int n=sizeof(a)/sizeof(int);

	buildTree(a,0,n-1,1);
	
	lazyPropagation(0,n-1,1,3,8,1);
	cout<<queryRange(0,n-1,1,3,1);

	return 0;
}