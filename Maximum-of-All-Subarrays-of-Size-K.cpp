// Maximum of All Subarrays of Size K using Segment Tree
// Asked in AMAZON

#include<bits/stdc++.h>
using namespace std;

void buildTree(int *a, int *tree, int start, int end, int index){

    if(start == end){
        tree[index] = a[start];
        return;
    }
    int mid = start + (end - start) / 2;
    buildTree(a, tree, start, mid, 2 * index);
    buildTree(a, tree, mid + 1, end, 2 * index + 1);
    tree[index] = max(tree[2 * index], tree[2 * index + 1]);
}

int query(int *tree, int start, int end, int l, int r, int index){

    if(l > end or r < start) return 0;
    if(l <= start and r >= end) return tree[index];
    int mid = start + (end - start) / 2;
    int s1 = query(tree, start, mid, l, r, 2 * index);
    int s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);
    return max(s1, s2);
}

int main(){

    int a[] = {1, 2, 3, 1, 4, 5, 2, 3, 6};
    int n = sizeof(a) / sizeof(int);

    int tree[4*n];

    buildTree(a, tree, 0, n-1, 1);
    
    int k;
    cin >> k;

    for(int i = 0; i < n; i++){
        int l = i;
        int r = i + k - 1;
        if(r < n) cout << query(tree, 0, n-1, l, r, 1) << " ";
    }
    return 0;
}