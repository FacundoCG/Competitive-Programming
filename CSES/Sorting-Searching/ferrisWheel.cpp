#include <bits/stdc++.h>

using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> children(n);

    for (long long &w : children) cin >> w;

    sort(children.begin(), children.end());

    int i = 0;
    int j = n-1;
    int res = 0;

    while (i <= j){
        if (children[i] + children[j] <= x){
            res ++;
            i++;
            j--;
        } else {
            res ++;
            j--;
        }
    }

    cout << res << "\n";
}
