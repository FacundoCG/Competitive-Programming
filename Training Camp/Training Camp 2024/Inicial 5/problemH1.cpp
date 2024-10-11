#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int j = 0; j < t; j++) {
        string s;
        cin >> s;

        int n = s.size();
        int ab = 0;
        int ba = 0;
        int minimumSteps = 0;

        for (int i = 1; i < n; i++) {
            if (s[i-1] == 'a' && s[i] == 'b'){
                ab++;
            } else if (s[i-1] == 'b' && s[i] == 'a'){
                ba++;
            }
        }

        int i = 0;

        if (ab > ba){
            while (ab != ba && i < n-1){
                if(s[i] == 'a' && s[i+1] == 'b'){
                    s[i] = 'b';
                    ab--;
                    minimumSteps++;
                }

                i++;
            }
        } else if (ab < ba){
            while (ab != ba && i < n-1){
                if(s[i] == 'b' && s[i+1] == 'a'){
                    s[i] = 'a';
                    ba--;
                    minimumSteps++;
                }

                i++;
            }
        }

        cout << s << "\n";
    }
}   
