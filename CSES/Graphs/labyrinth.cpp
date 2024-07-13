#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    int startingRow;
    int startingCol;

    vector<vector<int>> levels;
    queue<pair<int, int>> toVisit;

    for (int i = 0; i < n; i++){
        string row;
        cin >> row;
        map[i] = row;

        for (int j = 0; j < m; j++){
            if (row[j] == 'A'){
                startingRow = i;
                startingCol = j;
            }
        }
    }

    toVisit.push({startingCol, startingRow});
    map[startingRow][startingCol] = '#';
    int distance = 0;
    bool existsPath = false;

    while (!toVisit.empty()){
        pair<int, int> current = toVisit.front();
        toVisit.pop();

        int currentX = current.first;
        int currentY = current.second;

        if (map[currentX][currentY] == 'B'){
            existsPath = true;
            break;
        }

        if (currentX + 1 < n && map[currentX + 1][currentY] != '#'){
            toVisit.push({currentX+1, currentY});
        }

        if (0 <= currentX - 1 && map[currentX - 1][currentY] != '#'){
            toVisit.push({currentX-1, currentY});
        }

        if (currentY + 1 < m && map[currentX][currentY + 1] != '#'){
            toVisit.push({currentX, currentY + 1});
        }

        if (0 <= currentY - 1 && map[currentX][currentY - 1] != '#'){
            toVisit.push({currentX, currentY - 1});
        }

        distance++;
    }

    if (!existsPath){
        cout << "NO" << "\n";
    } else {
        cout << "YES" << "\n";
        cout << distance << "\n";
    }
}
