#include <bits/stdc++.h>

using namespace std;

const int INF = 1000500;

vector<bool> ready (INF, false);
vector<int> value (INF);
vector<int> coins;

int solve(int x){
    if (x < 0) return INF;
    if (x == 0) return 0;
    if (ready[x]) return value[x];

    int best = INF;

    for (auto c: coins){
        best = min(best, solve(x-c)+1);
    }

    value[x] = best;
    ready[x] = true;

    return best;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int a;
    int n;
    
    cin >> n;

    while (cin >> a) {
        coins.push_back(a);
    }

    cout << solve(n) << "\n";
}
