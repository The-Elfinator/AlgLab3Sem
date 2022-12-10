#include <bits/stdc++.h>

using namespace std;

//const int INFINITIVE = INT_MAX;
const int EDGE_MIN_WEIGHT = -1000;

void dfs(int v, vector<bool> &used, vector<int> &ans, vector<vector<pair<int, int>>> &g) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        int to = g[v][i].first;
        if (!used[to]) {
            dfs(to, used, ans, g);
        }
    }
    ans.push_back(v);
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    vector<vector<pair<int, int>>> g(n);
    vector<bool> used(n, false);
    for (int i = 0; i < m; i++) {
        int v, to, w;
        cin >> v >> to >> w;
        v--;
        to--;
//        w = w - EDGE_MIN_WEIGHT + 1;
        g[v].emplace_back(to, w);
    }
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i, used, ans, g);
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; ++i) {
        cout << ans[i]+1 << ' ';
    }
    cout << '\n';
    return 0;
}

