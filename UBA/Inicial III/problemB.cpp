#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<bool> stateBulbs(m, false);
    
    for (int i = 0; i < n; i++){
        int k;
        cin >> k;

        for (int j = 0; j < k; j++){
            int p;
            cin >> p;
            stateBulbs[p-1] = true;
        }
    }

    string res = "YES";

    for (int i = 0; i < m; i++){
        if (!stateBulbs[i]){
            res = "NO";
            break;
        }
    }

    cout << res << "\n";
}