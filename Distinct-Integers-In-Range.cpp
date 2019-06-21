// Distinct Integers In Range (HackerEarth)
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/distinct-integers-in-range-66eca44b/description/
// Segment Tree Implementation using Bitset
// Sexy Problem!!!

#include<bits/stdc++.h>
using namespace std;
#define MX 100001

bitset <5005> seg1[400001], seg2[400001];

void buildTree(int *a, int *b, int ss, int se, int index){

	if(ss>se) return;

	if(ss==se){
		seg1[index].set(a[ss]);
		seg2[index].set(b[ss]);
		return;
	}
	int mid=(ss+se)/2;
	buildTree(a,b,ss,mid,2*index);
	buildTree(a,b,mid+1,se,2*index+1);
	seg1[index]=seg1[2*index] | seg1[2*index+1];
	seg2[index]=seg2[2*index] | seg2[2*index+1];
}

bitset <5005> query1(int ss, int se, int l, int r, int index){

	if(l>se or r<ss) return 0;
	if(ss>=l and se<=r) return seg1[index];
	int mid=(ss+se)/2;
	return query1(ss,mid,l,r,2*index) | query1(mid+1,se,l,r,2*index+1);
}

bitset <5005> query2(int ss, int se, int l, int r, int index){

	if(l>se or r<ss) return 0;
	if(ss>=l and se<=r) return seg2[index];
	int mid=(ss+se)/2;
	return query2(ss,mid,l,r,2*index) | query2(mid+1,se,l,r,2*index+1);
}

int main(){

	int n;
	cin>>n;
	int a[MX],b[MX];
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int j=1;j<=n;j++) cin>>b[j];

	buildTree(a,b,1,n,1);

	int q;
	cin>>q;

	while(q--){

		int p,q,r,s;
		cin>>p>>q>>r>>s;

		cout<<(query1(1,n,p,q,1) | query2(1,n,r,s,1)).count()<<"\n";
	}

	return 0;
}
