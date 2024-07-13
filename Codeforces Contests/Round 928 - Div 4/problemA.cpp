#include <bits/stdc++.h>

using namespace std;

char mostRepetitions (string s){
    int a = 0;
    int b = 0;

    for (int i = 0; i < s.length(); i++){
        if (s[i] == 'A'){
            a++;
        } else {
            b++;
        }
    }

    if (b > a){
        return 'B';
    } else {
        return 'A';
    }
}



int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        cout << mostRepetitions(s) << '\n';
    }
}