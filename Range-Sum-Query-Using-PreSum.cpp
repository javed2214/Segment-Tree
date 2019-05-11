// Calculating Sum in a Given Range using Pre-Sum Array

#include<bits/stdc++.h>
using namespace std;

int getSum(int *a, int n, int *presum, int l, int r){

	if(l==0) return presum[r];
	return presum[r] - presum[l-1];
}

int main(){

	int a[]={3,1,2,5,7,8,5,7};
	int n=sizeof(a)/sizeof(int);

	int q;
	int *presum = new int[n];

	for(int i=0;i<n;i++){
		if(i==0) presum[i]=a[i];
		else presum[i]=a[i]+presum[i-1];
	}

	cout<<"No pf Queries: ";
	cin>>q;

	while(q--){
		
		int l,r;
		cin>>l>>r;

		cout<<getSum(a,n,presum,l,r)<<endl;
	}
	return 0;
}
