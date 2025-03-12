#include <bits/stdc++.h>
using namespace std;

long long minimumDistance(vector<long long>& arr, int k, bool hasToReturn){
    int m = arr.size();
    long long res = 0;
    int visited = 0;
    
    for (int i = m - 1; i >= 0; i -= k) {
        res += (long long) 2 * arr[i];
    }

    if (!hasToReturn) {
        res -= arr[m - 1];
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;

        vector<long long> positiveDistances;
        vector<long long> negativeDistances;

        for (int j = 0; j < n; j++){
            long long v;
            cin >> v;

            if (v >= 0){
                positiveDistances.push_back(v);
            } else {
                negativeDistances.push_back(abs(v));
            }
        }

        sort(positiveDistances.begin(), positiveDistances.end());
        sort(negativeDistances.begin(), negativeDistances.end());

        int y = positiveDistances.size();
        int z = negativeDistances.size();
        
        long long res = 0;

        if (y > 0 && z > 0 && positiveDistances[y-1] > negativeDistances[z-1]) {
            res += minimumDistance(negativeDistances, k, true);
            res += minimumDistance(positiveDistances, k, false);
        } else if (y > 0 && z > 0 && positiveDistances[y-1] <= negativeDistances[z-1]){
            res += minimumDistance(positiveDistances, k, true);
            res += minimumDistance(negativeDistances, k, false);
        } else if (z == 0){
            res = minimumDistance(positiveDistances, k, false);
        } else {
            res = minimumDistance(negativeDistances, k, false);
        }

        cout << res << "\n";
    }
}
