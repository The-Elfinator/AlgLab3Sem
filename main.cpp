#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

int main() {
    // input
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + m);
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

    /*<=======================================================================================>*/

    // output
    for (int i = 0; i < n; i++) {
        cout << "Skyscraper " << i+1 << " connected with fictive vertex: ";
        for (int v : g[i]) {
            cout << v-n+1 << ' ';
        }
        cout << '\n';
    }
    for (int i = n; i < n+m; i++) {
        cout << "Fictive vertex " << i-n+1 << " connected with skyscrapers: ";
        for (int u : g[i]) {
            cout << u+1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}

