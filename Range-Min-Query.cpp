// Range Minimum Query Using Segment Tree
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/

#include<bits/stdc++.h>
using namespace std;
#define MX 100005

void buildTree(int *a, int *tree, int ss, int se, int index){

	if(ss==se){
		tree[index]=a[ss];
		return;
	}
	int mid=(se+ss)/2;
	buildTree(a,tree,ss,mid,2*index);
	buildTree(a,tree,mid+1,se,2*index+1);
	tree[index]=min(tree[2*index], tree[2*index+1]);
}

void updateTree(int *a, int *tree, int ss, int se, int idx, int val, int index){

	if(ss==se){
		a[idx]=val;
		tree[index]=val;
	}
	else{
		int mid=(ss+se)/2;
		if(idx>=ss and idx<=mid) updateTree(a,tree,ss,mid,idx,val,2*index);
		else updateTree(a,tree,mid+1,se,idx,val,2*index+1);
		tree[index]=min(tree[2*index], tree[2*index+1]);
	}
}

int query(int *a, int *tree, int ss, int se, int l, int r, int index){

	if(l>se or r<ss) return INT_MAX;
	if(ss>=l and se<=r) return tree[index];
	int mid=(ss+se)/2;
	int s1=query(a,tree,ss,mid,l,r,2*index);
	int s2=query(a,tree,mid+1,se,l,r,2*index+1);
	return min(s1,s2);
}

int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n,q;
	cin>>n>>q;

	int a[MX],tree[4*MX];
	for(int i=0;i<n;i++) cin>>a[i];

	buildTree(a,tree,0,n-1,1);

	while(q--){

		char ch;
		int x,y;

		cin>>ch>>x>>y;

		if(ch=='q'){
			int c=query(a,tree,0,n-1,x-1,y-1,1);
			cout<<c<<"\n";
		}
		else updateTree(a,tree,0,n-1,x-1,y,1);
	}
	return 0;
}