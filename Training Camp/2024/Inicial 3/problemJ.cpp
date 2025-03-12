#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<long long> damage(n);
    vector<long long> prefixSum(n);

    long long res = 0;

    for (int i = 0; i < n; i++){
        long long v;
        cin >> v;
        damage[i] = v;
        res += v;

        if (i == 0){
            prefixSum[0] = v;
        } else {
            prefixSum[i] = v + prefixSum[i - 1];
        }
    }
    

    string s;
    cin >> s;

    vector<pair<int, int>> intervalsOfSubsequences;

    int origin = 0;
    int final = 0;

    for (int i = 1; i < n; i++){
        if (s[i] == s[i-1]){
            final++;
        } else{
            if (final - origin + 1 > k){
                //cout << "I have the pairs with origin: " << origin << " and final: " << final << "\n";
                intervalsOfSubsequences.push_back({origin, final});
            }
            final++;
            origin = final;
        }
    }

    int m = intervalsOfSubsequences.size();
    int lengthInterval = final - origin + 1;

    if ((m == 0 && lengthInterval > k) || (m > 0 && intervalsOfSubsequences[m-1].first != origin && intervalsOfSubsequences[m-1].second != final && lengthInterval > k)){
        intervalsOfSubsequences.push_back({origin, final});
    }


    for (pair<int, int> &p : intervalsOfSubsequences){
        vector<long long> subsequence;
        int start = p.first;
        int final = p.second;

        //cout << "I am with the pair with start: " << start << ", final: " << final << "\n";
        for (int i = start; i <= final; i++){
            //cout << "My subsequence has: " << damage[i] << finall;
            subsequence.push_back(damage[i]);
        }

        if (start != 0){
            res -= prefixSum[final] - prefixSum[start-1];
        } else {
            res -= prefixSum[final];
        }

        sort(subsequence.begin(), subsequence.end());
        int m = subsequence.size();

        for (int i = m-1; i >= m-k; i--) {
            res += subsequence[i];
        }
    }
    //cout << "My res without the subsequences is: " << res << finall;

    cout << res << "\n";
}
