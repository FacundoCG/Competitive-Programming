#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> availableFriends;

        for (int j = 0; j < m; j++){
            vector<int> availableDayI;
            int k;
            cin >> k;

            for (int h = 0; h < k; h++){
                int index;
                cin >> index;
                availableDayI.push_back(index);
            }

            availableFriends.push_back(availableDayI);
        }

        for (int j = 0; j < m; j++){

        }
    }
    
}
