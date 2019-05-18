




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

#define INF INT_MAX


using namespace std;

int n;
vector<vector<int>> g;

int BLOCK_LENGTH;
vector<pair<int, int>> block_data;  // <height, vert>
vector<int> first;

vector<bool> used;
vector<int> height;
vector<int> order;

void dfs(int v, int h) {
    used[v] = true;
    height[v] = h;
    order.push_back(v);
    
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u, h + 1);
            order.push_back(v);
        }
    }
}

int get_ans(int L, int R) {
    int min_val = INF, min_val_vert = INF;
    for (int i = L; i <= R; ) {
        if (i % BLOCK_LENGTH == 0 && i + BLOCK_LENGTH - 1 <= R) {
            if (min_val > block_data[i / BLOCK_LENGTH].first) {
                min_val = block_data[i / BLOCK_LENGTH].first;
                min_val_vert = block_data[i / BLOCK_LENGTH].second;
            }
            
            i += BLOCK_LENGTH;
        } else {
            if (min_val > height[order[i]]) {
                min_val = height[order[i]];
                min_val_vert = order[i];
            }
            i++;
        }
    }
    
    return min_val_vert+1;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    g.resize(n);
    used.resize(n);
    height.resize(n);
    
    int v;
    for (int i = 1; i < n; i++) {
        cin >> v;
        g[v-1].push_back(i);
    }
    
    dfs(0, 1);
    
    first.resize(n, -1);
    BLOCK_LENGTH = sqrt(order.size()) + 1;
    block_data.resize(BLOCK_LENGTH, make_pair(INF, INF));
    
    for (int i = 0; i < order.size(); i++) {
        v = order[i];
        if (first[v] == -1) {
            first[v] = i;
        }
        
        if (block_data[i / BLOCK_LENGTH].first > height[v]) {
            block_data[i / BLOCK_LENGTH].first = height[v];
            block_data[i / BLOCK_LENGTH].second = v;
        }
    }
    
    int m, u;
    cin >> m;
    
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        
        int l = first[v-1], r = first[u-1];
        if (l > r) {
            swap(l, r);
        }
        
        cout << get_ans(l, r) << " \n";
    }
    
    return 0;
}








