#include <bits/stdc++.h>

using namespace std;

const long long m = pow(10, 9) + 7;

vector<bool> ready;
vector<long long> value;
vector<long long> coins;

long long solve(long long x){
    if (x < 0) return 0;
    if (ready[x]) return value[x];

    long long best = 0;
    unordered_set<long long> distinctSums;

    for (auto c: coins){
        if (x - c >= 0){
            best += solve(x-c);
        }
    }

    value[x] = best % m;
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
        long long c;
        cin >> c;
        coins.push_back(c);
    }

    ready[0] = true;
    value[0] = 1;

    cout << solve(x) << "\n";
}
