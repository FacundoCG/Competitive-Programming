#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;


    for (int i = 0; i < t; i++){
        int n, m;
        cin >> n >> m;

        string a;
        string b;

        cin >> a >> b;

        int j = 0;

        for (int k = 0; k < m; k++){
            if (j == n){
                break;
            }

            if (a[j] == b[k]){
                j++;
            }
        }

        cout << j << "\n";
    }
}