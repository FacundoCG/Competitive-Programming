#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    long long res = 0;
    int firstDigit = s[0];

    if (firstDigit % 2 == 0){
        res++;
    }

    for (int i = 1; i < n; i++){
        int digit = s[i];

        if (digit % 2 == 0){
            res += i+1;
        }
    }

    cout << res << "\n";
}
