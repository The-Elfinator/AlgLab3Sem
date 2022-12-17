#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, g_transpose;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs1(to);
        }
    }
    order.push_back(v);
}

void dfs2(int v, int k) {
    used[v] = true;
    component[v] = k;
    for (int to : g_transpose[v]) {
        if (!used[to]) {
            dfs2(to, k);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.assign(n, vector<int>());
    g_transpose.assign(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int v, to;
        cin >> v >> to;
        v--;
        to--;
        g[v].push_back(to);
        g_transpose[to].push_back(v);
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    used.assign(n, false);
    component.assign(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
        int v = order[n-i-1];
        if (!used[v]) {
            dfs2(v, k);
            k++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << i+1 << ':' << component[i] << '\n';
    }
    return 0;
}

