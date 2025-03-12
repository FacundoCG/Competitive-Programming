#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        string s;
        cin >> s;

        int n = s.size();
        int totalPieces = 1;
        int specialPieces = 0;

        for (int i = 1; i < n; i++){
            if (s[i] == '0' && s[i-1] == '1'){
                totalPieces++;
            }

            if (s[i] == '1' && s[i-1] == '0'){
                specialPieces++;
            }
        }

        int res;

        if (specialPieces > 1){
            res = (totalPieces - specialPieces) + (specialPieces-1)*2 + 1;
        } else {
            res = totalPieces;
        }

        cout << res << "\n";
    }
}