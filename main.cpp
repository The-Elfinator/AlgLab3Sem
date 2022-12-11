#include <bits/stdc++.h>

using namespace std;

int INFINITIVE = INT_MAX;

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
    queue<int> q;
    vector<int> q1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto &pair: g[v]) {
            int to = pair.first;
            int w = pair.second;
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                q1.push_back(to);
            }
        }
        for (int i = 0; i < q1.size(); i++) {
            int min_q1 = i;
            for (int j = i+1; j < q1.size(); j++) {
                if (position_in_top_sort[q1[j]] < position_in_top_sort[q1[min_q1]]) {
                    min_q1 = j;
                }
            }
            int c = q1[i];
            q1[i] = q1[min_q1];
            q1[min_q1] = c;
        }
        for (int & i : q1) {
            q.push(i);
        }
        q1.clear();
    }
    if (dist[t] == INFINITIVE) {
        cout << "Unreachable" << '\n';
    } else {
        cout << dist[t] << '\n';
    }
    return 0;
}

