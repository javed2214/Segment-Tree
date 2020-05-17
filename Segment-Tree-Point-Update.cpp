// Segment Tree Point Update
// 

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

    if(l > end or r < start) return 0;
    if(l <= start and r >= end) return tree[index];
    int mid = start + (end - start) / 2;
    int s1 = query(tree, start, mid, l, r, 2 * index);
    int s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);
    return (s1 + s2);
}

void update(int *a, int *tree, int start, int end, int idx, int val, int index){

    if(start == end){
        tree[index] = val;
        a[idx] = val;
        return;
    }
    else{
        int mid = start + (end - start) / 2;
        if(idx >= start and idx <= mid) update(a, tree, start, mid, idx, val, 2 * index);
        else update(a, tree, mid + 1, end, idx, val, 2 * index + 1);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
}

int main(){

    int a[] = {4,1,3,6,8,5,1,7};
    int n = sizeof(a) / sizeof(int);

    int tree[4 * n];

    buildTree(a, tree, 0, n - 1, 1);

    int q;
    cin >> q;

    while(q--){
        
        int x;
        cin >> x;
        if(x == 0){
            int idx, val;
            cin >> idx >> val;
            update(a, tree, 0, n - 1, idx - 1, val, 1);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << query(tree, 0, n - 1, l - 1, r - 1, 1) << endl;
        }
    }
    return 0;
}