#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        string s;
        cin >> s;

        bool isMeow = true;

        if ((s[0] != 'M' && s[0] != 'm') || (s[n-1] != 'w' && s[n-1] != 'W')){
            isMeow = false;
        }

        for (int j = 1; j < n; j++){
            if (s[j-1] == 'M' || s[j-1] == 'm'){
                if (s[j] != 'M' && s[j] != 'm' && s[j] != 'e' && s[j] != 'E'){
                    isMeow = false;
                    break;
                }
            } else if (s[j-1] == 'e' || s[j-1] == 'E'){
                if (s[j] != 'e' && s[j] != 'E' && s[j] != 'o' && s[j] != 'O'){
                    isMeow = false;
                    break;
                }
            } else if (s[j-1] == 'o' || s[j-1] == 'O'){
                if (s[j] != 'o' && s[j] != 'O' && s[j] != 'w' && s[j] != 'W'){
                    isMeow = false;
                    break;
                }
            } else if (s[j-1] == 'W' || s[j-1] == 'w'){
                if (s[j] != 'W' && s[j] != 'w'){
                    isMeow = false;
                    break;
                }
            } else {
                isMeow = false;
                break;
            }
        }

        if (isMeow){
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
}
