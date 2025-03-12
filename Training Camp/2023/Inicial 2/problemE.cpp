#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;
const ll INF = LLONG_MAX;
const ll INF_NEG = LLONG_MIN;

ll productOfDigit(ll n, vector<ll> &memo){
    if (n < 10){
        return n;
    }

    if (memo[n] == UNDEFINED){
        memo[n] = 1;
        ll lastDigit = n%10;

        if (lastDigit != 0){
            memo[n] = (ll) memo[n] * lastDigit;
        }

        memo[n] = (ll) memo[n] * productOfDigit(n/10, memo);
    }

    return memo[n];
}

ll g (ll n, vector<ll> &memo, vector<ll> &productOfDigits){
    if (memo[n] == UNDEFINED){
        if (n < 10){
            memo[n] = n;
        } else {
            ll product = productOfDigit(n, productOfDigits);
            memo[n] = g(product, memo, productOfDigits);
        }
    }

    return memo[n];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    vector<tuple<ll, ll, ll>> queries(q);
    ll maxR = INF_NEG;

    for (int i = 0; i < q; i++) {
        ll l, r, k;
        cin >> l >> r >> k;
        queries[i]  = {l, r, k};

        if (r > maxR) {
            maxR = r;
        }
    }

    vector<ll> productOfDigits(maxR+1, UNDEFINED);
    vector<ll> memoG(maxR+1, UNDEFINED);
    vector<vector<ll>> results(maxR+1, vector<ll>(10, 0));

    for (int i = 1; i <= maxR; i++) {
        ll result = g(i, memoG, productOfDigits);
        results[i][result]++;
    }

    for (int k = 1; k <= 9; k++) {
        for (int i = 1; i <= maxR; i++) {
            results[i][k] += results[i-1][k];
        }
    }

    for (auto t : queries){
        ll l = get<0>(t);
        ll r = get<1>(t);
        ll k = get<2>(t);

        ll answer = results[r][k] - results[l-1][k];
        cout << answer << "\n";
    }
};
