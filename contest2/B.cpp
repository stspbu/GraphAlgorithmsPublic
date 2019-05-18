
// B

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#define inf INT_MAX

using namespace std;

vector<int> parent, vrank;
void dsu_make(int v) {
    parent[v] = v;
    vrank[v] = 0;
}

int dsu_find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = dsu_find(parent[v]);
}

void dsu_union(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    
    if (a != b) {
        if (vrank[a] < vrank[b])
            swap(a, b);
        
        parent[b] = a;
        if (vrank[a] == vrank[b])
            vrank[a]++;
    }
}

struct edge {
    int a, b, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    parent.resize(n);
    vrank.resize(n);
    
    edge newE;
    deque<edge> e;
    for (int i = 0; i < m; i++) {
        cin >> newE.a >> newE.b >> newE.w;
        newE.a--;
        newE.b--;
        e.push_back(newE);
    }
    
    sort(e.begin(), e.end(), [](edge e1, edge e2) {
        return e1.w < e2.w;
    });
    
    long long cost = 0;
    for (int i = 0; i < n; i++)
        dsu_make(i);
    
    for (int i = 0; i < m; i++) {
        newE = e.front();
        e.pop_front();
        
        if (dsu_find(newE.a) != dsu_find(newE.b)) {
            cost += newE.w;
            dsu_union(newE.a, newE.b);
        }
    }
    
    cout << cost << endl;
    return 0;
}

/*
 
 4 4
 1 2 1
 2 3 2
 3 4 5
 4 1 4
 
 */

