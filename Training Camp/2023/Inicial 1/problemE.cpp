#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<ll> rooms(n);

    for (int i = 0; i < n; i++) cin >> rooms[i];

    sort(rooms.begin(), rooms.end());

    cout << rooms[m-1] << "\n";
}
