#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, x;
    cin >> n >> x;
    
    vector <int> prices(n), pages(n);

    vector<vector<int> > dp (n+1, vector<int> (x+1, 0));
 
    for (int&v : prices) cin >> v;
    for (int&v : pages) cin >> v;

    for (int i = 1; i <= n; i++){
        for (int j = x; j >= 0; j--){
            if (j - prices[i-1] < 0){
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(pages[i-1]+dp[i-1][j - prices[i-1]], dp[i-1][j]);
            }
        }
    }

    cout << dp[n][x] << endl; 
}