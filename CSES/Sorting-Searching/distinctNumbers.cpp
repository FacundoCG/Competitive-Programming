#include <bits/stdc++.h>

using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<long long> nums(n);

    for (long long &v : nums) cin >> v;

    sort(nums.begin(), nums.end());

    int res = 1;

    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i-1]){
            res ++;
        }
    }

    cout << res << "\n";
}
