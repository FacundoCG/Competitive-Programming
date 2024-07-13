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
        bool eliminateOne = false;

        for (int &j : numbers) cin >> j;

        prefixSum[0] = abs(numbers[0]);

        for (int j = 1; j < n; j++){
            prefixSum[j] = prefixSum[j - 1] + abs(numbers[j]);
        }

        long long totalSum = prefixSum[n-1];
        int res = 0;

        if (totalSum % 3 == 2){
            res = 1;
        } else if (totalSum % 3 == 1){
            for (int j = 0; j < n; j++){
                if ((totalSum - numbers[j]) % 3 == 0){
                    res = 1;
                    eliminateOne = true;
                    break;
                }
            }

            if (!eliminateOne){
                res = 2;
            }
        }

        cout << res << "\n";
    }
}