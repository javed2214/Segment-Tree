// Range Sum Query Using Segment Tree

#include<bits/stdc++.h>
using namespace std;

void buildTree(int *a, int *tree, int start, int end, int index){

	if(start == end){
		tree[index]=a[start];
		return;
	}
	int mid=start+(end-start)/2;
	buildTree(a,tree,start,mid,2*index);
	buildTree(a,tree,mid+1,end,2*index+1);
	tree[index]=tree[2*index]+tree[2*index+1];
}

int getMid(int start, int end){
	return start + (end - start)/2;
}

int getSumUtil(int *tree, int ss, int se, int qs, int qe, int index){

	if(qs <= ss and qe >= se) return tree[index];
	if(qs > se or qe < ss) return 0;
	int mid = getMid(ss,se);
	return getSumUtil(tree,ss,mid,qs,qe,2*index) + getSumUtil(tree,mid+1,se,qs,qe,2*index+1);
}

int getSum(int *tree, int n, int qs, int qe){

	if(qs < 0 or qe > n-1 or qs > qe){
		cout<<"Invalid Input!";
		return -1;
	}
	return getSumUtil(tree,0,n-1,qs,qe,1);
}

int main(){

	int a[]={1,3,5,7,9,11};
	int n=sizeof(a)/sizeof(int);

	int *tree=new int[2*n];
	for(int i=0;i<2*n;i++) tree[i]=-1;

	buildTree(a,tree,0,n-1,1);
	cout<<"Segment Tree: ";
	for(int i=1;i<2*n;i++) cout<<tree[i]<<" ";	// Printing Segment Tree
	cout<<endl;
	cout<<"Sum Range (2,5): "<<getSum(tree,n,2,5)<<endl;		// Range(2,5) => 5, 7, 9, 11

	return 0;
}