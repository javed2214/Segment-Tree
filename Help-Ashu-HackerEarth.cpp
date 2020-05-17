// Help Ashu - HackerEarth
// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/help-ashu-1/editorial/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

void buildTree(ll *a, ll *tree, ll start, ll end, ll index){

    if(start == end){
        tree[index] = a[start];
        return;
    }
    ll mid = start + (end - start) / 2;
    buildTree(a, tree, start, mid, 2 * index);
    buildTree(a, tree, mid + 1, end, 2 * index + 1);
    tree[index] = tree[2 * index] + tree[2 * index + 1]; 
}

void update(ll *a, ll *tree, ll start, ll end, ll idx, ll val, ll index){

    if(start == end){
        tree[index] = val;
        a[idx] = val;
        return;
    }
    ll mid = start + (end - start) / 2;
    if(idx >= start and idx <= mid) update(a, tree, start, mid, idx, val, 2 * index);
    else update(a, tree, mid + 1, end, idx, val, 2 * index + 1);
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

ll query(ll *tree, ll start, ll end, ll l, ll r, ll index){

    if(l > end or r < start) return 0;
    if(l <= start and r >= end) return tree[index];
    ll mid = start + (end - start) / 2;
    ll s1 = query(tree, start, mid, l, r, 2 * index);
    ll s2 = query(tree, mid + 1, end, l, r, 2 * index + 1);
    return (s1 + s2);
}

int main(){

    ll n;
    cin >> n;
    ll a[n + 1];
    for(int i = 1; i <= n; i++){
        ll tx;
        cin >> tx;
        if(tx & 1) a[i] = 1;
        else a[i] = 0;
    }
    
    ll tree[4 * n], val;
   
    buildTree(a, tree, 1, n, 1);
    
    ll q;
    cin >> q;
    
    while(q--){
        ll x, y, z;
        cin >> x >> y >> z;
        if(x == 0){
            if(z & 1) val = 1;
            else val = 0;
            update(a, tree, 1, n, y, val, 1);
        }
        else if(x == 1){
            ll len = z - y + 1;
            cout << len - query(tree, 1, n, y, z, 1) << endl;
        }
        else if(x == 2){
            cout << query(tree, 1, n, y, z, 1) << endl;
        }
    }
    return 0;
}