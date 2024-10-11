#include <bits/stdc++.h>
using namespace std;

int main() {
    //ios :: sync_with_stdio(0);
    //cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long n;
        cin >> n;

        int res = 1;
        long long j = 2;
        long long square = 4;
        long long cube = 8;
        vector<long long> goodNumbers;


        while(square <= n){
            goodNumbers.push_back(square);
            res++;
            j++;
            square = (long long) pow(j, 2);
        }

        j = 2;

        while(cube <= n){
            auto itr = lower_bound(goodNumbers.begin(), goodNumbers.end(), cube);

            if (*itr != cube){
                res++;
            }

            j++;
            cube = (long long) pow(j, 3);
        }  

        cout << res << "\n";
    }
}
