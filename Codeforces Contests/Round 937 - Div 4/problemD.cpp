#include <bits/stdc++.h>
using namespace std;

void digits(int n, vector<int>& arr){
    if (n < 10){
        arr.push_back(n);
    } else {
        arr.push_back(n%10);
        digits(n/10, arr);
    }
}

bool isBinaryDecimal(int n){
    vector<int> digitsNumber;
    digits(n, digitsNumber);

    int m = digitsNumber.size();
    bool res = true;

    for (int i = 0; i < m; i++) {
        if (digitsNumber[i] != 0 && digitsNumber[i] != 1) {
            res = false;
        }
    }

    return res;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    int max = 0;
    vector<int> numbers(t);

    for (int i = 0; i < t; i++){
        int m;
        cin >> m;
        numbers[i] = m;

        if (m > max){
            max = m;
        }
    }

    vector<bool> memo(max+1, false);

    for (int i = 0; i <= max; i++){
        if (isBinaryDecimal(i)){
            memo[i] = true;
        }
    }

    for (int i = 2; i <= max; i++){
        if (memo[i] == true){
            for (int j = 2; j <= max; j++){
                if (memo[j] == true && i * j <= max){
                    memo[i*j] = true;
                }
            }
        }
    }

    for (int i = 0; i < t; i++){
        if (memo[numbers[i]]){
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }   
}