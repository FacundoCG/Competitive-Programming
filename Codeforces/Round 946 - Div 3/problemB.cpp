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
        int n;
        string s;
        cin >> n >> s;

        set<char> distinctLetters;
        map<char, char> encode;
        string r = "";

        for (int j = 0; j < n; j++){
            distinctLetters.insert(s[j]);
        }

        for (char c : distinctLetters){
            r += c;
        }

        int p = 0;
        int k = r.size() - 1;

        while (p <= k){
            encode[r[p]] = r[k];
            encode[r[k]] = r[p];
            p++;
            k--;
        }

        for (int j = 0; j < n; j++){
            s[j] = encode[s[j]];
        }

        cout << s << "\n";
    }
}