#include <bits/stdc++.h>

using namespace std;

const long long m = pow(10, 9) + 7;

vector<bool> ready;
vector<long long> value;
vector<long long> dices = {1,2,3,4,5,6};

long long solve(long long x){
    if (x < 0) return 0;
    if (ready[x]) return value[x];

    long long best = 0;

    for (auto c: dices){
        if (x - c >= 0){
            best += solve(x-c) % m;
        }
    }
    best = best % m;
    value[x] = best % m;
    ready[x] = true;

    return best;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    ready.assign(n + 1, false);
    value.assign(n + 1, 0);

    ready[0] = true;
    value[0] = 1;

    cout << solve(n) << "\n";
}
