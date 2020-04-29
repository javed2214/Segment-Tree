// Range Sum - HackerEarth
// https://www.hackerearth.com/problem/algorithm/range-sum-4/description/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=1e6+10;

void buildTree(int *a, ll *tree, int start, int end, int index){

	if(start == end){
		tree[index] = a[start];
		return;
	}

	int mid = (end + start) / 2;
	buildTree(a, tree, start, mid, 2 * index);
	buildTree(a, tree, mid + 1, end, 2 * index + 1);

	tree[index] = tree[2 * index] + tree[2 * index + 1];
}

ll query(ll *tree, int start, int end, int l, int r, int index){

	if(l <= start and r >= end) return tree[index];
	if(start > end or l > end or r < start) return 0;
	int mid = (end + start) / 2;

	return query(tree, start, mid, l, r, 2 * index) + query(tree, mid + 1, end, l, r, 2 * index + 1);
}

int main(){

    ios_base::sync_with_stdio(false);

	cin.tie(NULL);
	cout.tie(NULL);

	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	int test;
	cin>>test;

	while(test--){

		int n;
		cin>>n;

		int a[N];
		for(int i=1;i<=n;i++) cin>>a[i];

		ll tree[N];

		buildTree(a, tree, 1, n, 1);

		int q;
		cin>>q;

		for(int i=0;i<q;i++){
			int l, r;
			cin>>l>>r;
			ll tx = query(tree, 1, n, l, r, 1);
			cout<<tx<<"\n";
		}
	}

	return 0;
}