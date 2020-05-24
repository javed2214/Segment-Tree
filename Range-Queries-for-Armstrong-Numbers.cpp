// Range Queries for Armstrong Numbers With Point Updates
// https://www.geeksforgeeks.org/range-queries-for-number-of-armstrong-numbers-in-an-array-with-updates/

#include<bits/stdc++.h>
using namespace std;

bool isArmstrong(int n){

    int r, s = 0, x = n;
    int cnt = 0;

    while(n){
        cnt += 1;
        n /= 10;
    }

    n = x;

    while(n){
        
        r = n % 10;
        s +=  pow(r, cnt);
        n /= 10;
    }

    return s == x;
}

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
        a[start] = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if(idx >= start and idx <= mid) update(a, tree, start, mid, idx, val, 2 * index);
    else update(a, tree, mid + 1, end, idx, val, 2 * index + 1);
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

int main(){

    int a[] = {18, 153, 8, 9, 14, 5};
    int n = sizeof(a) / sizeof(int);

    for(int i = 0; i < n; i++){
        if(isArmstrong(a[i])) a[i] = 1;
        else a[i] = 0;
    }

    int tree[4*n];

    buildTree(a, tree, 0, n-1, 1);

    int q;
    cin >> q;

    while(q--){

        int x, y, z;
        cin >> x >> y >> z;

        if(x == 0) cout << query(tree, 0, n-1, y, z, 1) << "\n";
        else{
            if(isArmstrong(z)) update(a, tree, 0, n-1, y, 1, 1);
            else update(a, tree, 0, n-1, y, 0, 1);
        }
    }

    return 0;
}