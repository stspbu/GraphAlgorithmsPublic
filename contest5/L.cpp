

//
//  Created by Vyacheslav Bushev on 07/03/2019.
//  Copyright © 2019 Vyacheslav Bushev. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <time.h>
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <bitset>
#include <string>
#include <climits>

#define MAX_N 100000

using namespace std;

int n;
set<int> colors[MAX_N+1];
int color[MAX_N+1], ans[MAX_N+1];
vector<vector<int>> g;

void dfs(int v) {
    colors[v].insert(color[v]);
    
    for (int u : g[v]) {
        dfs(u);
        
        if (colors[v].size() < colors[u].size()) {
            swap(colors[v], colors[u]);
        }
        colors[v].insert(colors[u].begin(), colors[u].end());
        colors[u].clear();
    }
    
    ans[v] = (int) colors[v].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    g.resize(n+1);
    
    int v, c;
    for (int i = 1; i <= n; i++) {
        cin >> v >> c;
        g[v].push_back(i);
        color[i] = c;
    }
    
    dfs(0);
    
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}

/*
 
 5
 2 1
 3 2
 0 3
 3 3
 2 1
 
 */







