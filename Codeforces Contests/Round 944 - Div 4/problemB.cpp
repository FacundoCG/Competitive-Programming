#include <bits/stdc++.h>
using namespace std;

void swap (string &s, int i, int j){
    char oldValue = s[i];
    s[i] = s[j];
    s[j] = oldValue;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        string s;
        cin >> s;

        char firstCharacter = s[0];
        int n = s.size();
        bool isPossibleRearrange = false;

        for (int j = 1; j < n; j++){
            if (s[j] != firstCharacter){
                isPossibleRearrange = true;
            }
        }

        if (isPossibleRearrange){
            cout << "YES" << "\n";

            for (int i = 0; i < n-1; i++){
                if (s[i] != s[i+1]){
                    swap(s, i, i+1);
                    break;
                }
            }

            cout << s << "\n";

        } else {
            cout << "NO" << "\n";
        }
    }
}