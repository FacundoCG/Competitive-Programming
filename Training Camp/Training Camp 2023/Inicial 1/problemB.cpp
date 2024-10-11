#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

ll maxSumJewels (vector<ll> &jewels, vector<ll> &memo, int i){
    if (i <= -1){
        return 0;
    }

    if (memo[i] == UNDEFINED){
        memo[i] = 0;
        ll ignoreIthJewel = maxSumJewels(jewels, memo, i-1);
        ll takeIthJewel = (ll) jewels[i] + maxSumJewels(jewels, memo, i-3);
        memo[i] = max(ignoreIthJewel, takeIthJewel);
    }

    return memo[i];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ll> jewels(n);
    vector<ll> memo(n, UNDEFINED);

    for (int i = 0; i < n; i++) cin >> jewels[i];

    ll res = maxSumJewels(jewels, memo, n-1);
    cout << res << "\n";
}
