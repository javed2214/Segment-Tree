// FLIPCOIN (CodeChef)
// https://www.codechef.com/problems/FLIPCOIN

#include<bits/stdc++.h>
using namespace std;
#define MX (400*(1<<10))

int tree[MX]={0};
int lazy[MX]={0};

void lazyUpdate(int start, int end, int l, int r, int index){

	if(lazy[index] != 0){

		tree[index] = (end - start + 1) - tree[index];	// new heads = total coins in curr node - no of old heads
	
		if(start != end){

			lazy[2 * index] =! lazy[2 * index];
			lazy[2 * index + 1] =! lazy[2 * index + 1];
		}
		lazy[index] = 0;	
	}

	if(start > end or l > end or r < start)
		return;

	if(start >= l and end <= r){

		tree[index] = (end - start + 1) - tree[index];

		if(start != end){

			lazy[2 * index] =! lazy[2 * index];
			lazy[2 * index + 1] =! lazy[2 * index + 1];
		}
		return;
	}

	int mid = (start + end) / 2;
	lazyUpdate(start, mid, l ,r, 2 * index);
	lazyUpdate(mid + 1, end, l, r, 2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index + 1];
}

int getQuery(int start, int end, int l, int r, int index){

	if(lazy[index] != 0){

		tree[index] = (end - start + 1) - tree[index];
		
		if(start != end){

			lazy[2 * index] =! lazy[2 * index];
			lazy[2 * index + 1] =! lazy[2 * index + 1];
		}
		lazy[index] = 0;
	}

	if(start > end or l > end or r < start)
		return 0;

	if(start >= l and end <= r)
		return tree[index];

	int mid = (start + end) / 2;
	int s1 = getQuery(start, mid, l ,r, 2 * index);
	int s2 = getQuery(mid + 1, end, l, r, 2 * index + 1);

	return (s1 + s2);
}

int main(){

	ios_base::sync_with_stdio(false);

	cin.tie(NULL);
	cout.tie(NULL);

	int n,q;
	cin>>n>>q;

	while(q--){

		int type,l,r;
		cin>>type>>l>>r;

		if(type == 0) lazyUpdate(0,n-1,l,r,1);
		else cout<<getQuery(0,n-1,l,r,1)<<"\n";
	}
	return 0;
}