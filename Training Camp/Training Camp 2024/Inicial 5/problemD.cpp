#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long a, b, c;

        int maximum = max(a, max(b, c));
        int minimum = min(a, min(b, c));
        int mid;

        if ((a == maximum && b == minimum) || (a == minimum && b == maximum)){
            mid = c;
        } else if ((a == maximum && c == minimum) || (a == minimum && c == maximum)) {
            mid = b;
        } else {
            mid = a;
        }

        while (maximum != mid){
            
        }
    }
}
