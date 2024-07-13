#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n, a, b;
        cin >> n >> a >> b;

        if (2*a <= b){
            cout << a*n << "\n";
        } else {
            if (n % 2 == 0){
                cout << (n/2) * b << "\n";
            } else {
                cout << (n-1)/2 * b + a << "\n";
            }
        }
    }
}