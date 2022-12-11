#include <bits/stdc++.h>

using namespace std;

int INFINITIVE = INT_MAX;

struct cmp {
    bool operator() (const pair<int, int> a, const pair<int, int> b) const {
        return a.second < b.second;
    }
};

void dfs(int v, vector<bool> &used, vector<int> &top_sort, vector<vector<pair<int, int>>> &g) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        int to = g[v][i].first;
        if (!used[to]) {
            dfs(to, used, top_sort, g);
        }
    }
    top_sort.push_back(v);
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
        g[v].emplace_back(to, w);
    }
    vector<int> top_sort;

    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i, used, top_sort, g);
    }
    reverse(top_sort.begin(), top_sort.end());
    vector<int> position_in_top_sort(n);
    for (int i = 0; i < n; i++) {
        position_in_top_sort[top_sort[i]] = i;
    }
    vector<int> dist(n, INFINITIVE);
    dist[s] = 0;
    set<pair<int, int>, cmp> my_set;
    my_set.insert(make_pair(s, position_in_top_sort[s]));
    while (!my_set.empty()) {
        pair<int, int> pair_v = *my_set.begin();
        my_set.erase(pair_v);
        int v = pair_v.first;
        for (const auto &pair: g[v]) {
            int to = pair.first;
            int w = pair.second;
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                my_set.insert(make_pair(to, position_in_top_sort[to]));
            }
        }
    }
    if (dist[t] == INFINITIVE) {
        cout << "Unreachable" << '\n';
    } else {
        cout << dist[t] << '\n';
    }
    return 0;
}

