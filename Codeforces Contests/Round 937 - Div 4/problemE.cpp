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

       map<char, int> letterRepetitions;
       int diff = n;

       for (int j = 0; j < n; j++) {
            if (letterRepetitions.find(s[j]) != letterRepetitions.end()){
                letterRepetitions[s[j]]++;
            } else {
                letterRepetitions[s[j]] = 1;
            }
       }

       int min = letterRepetitions.size();


    }
}