#include <bits/stdc++.h>
using namespace std;

const long long MOD = pow(10, 9) + 7;

int countingTilings(int i, int j, vector<vector<int>>& memo){
    if ((i == 1 && j == 1) || i < 1 || j < 1){
        return 0;
    } else if ((i == 2 && j == 1) || (i == 1 && j == 2)){
        return 1;
    } 

    if (memo[i][j] == -1){
        int puttingRow = 0;
        int puttingColumn = 0;

        if (i == 2 && j == 2){
            memo[i][j] = countingTilings(i-1, j, memo) + countingTilings(i, j-1, memo);
        } else if (j > 2 && i > 2){ // I can put a row and a column
            int S1 = countingTilings(i, j-2, memo);
            int S2 = countingTilings(i - 1, 2, memo);
            int S3 = countingTilings(i-1, j, memo);
            int S4 = countingTilings(1, j-2, memo);
            
            if (S1 != 0 && S2 != 0){
                puttingRow += S1 * S2;
            }

            if (S3 != 0 && S4 != 0){
                puttingRow += S3 * S4;
            }

            int Z1 = countingTilings(i - 2, j, memo);
            int Z2 = countingTilings(2, j-1, memo);
            int Z3 = countingTilings(i, j-1, memo);
            int Z4 = countingTilings(i-2, 1, memo);

            if (Z1 != 0 && Z2 != 0){
                puttingColumn += Z1 * Z2;
            }        

            if (Z3 != 0 && Z4 != 0){
                puttingColumn += Z3 * Z4;
            }

            puttingRow = S1 * S2 + S3 * S4;
            puttingColumn = Z1 * Z2 + Z3 * Z4;

            memo[i][j] = puttingColumn + puttingRow;
        } else if (j >= 2 && i == 1){
            int puttingRow = countingTilings(i, j-2, memo);
            memo[i][j] = puttingRow;
        } else if (i >= 2 && j == 1){
            int puttingColumn = countingTilings(i - 2, j, memo);
            memo[i][j] = puttingColumn;
        } 
    }

    return memo[i][j];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> memo(n+1, vector<int>(m+1, -1));

    cout << countingTilings(n, m, memo) << "\n";
}