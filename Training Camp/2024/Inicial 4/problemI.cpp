#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n,k,x;
    cin >> n >> k >> x;

    vector<int> chores(n);
    vector<int> prefixSum(n);

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;

        chores[i] = c;

        if (i == 0){
            prefixSum[i] = c;
        } else {
            prefixSum[i] = prefixSum[i-1] + c;
        }
    }
    
    int minimumWork;

    if (k == n){
        minimumWork = n*x;
    } else {
        minimumWork = k*x + prefixSum[n-k-1];
    }

    cout << minimumWork << "\n";
}
