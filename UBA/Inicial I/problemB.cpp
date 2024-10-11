#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        
        int n = s.size();
        int a = 0;
        int b = 0;

        for (int j = 0; j < n; j++) {
            if (s[j] == 'A') {
                a++;
            } else {
                b++;
            }
        }

        if (a > b){
            cout << "A" << "\n";
        } else {
            cout << "B" << "\n";
        }
    }
}
