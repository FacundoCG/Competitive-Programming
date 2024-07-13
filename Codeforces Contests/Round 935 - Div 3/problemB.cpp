#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long a,b,m;

        cin >> a >> b >> m;

        if (a > m && b > m){
            cout << 2 << "\n";
        } else if (a == m && b < m){
            cout << 2 + m/b + 1 << "\n";
        } else if (b == m && a < m){
            cout << 2 + m/a + 1 << "\n";
        } else if ((a == m && b > m) || (b == m && a > m)){ 
            cout << 3 << "\n";
        } else if (a == m && b == m){
            cout << 4 << "\n";
        } else if (a < m && b > m){
            cout << 1 + m/a + 1 << "\n";
        } else if (b < m && a > m){
            cout << 1 + m/b + 1 << "\n";
        } else {
            cout << m/a + m/b + 2 << "\n";
        }
    }
}