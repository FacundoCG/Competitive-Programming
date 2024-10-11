#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<ll> arr(n);

        for (int j = 0; j < n; j++) cin >> arr[j];

        ll a = arr[0];
        ll b = arr[1];
        ll c = arr[n-1];

        if (a + b <= c){
            cout << 1 << " " << 2 << " " << n << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
};
