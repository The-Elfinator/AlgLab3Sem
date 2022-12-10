#include <bits/stdc++.h>

using namespace std;

const int INFINITIVE = INT_MAX;
const int EDGE_MIN_WEIGHT = -1000;

int one_k_bfs(int n, int s, int t, int k, const vector<vector<pair<int, int>>> &g) {
    vector<queue<int>> myQueue (k + 1);
    myQueue[0].push(s);
    vector<pair<int, int>> dist (n, make_pair(INFINITIVE, 0));
    dist[s].first = 0;
    vector<bool> used (n, false);
    int index_nonEmpty_queue = 0;
    int size_of_queue = 1;
    while (size_of_queue > 0) {
        while (myQueue[index_nonEmpty_queue % (k + 1)].empty()) {
            index_nonEmpty_queue++;
        }
        int u = myQueue[index_nonEmpty_queue % (k + 1)].front();
        myQueue[index_nonEmpty_queue % (k + 1)].pop();
        size_of_queue--;
        if (!used[u]) {
            used[u] = true;
            for (auto edge : g[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u].first + dist[u].second * (EDGE_MIN_WEIGHT - 1) + w + (EDGE_MIN_WEIGHT - 1) < dist[v].first + dist[v].second * (EDGE_MIN_WEIGHT - 1)) {
                    dist[v].first = dist[u].first + w;
                    dist[v].second = dist[u].second + 1;
                    myQueue[dist[v].first % (k + 1)].push(v);
                    size_of_queue++;
                }
            }
        }
    }
    int res = dist[t].first + dist[t].second * (EDGE_MIN_WEIGHT - 1);
    return res;
}

int main() {
    int n, m, s, t;
    int k = -2*EDGE_MIN_WEIGHT+1;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int v, to, w;
        cin >> v >> to >> w;
        v--;
        to--;
        w = w - EDGE_MIN_WEIGHT + 1;
        g[v].emplace_back(to, w);
    }
    int res = one_k_bfs(n, s, t, k, g);

    //TODO: stress-test with Ford-Bellman algorithm

    if (res == INFINITIVE) {
        cout << "Unreachable" << '\n';
    } else {
        cout << res << '\n';
    }

    return 0;
}

