#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main(){
	int n;
	cin >> n;
	
	while (n != 0){
		vector<vector<int> > grid(n, vector<int>(n));
		
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++) cin >> grid[i][j];
		}
		
		int badRows = 0;
		int badColumns = 0;
		
		int badRow = 0;
		int badColumn = 0;
		
		for (int i = 0; i < n; i++){
			int sumOfRow = 0;
			for (int j = 0; j < n; j++) sumOfRow += grid[i][j];
			badRows += (sumOfRow % 2 == 1);
			if (sumOfRow % 2 == 1) badRow = i;
		}
		
		for (int i = 0; i < n; i++){
			int sumOfColumn = 0;
			for (int j = 0; j < n; j++) sumOfColumn += grid[j][i];
			badColumns += (sumOfColumn % 2 == 1);
			if (sumOfColumn % 2 == 1) badColumn = i;
		}
		
		if (badRows > 1 || badColumns > 1){
			cout << "Corrupt" << "\n";
		} else if (badRows == 0 && badColumns == 0){
			cout << "OK" << "\n";
		} else {
			cout << "Change bit (" << badRow+1 << "," << badColumn+1 << ")\n"; 
		}
		
		cin >> n;
	}
	
	return 0;
}
