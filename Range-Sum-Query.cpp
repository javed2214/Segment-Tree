// Range Sum Query Using Segment Tree

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
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

int query(int *tree, int start, int end, int l, int r, int index){

    if(l > end or r < start or start > end) return 0;         // No Overlap
    if(l <= start and r >= end) return tree[index];           // Complete Overlap
    int mid = start + (end - start) / 2;
    int s1 = query(tree, start, mid, l, r, 2 * index);        // Partial Overlap
    int s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);  // Partial Overlap
    return (s1 + s2);
}

int main(){

    int a[] = {3, 1, 3, 5, 7, 4, 7, 9};
    int n = sizeof(a) / sizeof(int);

    int tree[4 * n];

    buildTree(a, tree, 0, n-1, 1);

    int q;
    cin >> q;

    while(q--){

        int l, r;
        cin >> l >> r;

        cout << query(tree, 0, n-1, l, r, 1) << "\n";
    }
    return 0;
}
