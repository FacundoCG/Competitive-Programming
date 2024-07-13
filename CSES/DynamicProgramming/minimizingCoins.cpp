#include <bits/stdc++.h>

using namespace std;

const int INF = 1000500;

vector<bool> ready;
vector<long long> value;
vector<long long> coins;

long long solve(long long x){
    if (x < 0) return INF;
    if (ready[x]) return value[x];

    long long best;

    for (auto c: coins){
        best = min(solve(x-c)+1, best);
    }

    value[x] = best;
    ready[x] = true;

    return best;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;
    long long x;
    cin >> x;

    ready.assign(x + 1, false);
    value.assign(x + 1, 0);

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        coins.push_back(c);
    }

    ready[0] = true;
    value[0] = 0;

    int minimunNumberCoins = solve(x);

    if (minimunNumberCoins == INF) {
        cout << -1 << "\n";
    } else{
        cout << solve(x) << "\n";
    }

}
