#include <bits/stdc++.h>

using namespace std;

void algorithm(long long n) {
    
    while(n!=1) {
        if (n%2==0) {
            n = n/2;
        } else {
            n = n*3 + 1;
        }
        cout << n << " ";
    }

}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    cout << n << " ";
    algorithm(n);
}
