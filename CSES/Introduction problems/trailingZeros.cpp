#include <bits/stdc++.h>

using namespace std;

void trailingZeros(int n){
    int res = 0;

    for (int i = 5; i<n+1; i+=5){
        int num = i;

        while (num % 5 == 0){
            num /= 5;
            res ++;
        }
    }

    cout << res << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    trailingZeros(n);
}

