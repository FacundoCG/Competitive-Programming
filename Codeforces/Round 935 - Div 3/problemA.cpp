#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long a,b,c;

        cin >> a >> b >> c;

        long long minimumTents = a;
        long long extrovertsSharing = b/3;
        minimumTents += extrovertsSharing;
        long long restExtroverts = b%3;

        if (restExtroverts != 0 && restExtroverts + c < 3){
            cout << -1 << "\n";
        } else {
            minimumTents += (restExtroverts + c + 3 - 1)/3;
            cout << minimumTents << "\n";
        }
    }
}