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

    for (int i = 0; i < t; i++){
        int m;
        long long x;

        cin >> m >> x;

        int maxHappines = 0;

        vector<pair<long long, int>> happinesPrices(m);
        for (int j = 0; j < m; j++){
            long long c;
            int h;
            cin >> c >> h;

            maxHappines += h;
            happinesPrices[j] = {c, h};
        }

        vector<int> minimumCostHappines(maxHappines);

        for (int j = 0; j < m; j++){
            
        }

        vector<long long> memo(m+1);
        memo[0] = 0;

        for (int i = 1; i < m; i++){
            
        }
    }
}