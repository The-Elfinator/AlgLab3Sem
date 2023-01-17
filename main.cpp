#include <bits/stdc++.h>
#define DEBUG false

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
    g.assign(2*n, vector<int>());
    g_transpose.assign(2*n, vector<int>());
    // i-th name has number 2*i for him and 2*i+1 for not him
    map<string, int> names;
    vector<string> names_in_order;
    for (int i = 0; i < n; i++) {
        char name[10];
        int num = i;
        cin >> name;
        names[name] = num;
        names_in_order.emplace_back(name);
    }
    for (int i = 0; i < m; i++) {
        string name1, impl, name2;
        char sign1, sign2;
        cin >> sign1 >> name1 >> impl >> sign2 >> name2;
        int v1, to1;
        int v2, to2;
        if (sign1 == '-') {
            v1 = names[name1]*2+1;
            v2 = names[name1]*2;
        } else {
            v1 = names[name1]*2;
            v2 = names[name1]*2+1;
        }
        if (sign2 == '-') {
            to1 = names[name2]*2+1;
            to2 = names[name2]*2;
        } else {
            to1 = names[name2]*2;
            to2 = names[name2]*2+1;
        }
        // has edges v1 -> to1 and v2 -> to2
        g[v1].push_back(to1);
        g[to2].push_back(v2);
        g_transpose[to1].push_back(v1);
        g_transpose[v2].push_back(to2);
    }

    // find strongly connected components
    used.assign(2*n, false);
    for (int i = 0; i < 2*n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }

    used.assign(2*n, false);
    component.assign(2*n, 0);
    int k = 0;
    for (int i = 0; i < 2*n; i++) {
        int v = order[2*n-i-1];
        if (!used[v]) {
            dfs2(   v, k);
            k++;
        }
    }
    int count_of_scc = k-1;

#if DEBUG
    for (int i = 0; i < 2*n; i++) {
        cout << i+1 << ':' << component[i] << '\n';
    }
#endif

    bool has_solution = true;
    for (int i = 0; i < n; i++) {
        if (component[2*i] == component[2*i+1]) {
            has_solution = false;
            break;
        }
    }
    if (has_solution) {
        vector<string> ans;
        for (int i = 0; i < n; i++) {
            if (component[2*i] > component[2*i+1]) {
                ans.push_back(names_in_order[i]);
            }
        }
        cout << ans.size() << '\n';
        for (const string& name : ans) {
            cout << name << '\n';
        }
    } else {
        cout << -1 << '\n';
    }
    return 0;
}

