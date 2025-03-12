#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    ll n, x0, y0, x1, y1;
    cin >> n >> x0 >> y0 >> x1 >> y1;

    ll dx = (ll) x0-x1;
    ll dy = (ll) y0-y1;
    dx = abs(dx);
    dy = abs(dy);
    ll minMoves = (ll) dx + dy;
    ll res;

    if (minMoves == 0){
        res = n/2;
        cout << res << "\n";
        return 0;
    } 

    while (minMoves <= n){
        res++;
        minMoves+=2;
    }

    cout << res << "\n";
}
