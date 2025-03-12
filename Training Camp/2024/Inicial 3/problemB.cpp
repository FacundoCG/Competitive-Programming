#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    bool giveTwoBags = a + b == c + d || a + c == b + d || a + d == c + b;
    bool giveThreeBags = a + b + c == d || a + b + d == c || a + c + d == b || b + c + d == a;

    if (giveTwoBags || giveThreeBags){
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
}
