#include <bits/stdc++.h>

using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> nums(n);
    vector<long long> sortedNums(n);

    for (long long &v: nums) cin >> v;
    
    for (int i = 0; i < n; i++){
        sortedNums[i] = nums[i];
    }

    sort(sortedNums.begin(), sortedNums.end());

    int i = 0;
    int j = n-1;

    tuple<int, int> res = {-1, -1};

    while (i < j){
        if (sortedNums[i] + sortedNums[j] == x){
            res = {i, j};
            break;
        } else if (sortedNums[i] + sortedNums[j] < x){
            i++;
        } else {
            j--;
        }
    }




    if (get<0>(res) == -1){
        cout << "IMPOSSIBLE" << "\n";
    } else {
        int a = get<0>(res);
        int b = get<1>(res);
        for (int i = 0; i < n; i++){
            if (sortedNums[a] == nums[i]){
                a = i;
                break;
            }
        }

        for (int i = 0; i < n; i++){
            if (sortedNums[b] == nums[i] && i != a){
                b = i;
                break;
            }
        }

        cout << a+1 << " " << b+1 << "\n";
    }
}
