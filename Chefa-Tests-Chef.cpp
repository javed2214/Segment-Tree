// Chefa Tests Chef - CodeChef
// https://www.codechef.com/problems/CFATC

#include<bits/stdc++.h>
using namespace std;

const int MAX = (int)(1e5+1);
#define ll long long

ll tree[4 * MAX][10] = {0};
ll lazy[4 * MAX] = {0};
ll temp[MAX] = {0};

void buildTree(ll *a, ll start, ll end, ll index, ll x){

	if(start == end){
		
		for(int i=0;i<x;i++) tree[index][i] = 0;
		ll p = a[start] % x;
		tree[index][p]++;

		return;
	}

	ll mid = start + (end - start) / 2;
	buildTree(a, start, mid, 2 * index, x);
	buildTree(a, mid + 1, end, 2 * index + 1, x);

	for(int i=0;i<x;i++) tree[index][i] = tree[2 * index][i] + tree[2 * index  + 1][i];
}


void lazyUpdate(ll start, ll end, ll l, ll r, ll value, ll index, ll x){

	if(lazy[index] != 0){

		for(int i=0;i<x;i++) temp[(i + lazy[index]) % x] = tree[index][i];
		for(int i=0;i<x;i++) tree[index][i] = temp[i];

		if(start != end){

			lazy[2 * index] = (lazy[2 * index] + lazy[index]) % x;
			lazy[2 * index + 1] = (lazy[2 * index + 1] + lazy[index]) % x;
		}

		lazy[index] = 0;
	}

	if(start > end or l > end or r < start) return;
	if(l <= start and r >= end){

		for(int i=0;i<x;i++) temp[(i + value) % x] = tree[index][i];
		for(int i=0;i<x;i++) tree[index][i] = temp[i];

		if(start != end){

			lazy[2 * index] = (lazy[2 * index] + value) % x;
			lazy[2 * index + 1] = (lazy[2 * index + 1] + value) % x;
		}
		return;
	}

	int mid = start + (end - start) / 2;
	lazyUpdate(start, mid, l, r, value, 2 * index, x);
	lazyUpdate(mid + 1, end, l, r, value, 2 * index + 1, x);

	for(int i=0;i<x;i++) tree[index][i] = tree[2 * index][i] + tree[2 * index + 1][i];
}


ll getQuery(ll start, ll end, ll l, ll r, ll index, ll x){

	if(lazy[index] != 0){

		for(int i=0;i<x;i++) temp[(i + lazy[index]) % x] = tree[index][i];
		for(int i=0;i<x;i++) tree[index][i] = temp[i];

		if(start != end){

			lazy[2 * index] = (lazy[2 * index] + lazy[index]) % x;
			lazy[2 * index + 1] = (lazy[2 * index + 1] + lazy[index]) % x;
		}

		lazy[index] = 0;
	}

	if(start > end or l > end or r < start) return 0;

	if(l <= start and r >= end) return tree[index][0];

	int mid = start + (end - start) / 2;
	int s1 = getQuery(start, mid, l, r, 2 * index, x);
	int s2 = getQuery(mid + 1, end, l, r, 2 * index + 1, x);

	return (s1 + s2);
}


int main(){

	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	ll n, q, x;
	cin >> n >> q >> x;

	ll a[n];

	for(ll i=0;i<n;i++) cin >> a[i];
	buildTree(a, 0, n-1, 1, x);

	for(ll i=0;i<q;i++){

		ll type, l, r, tx;
		cin >> type;
		
		if(type == 1){

			cin >> l >> r >> tx;
			--l; --r;
			lazyUpdate(0, n-1, l, r, tx, 1, x);
		}
		else{

			cin >> l >> r;
			--l; --r;
			cout << getQuery(0, n-1, l, r, 1, x) << endl;
		}
	}

	return 0;
}
