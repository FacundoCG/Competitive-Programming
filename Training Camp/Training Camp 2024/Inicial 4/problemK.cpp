#include <bits/stdc++.h>
using namespace std;


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int rocks = 0;

    for (int i = 0; i < n; i++){
        if (s[i] == '+'){
            rocks++;
        } else if (rocks > 0 && s[i] == '-'){
            rocks--;
        }
    }

    cout << rocks << "\n";
}
