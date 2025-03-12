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
        int x, y;
        cin >> x >> y;

        // En cada pantalla puede entrar como máximo 2ys, y 7xs.
        int minimumScreens = 0;
        bool specialScreen = false;

        while (y > 0){
            minimumScreens++;
            y-=2;
        }

        if (y % 2 != 0){
            x-=11;
            x -= (minimumScreens-1)*7;

            while (x > 0){
                minimumScreens++;
                x -=15;
            }
        } else {
            x -= minimumScreens*7;

            while (x > 0){
                minimumScreens++;
                x-=15;
            }
        }

        cout << minimumScreens << "\n";

    }
}