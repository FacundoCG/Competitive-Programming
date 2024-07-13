#include <bits/stdc++.h>

using namespace std;

void coinPiles(int n) {
    for (int i = 0; i < n; i++) {
        int a;
        int b; 
        cin >> a;
        cin >> b;

        if ((a+b) % 3 == 0){
            if ((a>=b && a<=2*b) || (b>=a && b<=2*a)){
                cout << "YES" << "\n";
            } else{
                cout << "NO" << "\n";
            }
        } else{
            cout << "NO" << "\n";
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    coinPiles(n);
}
