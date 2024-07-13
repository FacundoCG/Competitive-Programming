#include <bits/stdc++.h>

using namespace std;

long long kthCard(long long n, long long k, int i){
    if (k <= ceil((double)n/2)){
        return (2*k - 1)* pow(2,i);
    } else {
        return kthCard(n - ceil((double)n/2), k - ceil((double)n/2), i+1);
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long n, k;
        cin >> n >> k;
        
        cout << kthCard(n,k,0) << '\n';
    }
}