#include <iostream>
#include <vector>
using namespace std;

void dfs(int x, int y, vector<string> &grid, vector<vector<bool> > &visited){
	visited[x][y] = true;
	if (x+1 < (int) grid.size() && !visited[x+1][y] && grid[x+1][y] == '.') dfs(x+1, y, grid, visited);
	if (0 <= x-1 && !visited[x-1][y] && grid[x-1][y] == '.') dfs(x-1, y, grid, visited);
	if (y+1 < (int) grid[0].size() && !visited[x][y+1] && grid[x][y+1] == '.') dfs(x, y+1, grid, visited);
	if (0 <= y-1 && !visited[x][y-1] && grid[x][y-1] == '.') dfs(x, y-1, grid, visited);
}

int main()
{
    int w, h;
    cin >> w >> h;
    
    while (w != 0){
		vector<string> grid(h);
		vector<vector<bool> > visited(h, vector<bool>(w));
		for(int i=0; i < h; i++) cin >> grid[i];
		
		int x = 0;
		int y = 0;
		
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				if (grid[i][j] == '@'){
					x = i;
					y = j;
				}
			}
		}
				
		dfs(x, y, grid, visited);

		int blackTilesVisited = 0;
		
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				if (visited[i][j]) blackTilesVisited++;
			}
		}
		
		cout << blackTilesVisited << "\n";
		cin >> w >> h;
	}

    return 0;
}


