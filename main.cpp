#include <bits/stdc++.h>

using namespace std;

vector<int> Z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    z[0] = n;
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    // input
    string p, t;
    cin >> p >> t;

    /*<=======================================================================================>*/
    // solution
    string s = p + '$' + t;
    int offset = (int) p.length();
    vector<int> z = Z_function(s);
    int cnt = 0;
    vector<int> positions;
    for (int i = 0; i < z.size(); i++) {
        if (z[i] == offset) {
            cnt++;
            positions.push_back(i - offset);
        }
    }

    /*<=======================================================================================>*/

    // output
    cout << cnt << '\n';
    for (int x : positions) {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}

