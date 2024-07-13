#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> leftPocket(n);
        vector<int> rightPocket(m);
        int res = 0;

        for (int &v : leftPocket) cin >> v;
        for (int &w : rightPocket) cin >> w;

        for (int j = 0; j < n; j++){
            for (int h = 0; h < m; h++){
                if (leftPocket[j] + rightPocket[h] <= k){
                    res++;
                }
            }
        }

        cout << res << "\n";
    }
}