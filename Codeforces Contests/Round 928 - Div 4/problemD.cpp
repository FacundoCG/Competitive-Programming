#include <bits/stdc++.h>

using namespace std;

void decimalToBinaryAlgorithm (int n, vector<int>& arr){
    if (n == 0){
        return arr.push_back(0);
    } else if (n == 1){
        return arr.push_back(1);
    } else {
        arr.push_back(n%2);
        return decimalToBinaryAlgorithm(n/2, arr);
    }
}

vector<int> decimalToBinary(int n) {
    vector<int> res;
    decimalToBinaryAlgorithm(n , res);
    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) { // O(t)
        int n;
        cin >> n;

        vector<int> nums (n,0);

        for (int j = 0; j < n; j++) {
            int k;
            cin >> k;
            nums[j] = k;
        }

    }
}