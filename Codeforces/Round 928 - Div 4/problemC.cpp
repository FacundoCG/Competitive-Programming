#include <bits/stdc++.h>

using namespace std;

int digitSum(int n){
    if (n < 10){
        return n;
    } else {
        return digitSum(n/10) + n%10;
    }
}

int max (vector<int> arr){
    int n = arr.size();
    int res = arr[0];

    for (int i = 1; i < n; i++){
        if (arr[i] > res){
            res = arr[i];
        }
    }

    return res;
}



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    vector<int> digits (t,0); // O(t)

    for (int i = 0; i < t; i++) { // O(t)
        int n;
        cin >> n;
        digits[i] = n;
    }

    int m = max(digits); // O(t)

    vector<int> answers (m+1, 0);
    answers[0] = 0;
    answers[1] = 1;

    for (int i = 2; i < m+1; i++) { // O(n * log n)
        answers[i] = answers[i-1] + digitSum(i);
    }

    for (int i = 0; i < t; i++) { // O(t)
        int k = digits[i];
        cout << answers[k] << '\n';
    }
}