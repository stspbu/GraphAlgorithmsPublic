//
//  main.cpp
//  tsweb
//
//  Created by Vyacheslav Bushev on 14/02/2019.
//  Copyright © 2019 Vyacheslav Bushev. All rights reserved.
//
//  TopSort: u < v, if u -> v
//

#define yow continue

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum colors {
    WHITE,
    GRAY,
    BLACK
};

vector<vector<int>> g;
vector<colors> color;

bool acyclic = true;
pair<int, int> lastPath; // (start, end)

vector<int> pathLogger;

bool dfs(int u) {
    color[u] = GRAY;
    
    for (auto v : g[u]) {
        int to = v;
        if(color[v] == WHITE) {
            pathLogger[to] = u;
            
            if (dfs(v)) {
                return true;
            }
        } else if (color[v] == GRAY) {
            pathLogger[to] = u;
            lastPath = pair<int, int>(to, u);
            
            return true;
        }
    }
    
    color[u] = BLACK;
    return false;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    pathLogger.resize(n);
    color.resize(n, WHITE);
    g.resize(n, vector<int>());
    
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    
    lastPath = pair<int, int>(-1, -1);
    for (int i = 0; i < n && !dfs(i); i++)
        yow;
    
    if (lastPath.first == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        
        vector<int> cycle;
        for (int v = lastPath.second; v != lastPath.first; v = pathLogger[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(lastPath.first);
        reverse(cycle.begin(), cycle.end());
        
        for (auto x : cycle) {
            cout << (x+1) << " ";
        }
    }
    
    return 0;
}

