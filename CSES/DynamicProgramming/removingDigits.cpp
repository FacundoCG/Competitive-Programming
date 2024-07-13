#include <bits/stdc++.h>

using namespace std;

void calculateDigits(int n, vector<int>& digitsArr){
    if (n != 0){
        digitsArr.push_back(n%10);
        calculateDigits(n/10, digitsArr);
    }
}

vector<int> digits(int n){
    vector<int> digitsArr;

    if (n == 0){
        digitsArr.push_back(0);
    } else {
        calculateDigits(n, digitsArr);
    }

    return digitsArr;
}

int removingDigits(vector<int>& memo, int n){
    if (n < 10){
        return 1;
    }

    if (memo[n] == INT_MAX){
        vector<int> digitsArr = digits(n);
        int m = digitsArr.size();

        for (int i = 0; i < m; i++){
            if (digitsArr[i] != 0){
                memo[n] = min(memo[n], 1 + removingDigits(memo,n - digitsArr[i]));
            }
        }
    }

    return memo[n];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> memo(n+1, INT_MAX);

    cout << removingDigits(memo, n) << "\n";
}
