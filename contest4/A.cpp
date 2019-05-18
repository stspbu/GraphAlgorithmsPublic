




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

using namespace std;

int d1, d2;
vector<vector<int>> g;
vector<int> matching;
vector<bool> used;

bool kuhn_alg(int u) {
    if (used[u]) {
        return false;
    }
    
    used[u] = 1;
    for (int v : g[u]) {
        if (matching[v] == -1 || kuhn_alg(matching[v])) {
            matching[v] = u;
            return true;
        }
    }
    
    return false;
}

vector<bool> used2;
vector<vector<int>> g2;
void special_dfs(int u) {
    if (used2[u]) {
        return;
    }
    
    used2[u] = true;
    for (int v : g2[u]) {
        special_dfs(v);
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> d1 >> d2;
    
    g.resize(d1);
    used.resize(d1);
    
    int v, u;
    for (v = 0; v < d1; v++) {
        while(true) {
            cin >> u;
            
            if (u == 0) {
                break;
            }
            
            g[v].push_back(u-1);
        }
    }
    
    matching.resize(d2, -1);
    for (int i = 0; i < d1; i++) {
        used.assign(d1, false);
        kuhn_alg(i);
    }
    
    //
    
    
    stringbuf buff;
    ostream os(nullptr);
    os.rdbuf(&buff);
    
    int matching_count = 0;
    for (int i = 0; i < matching.size(); i++) {
        if (matching[i]!= -1) {
            os << (matching[i]+1) << " " << (i+1) << "\n";
            ++matching_count;
        }
    }
    
    cout << matching_count << "\n";
    cout << buff.str() << endl;
    
    return 0;
}








