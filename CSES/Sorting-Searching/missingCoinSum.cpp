#include <bits/stdc++.h>

using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<long long> coins(n);

    for (long long &v: coins) cin >> v;

    int res = 1;
    int sum = 0;

    sort(coins.begin(), coins.end());

    for (int i = 0; i < n; i++){
        if (res < coins[i] || res < sum){
            break;
        } else {
            sum += coins[i];
            res = coins[i] + 1;
        }
    }
}
