#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;    

    for (int i = 0; i < t; i++) {
        long long x, y;
        cin >> x >> y;

        long long diferencia = (long long ) x - y;

        if (diferencia != 1){
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
}
