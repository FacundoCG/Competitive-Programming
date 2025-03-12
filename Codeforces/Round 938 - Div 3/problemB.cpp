#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n, c, d;
        cin >> n >> c >> d;

        int min = INT_MAX;
        map<int, int> apparitions;
        vector<vector<int>> progressiveSquare(n, vector<int>(n));

        for (int j = 0; j < n*n; j++){
            int k;
            cin >> k;

            if (min > k){
                min = k;
            }

            if (apparitions.find(k) == apparitions.end()){
                apparitions[k] = 1;
            } else {
                apparitions[k]++;
            }
        }

        progressiveSquare[0][0] = min;

        for (int j = 1; j < n; j++){
            progressiveSquare[0][j] = progressiveSquare[0][j-1] + d;
        }

        for (int j = 1; j < n; j++){
            for (int k = 0; k < n; k++){
                progressiveSquare[j][k] = progressiveSquare[j-1][k] + c;
            }
        }

        map<int, int> apparitionsSquare;

        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                if (apparitionsSquare.find(progressiveSquare[j][k]) == apparitionsSquare.end()){
                    apparitionsSquare[progressiveSquare[j][k]] = 1;
                } else {
                    apparitionsSquare[progressiveSquare[j][k]]++;
                }
            }
        }

        if (apparitionsSquare == apparitions){
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
}