#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    ll k, p;
    cin >> k >> p;

    ll res = 0;

    for (int i = 1; i <= k; i++){
        string s = to_string(i);
        string reverseS = to_string(i);
        reverse(reverseS.begin(), reverseS.end());
        ll zcyNumber = stoll(s + reverseS);
        res += (ll) zcyNumber;
    }

    res = (ll) res % p;
    cout << res << "\n";
};
