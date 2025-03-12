#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        string s;
        cin >> n >> s;

        vector<int> prefixSum(n);
        prefixSum[0] = s[0] - '0';
        int res;

        for (int j = 1; j < n; j++){
            prefixSum[j] = prefixSum[j-1] + (s[j] - '0');
        }

        for (int j = n; j >= 1; j--){
            if (prefixSum[j-1] == j || prefixSum[j-1] == 0){
                res = j;
                break;
            }
        }

        cout << res << "\n";
    }
}