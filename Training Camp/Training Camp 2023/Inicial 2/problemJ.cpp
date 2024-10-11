#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;
const ll INF = LLONG_MAX;
const ll INF_NEG = LLONG_MIN;

vector<ll> suffixSum;

ll mostAmountPie (vector<ll> &slices, vector<vector<ll>>& memo, int i, int player){
    if (i >= slices.size()){
        return 0;
    }

    if (memo[i][player] == UNDEFINED){
        memo[i][player] = 0;
        ll player2;

        if (player == 0){
            player2 = 1;
        } else {
            player2 = 0;
        }

        ll ignorePie = mostAmountPie(slices, memo, i+1, player); // I maximize the pie that I can take between i+1 and n
        ll takePie = (ll) slices[i] + suffixSum[i+1] - mostAmountPie(slices, memo, i+1, player2); // My result is the current slice more what is left of the i+1 and n slices that maximizes the other player
        memo[i][player] = max(ignorePie, takePie); // My result is the best decision 
    }

    return memo[i][player];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<ll> slices(n);
    suffixSum.assign(n+1, 0);
    vector<vector<ll>> memo(n, vector<ll>(2, UNDEFINED));

    for (int i = 0; i < n; i++) cin >> slices[i];

    suffixSum[n-1] = slices[n-1];

    for (int i = n-2; i >= 0; i--){
        suffixSum[i] = suffixSum[i+1] + slices[i];
    }

    ll mostPieBob = mostAmountPie(slices, memo, 0, 0);
    ll mostPieceAlice = suffixSum[0] - mostPieBob;

    cout << mostPieceAlice << " " << mostPieBob << "\n";
};
