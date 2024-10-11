#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll zero = 0;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> apartments(n);
    vector<ll> sizes(m);

    for (int i = 0; i < n; i++) cin >> apartments[i];
    for (int i = 0; i < m; i++) cin >> sizes[i];

    sort(apartments.begin(), apartments.end());
    sort(sizes.begin(), sizes.end());

    ll res = 0;
    int j = 0;
    int i = 0;

    while (j < m && i < n){
        ll sizeDesired = apartments[i];
        ll bestSize = sizes[j];
        ll lowerBound = (ll) bestSize - k;
        lowerBound = max(lowerBound, zero);
        ll upperBound = (ll) bestSize + k;

        if (lowerBound <= sizeDesired && sizeDesired <= upperBound){ // If my option is in range, I take it.
            res++;
            i++;
            j++;
        } else if (upperBound < sizeDesired){ // If my option is smaller than the desired apartment, let's see the next option.
            j++;
        } else if (sizeDesired < lowerBound){ // If my option is bigger than the desired apartment, let's continue with my next desired apartment
            i++;
        }
    }

    cout << res << "\n";
}
