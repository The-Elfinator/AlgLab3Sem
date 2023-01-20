#include <bits/stdc++.h>
#include <cmath>

using namespace std;

const int INF = INT_MAX;

int main() {
    // input
    int n;
    cin >> n;
    vector<pair<int, int>> g;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g.emplace_back(x, y);
    }

    /*<=======================================================================================>*/
    // solution
    vector<bool> used (n, false);
    vector<double> min_edge_from_vertex (n, INF);
    vector<int> min_edge_end (n, -1);
    min_edge_from_vertex[0] = 0;
    double res = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        // find vertex with min out coming edge
        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || min_edge_from_vertex[v] > min_edge_from_vertex[j])) {
                v = j;
            }
        }

        // try to improve the answer
        used[v] = true;
        if (min_edge_end[v] != -1) {
            double dx = g[v].first - g[min_edge_end[v]].first;
            double dy = g[v].second - g[min_edge_end[v]].second;
            res += sqrt(dx*dx + dy*dy);
        }

        // renew min_edge_from_vertex vector if it's possible
        for (int to = 0; to < n; to++) {
            double edge_v_to_dx = g[v].first - g[to].first;
            double edge_v_to_dy = g[v].second - g[to].second;
            double edge_v_to_weight = sqrt(edge_v_to_dx * edge_v_to_dx + edge_v_to_dy * edge_v_to_dy);
            if (edge_v_to_weight < min_edge_from_vertex[to]) {
                min_edge_from_vertex[to] = edge_v_to_weight;
                min_edge_end[to] = v;
            }
        }
    }
    /*<=======================================================================================>*/

    // output
    cout << res << '\n';
    return 0;
}

