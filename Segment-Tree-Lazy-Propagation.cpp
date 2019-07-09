// Segment Tree Lazy Propagation
// Lazy Propagation is used to Optimize Range Updation

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MX 101

ll tree[MX]={0};
ll lazy[MX]={0};

void lazyUpdate(ll start, ll end, ll l, ll r, ll val, ll index){

	if(lazy[index] != 0){

		tree[index] += lazy[index] * (end - start + 1);
		
		if(start != end){
			lazy[2 * index] += lazy[index];
			lazy[2 * index + 1] += lazy[index];
		}
		
		lazy[index] = 0;
	}
	
	if(start > end or l > end or r < start)
		return;

	if(start >= l and end <= r){

		tree[index] += val * (end - start + 1);

		if(start != end){
			lazy[2 * index] += val;
			lazy[2 * index + 1] += val;
		}
		return;
	}
	ll mid = (start + end) / 2;
	lazyUpdate(start, mid, l, r, val, 2 * index);
	lazyUpdate(mid+1, end, l, r, val, 2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index + 1];
}

ll query(ll start, ll end, ll l, ll r, ll index){

	if(start > end or r < start or l > end)
		return 0;

	if(lazy[index] != 0){

		tree[index] += lazy[index] * (end - start + 1);

		if(start != end){

			lazy[2 * index] += lazy[index];
			lazy[2 * index + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if(start >= l and end <= r)
		return tree[index];

	ll mid = (start + end) / 2;
	ll s1 = query(start, mid, l, r, 2 * index);
	ll s2 = query(mid + 1, end, l, r, 2 * index + 1);

	return (s1 + s2);
}

void buildTree(ll *a, ll start, ll end, ll index){

	if(start == end){
		tree[index] = a[start];
		return;
	}
	ll mid = (start + end) / 2;
	buildTree(a,start,mid,2 * index);
	buildTree(a,mid+1,end,2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index+1];
}

int main(){

	ll a[]={4,5,2,1,8,7,9,4,5};
	ll n=sizeof(a)/sizeof(ll);

	buildTree(a,0,n-1,1);
	
	lazyUpdate(0,n-1,1,3,8,1);
	cout<<query(0,n-1,1,3,1);

	return 0;
}
