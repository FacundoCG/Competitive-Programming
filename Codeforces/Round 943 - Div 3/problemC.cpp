#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        vector<int> values(n-1);
        vector<int> answer(n);

        for (int j = 0; j < n-1; j++){
            int x;
            cin >> x;
            values[j] = x;
        }

        answer[0] = 501;

        for (int k = 1; k < n; k++){
            answer[k] = answer[k-1] + values[k-1];
        }

        for (int k = 0; k < n; k++){
            cout << answer[k] << " ";
        } 

        cout << "\n";
    }
}