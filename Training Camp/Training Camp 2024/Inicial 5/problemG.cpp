#include <bits/stdc++.h>
using namespace std;

long long biggestNumber(vector<int>& digits, int i){
    if (i == -1){
        return 0;
    }

    int number = digits[i];
    int m = digits.size();
    long long res = 1;
    long long normal = 1;
    long long extra = number-1;
    
    if (extra == 0){
        extra = 1;
    } 

    for (int j = m-1; j >= 0; j--){
        if (j == i){
            res *= (long long) extra;
        } else if (j > i){
            res *= (long long) digits[j];
        } else {
            res *= (long long) 9;
        }
    }

    for (int j = m-1; j >= 0; j--){
        normal *= digits[j];
    }
    
    res = max(max(res, normal), biggestNumber(digits, i-1));
    return res;
}

void decimalDigit(vector<int>& digits, long long n){
    if (n <= 9){
        digits.push_back(n);
        return;
    }

    digits.push_back(n%10);
    decimalDigit(digits, n/10);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    vector<int> digits;
    decimalDigit(digits, n);
    int m = digits.size();

    long long res = biggestNumber(digits, m-1);
    cout << res << "\n";
}   
