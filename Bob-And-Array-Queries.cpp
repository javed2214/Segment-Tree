// Bob and Array Queries

#include<bits/stdc++.h>
using namespace std;
#define MX 500005

int a[MX];

void buildTree(int *a, int *tree, int ss, int se, int index){

	if(ss==se){
		tree[index]=a[ss];
		return;
	}
	int mid=(ss+se)/2;
	buildTree(a,tree,ss,mid,2*index);
	buildTree(a,tree,mid+1,se,2*index+1);
	tree[index]=tree[2*index]+tree[2*index+1];
}

void updateTree1(int *a, int *tree, int ss, int se, int idx, int index, int px){

	if(ss==se){
		a[idx]++;
		tree[index]++;
	}
	else{
		int mid=(ss+se)/2;
		if(idx>=ss and idx<=mid) updateTree1(a,tree,ss,mid,idx,2*index,px);
		else updateTree1(a,tree,mid+1,se,idx,2*index+1,px);
		tree[index]=tree[2*index]+tree[2*index+1];
	}
}

void updateTree2(int *a, int *tree, int ss, int se, int idx, int index, int px){

	if(ss==se){
		if(a[idx]==0) return;
		a[idx]--;
		tree[index]--;
	}
	else{
		int mid=(ss+se)/2;
		if(idx>=ss and idx<=mid) updateTree2(a,tree,ss,mid,idx,2*index,px);
		else updateTree2(a,tree,mid+1,se,idx,2*index+1,px);
		tree[index]=tree[2*index]+tree[2*index+1];
	}
}

int query(int *a, int *tree, int ss, int se, int l, int r, int index){

	if(r<ss or l>se) return 0;
	if(l<=ss and se<=r) return tree[index];
	int mid=(ss+se)/2;
	int s1=query(a,tree,ss,mid,l,r,2*index);
	int s2=query(a,tree,mid+1,se,l,r,2*index+1);
	return (s1+s2);
}

int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n,q;
	cin>>n>>q;

	for(int i=0;i<n;i++) a[i]=0;

	int tree[4*MX];
	buildTree(a,tree,1,n,1);

	while(q--){
		int p;
		cin>>p;
		if(p==1){
			int x;
			cin>>x;
			updateTree1(a,tree,1,n,x,1,1);
		}
		else if(p==2){
			int x;
			cin>>x;
			updateTree2(a,tree,1,n,x,1,2);
		}
		else if(p==3){
			int x,y;
			cin>>x>>y;
			cout<<query(a,tree,1,n,x,y,1);
			cout<<"\n";
		}
	}

	return 0;
}