#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        string s;
        cin >> n >> s;

        vector<int> prefixSum(n);

        prefixSum[0] = s[0] - '0';

        for (int j = 1; j < n; j++) {
            prefixSum[j] = prefixSum[j-1] + (s[j] - '0');
        }

        vector<int> res;

        for (int j = n-1; j >= 0; j--){
            int firstHalf = prefixSum[j];
            int secondHalf;
            int minimumLeft = (j+1)/2;
            int minimumRight = (n-(j+1) + 1)/2;
            
            if (j == n-1){
                if (firstHalf <= minimumLeft){
                    res.push_back(j+1);
                }
            } else {
                secondHalf = prefixSum[n-1] - prefixSum[j];
                if (firstHalf <= minimumLeft && minimumRight <= secondHalf){
                    res.push_back(j+1);
                }
            }
        }

        if (prefixSum[n-1] >= (n+1)/2){
            res.push_back(0);
        } 

        for (int j = 0; j < res.size(); j++){
            cout << "The " << res[j] << " house is good." << endl;
        }

        int bestHouse = res[0];

        for (int j = 1; j < res.size(); j++){
            int currentMin = abs((n+1)/2 - bestHouse);
            int possibleMin = abs((n+1)/2 - res[j]);

            if (possibleMin < currentMin && res[j] != 0){
                bestHouse = res[j];
            } else if (possibleMin == currentMin && res[j] != 0){
                bestHouse = min(bestHouse, res[j]);
            }
        }

        cout << bestHouse << "\n";
    }
}