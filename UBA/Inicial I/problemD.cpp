#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> minimuns(n);

    for (int i = 0; i < n; i++){
        int minStreet = INT_MAX;

        for (int j = 0; j < m; j++){
            long long k;
            cin >> k;

            if (k < minStreet){
                minStreet = k;
            }
        }

        minimuns[i] = minStreet;
    }

    int res = minimuns[0];

    for (int i = 1; i < n; i++){
        if (res < minimuns[i]){
            res = minimuns[i];
        }
    }

    cout << res << "\n";
}
