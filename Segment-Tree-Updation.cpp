// Updation at Particular Index
									
#include<bits/stdc++.h>
using namespace std;

void buildTree(int *a, int *tree, int start, int end, int index){

	if(start == end){
		tree[index] = a[start];
		return;
	}
	int mid = (start + (end - start)/2);
	buildTree(a,tree,start,mid,2*index);
	buildTree(a,tree,mid+1,end,2*index+1);
	tree[index] = tree[2*index] + tree[2*index + 1];
}

int getSumUtil(int *tree, int ss, int se, int qs, int qe, int index){

	if(ss >= qs and se <= qe) return tree[index];
	if(qe < ss or qs > se) return 0;
	int mid = (ss + (se - ss) / 2);
	return getSumUtil(tree,ss,mid,qs,qe,2*index) + getSumUtil(tree,mid+1,se,qs,qe,2*index+1);
}

int getSum(int *tree, int n, int qs, int qe){

	if(qs < 0 or qe > n-1 or qs > qe){
		cout<<"Invalid Query!";
		return -1;
	}
	return getSumUtil(tree,0,n-1,qs,qe,1);
}

void updateValueUtil(int *tree, int ss, int se, int i, int diff, int index){

	if(i < ss or i > se) return;
	tree[index] = tree[index] + diff;
	if(ss != se){
		int mid = (ss + (se - ss) / 2);
		updateValueUtil(tree,ss,mid,i,diff,2*index);
		updateValueUtil(tree,mid+1,se,i,diff,2*index + 1);
	}
}

void updateValue(int *a, int *tree, int n, int i, int new_value){

	if(i < 0 or i > n-1){
		cout<<"Invalid Index!";
		return;
	}

	int diff = new_value - a[i];
	a[i] = new_value;

	updateValueUtil(tree,0,n-1,i,diff,1);
}

int main(){

	int a[]={1,3,5,7,9,11};
	int n=sizeof(a)/sizeof(a[0]);

	int *tree = new int[2*n];
	for(int i=0;i<2*n;i++) tree[i]=-1;

	buildTree(a,tree,0,n-1,1);
	// for(int i=1;i<2*n;i++) cout<<tree[i]<<" ";

	cout<<getSum(tree,n,2,3);

	int index=3,new_value=10;
	updateValue(a,tree,n,index,new_value);

	cout<<endl;

	cout<<getSum(tree,n,2,3);

	return 0;
}
