#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n, d, e;
    cin >> n >> d >> e;

    int res = n;

    for (int i = 0; i < n; i++){
        int rublesLeft;

        if (n >= i*d && (n - i*d) >= 5*e){
            rublesLeft = (n - i*d) % (5*e);
            res = min(res, rublesLeft);
        }

        if (n >= i*d){
            rublesLeft = (n - i*d);
            res = min(res, rublesLeft);
        }

        if (n >= 5*e){
            rublesLeft = n % (5*e);
            res = min(res, rublesLeft);
        }
    }

    cout << res << "\n";
}
