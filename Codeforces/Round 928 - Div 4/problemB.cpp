#include <bits/stdc++.h>

using namespace std;

string shapeGrid(vector<vector<int>> grid)
{
    string res = "SQUARE";
    int n = grid.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && grid[0][j] == 1 && grid[1][j] != 1)
            {
                res = "TRIANGLE";
            }
            else if (i == n - 1 && grid[n - 1][j] == 1 && grid[n - 2][j] != 1)
            {
                res = "TRIANGLE";
            }
            else if (0 < i && i < n - 1 && (grid[i][j] == 1 && grid[i - 1][j] != 1) && (grid[i][j] == 1 && grid[i + 1][j] != 1))
            {
                res = "TRIANGLE";
            }
        }
    }

    return res;
}

int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;

        vector<vector<int>> grid(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            string m;
            cin >> m;

            for (int j = 0; j < n; j++)
            {
                grid[i][j] = m[j] - '0';
            }
        }

        cout << shapeGrid(grid) << "\n";
    }
}