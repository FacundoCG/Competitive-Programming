#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        bool found = false;
        string res = "";
        map<int, char> encode;
        int j = 1;
        
        int a,b,c;

        for (char c = 'a'; c <= 'z'; c++) {
            encode[j] = c;
            j++;
        }

        for (int k = 1; k <= 26; k++){
            for (int h = 1; h <= 26; h++) {
                for (int p = 1; p <= 26; p++) {
                    if (k + h + p == n){
                        a = k;
                        b = h;
                        c = p;
                        found = true;
                        break;
                    }
                }

                if (found){
                    break;
                }
            }

            if (found){
                break;
            }
        }

        res += encode[a];
        res += encode[b];
        res += encode[c];
        cout << res << "\n";
    }
}