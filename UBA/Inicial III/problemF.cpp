#include <bits/stdc++.h>
using namespace std;

long long boredom_TD(vector<int>& arr, vector<long long>& memo, map<int, int>& repetitions, int i){
    if (i < 0){
        return 0;
    } 

    if (memo[i] == -1){
        long long extra = (long long) arr[i]*repetitions[arr[i]];
        if(0<= i-1 && arr[i] == arr[i-1] + 1){
            memo[i] = max(extra + boredom_TD(arr, memo, repetitions, i-2), boredom_TD(arr, memo, repetitions, i-1));
        } else {
            memo[i] = extra + boredom_TD(arr, memo, repetitions, i-1);
        }
    }

    return memo[i];
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> numbers(n);

    for (int &j: numbers) cin >> j;

    map<int, int> repetitions;

    for (int j : numbers){
        if (repetitions.find(j) == repetitions.end()){
            repetitions[j] = 1;
        } else {
            repetitions[j]++;
        }
    }

    vector<int> distinctNumbers;
    for (const auto &pair : repetitions){
        distinctNumbers.push_back(pair.first);
    }

    int k = distinctNumbers.size();
    sort(distinctNumbers.begin(), distinctNumbers.end());
    vector<long long> memo(k, -1);

    cout << boredom_TD(distinctNumbers, memo, repetitions, k-1) << "\n";    
}