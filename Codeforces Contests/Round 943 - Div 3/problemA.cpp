#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    while (a > 0 && b > 0){
        if (a > b){
            a = a%b;
        } else {
            b = b%a;
        }
    }

    if (a == 0){
        return b;
    } 

    return a;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;


    for (int i = 0; i < t; i++){
        int x;
        cin >> x;

        int y;
        int res = 0;

        for (int j = x-1; j >= 1; j--){
            int candidate = gcd(x, j) + j;
            if (candidate > res){
                res = candidate;
                y = j;
            }
        }

        cout << y << "\n";
    }
}