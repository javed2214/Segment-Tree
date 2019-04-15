// Program to Build Segment Tree from an Array
// Left Child: 2*index
// Right Chid: 2*index+1
// Indexing Starts from 1 (Root Index: 1)

#include<bits/stdc++.h>
using namespace std;

void buildTree(int *a, int *tree, int start, int end, int index){

	if(start==end){
		tree[index]=a[start];
		return;
	}
	int mid=(start+end)/2;
	buildTree(a,tree,start,mid,2*index);
	buildTree(a,tree,mid+1,end,2*index+1);
	tree[index]=tree[2*index]+tree[2*index+1];
}

int main(){

	int a[]={1,2,3,4,5,6,7,8,9};
	int n=sizeof(a)/sizeof(int);

	int *tree=new int[2*n-1];

	buildTree(a,tree,0,n-1,1);

	for(int i=1;i<2*n;i++)
		cout<<tree[i]<<" ";

	return 0;
}
