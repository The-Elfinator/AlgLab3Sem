#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
int timer;
vector<int> tin;
vector<int> first_up;
set<int> points;

void dfs(int v, int pred = -1) {
    used[v] = true;
    tin[v] = timer;
    first_up[v] = timer;
    timer++;
    int child = 0;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to == pred) {
            continue;
        }
        if (used[to]) {
            first_up[v] = min(first_up[v], tin[to]);
        } else {
            dfs(to, v);
            first_up[v] = min(first_up[v], first_up[to]);
            if (first_up[to] >= tin[v] && pred != -1) {
                points.insert(v);
            }
            child++;
        }
    }
    if (pred == -1 && child > 1) {
        points.insert(v);
    }

}

int main() {
    // input
    int n, m;
    cin >> n >> m;
    g.assign(n + m, vector<int>());
    used.assign(n+m, false);
    timer = 0;
    tin.assign(n + m, 0);
    first_up.assign(n + m, 0);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        // x, y, z - which skyscrapers connected with magnet pillow
        cin >> x >> y >> z;
        x--;
        y--;
        z--;
        int fictive_vertex = n+i;
        g[x].push_back(fictive_vertex);
        g[y].push_back(fictive_vertex);
        g[z].push_back(fictive_vertex);
        g[fictive_vertex].push_back(x);
        g[fictive_vertex].push_back(y);
        g[fictive_vertex].push_back(z);
    }

    /*<=======================================================================================>*/
    // solution
    // Найти точки сочленения в полученном графе, которые являются фиктивными вершинами
    dfs(0);
    vector<int> points_fictive;
    for (int v : points) {
        if (v >= n) {
            points_fictive.push_back(v - n + 1);
        }
    }
    /*<=======================================================================================>*/

    // output
//    for (int i = 0; i < n; i++) {
//        cout << "Skyscraper " << i+1 << " connected with fictive vertex: ";
//        for (int v : g[i]) {
//            cout << v-n+1 << ' ';
//        }
//        cout << '\n';
//    }
//    for (int i = n; i < n+m; i++) {
//        cout << "Fictive vertex " << i-n+1 << " connected with skyscrapers: ";
//        for (int u : g[i]) {
//            cout << u+1 << ' ';
//        }
//        cout << '\n';
//    }
    cout << points_fictive.size() << '\n';
    for (int v : points_fictive) {
        cout << v << '\n';
    }
    return 0;
}

