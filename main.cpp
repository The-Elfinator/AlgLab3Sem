#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

int main() {
    // input
    int n, m, k;
    cin >> n >> k;
    vector<int> exits;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x--;
        exits.push_back(x);
    }
    cin >> m;
    vector<vector<int>> g(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    /*<=======================================================================================>*/
    // solution
    queue<int> my_queue;
    vector<int> dist(n, INF);
    vector<int> nearest_exit(n, -1);
    for (int e : exits) {
        my_queue.push(e);
        dist[e] = 0;
        nearest_exit[e] = e;
    }
    while (!my_queue.empty()) {
        int v = my_queue.front();
        my_queue.pop();
        for (int to : g[v]) {
            if (dist[to] > dist[v] + 1) {
                dist[to] = dist[v] + 1;
                nearest_exit[to] = nearest_exit[v];
                my_queue.push(to);
            } else if (dist[to] == dist[v] + 1) {
                nearest_exit[to] = min(nearest_exit[to], nearest_exit[v]);
                my_queue.push(to);
            }
        }
    }
    /*<=======================================================================================>*/

    // output
    for (int x : dist) {
        cout << x << ' ';
    }
    cout << '\n';
    for (int v : nearest_exit) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
    return 0;
}

