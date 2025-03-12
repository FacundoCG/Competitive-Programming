#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> numbers(n);
        vector<int> prefixSum(n);

        for (int &j : numbers) cin >> j;

        prefixSum[0] = abs(numbers[0]);

        for (int j = 1; j < n; j++){
            prefixSum[j] = prefixSum[j - 1] + abs(numbers[j]);
        }

        cout << prefixSum[n-1] << "\n";
    }
}