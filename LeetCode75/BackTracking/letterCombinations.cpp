#include <bits/stdc++.h>
using namespace std;

void generateCombinations(map<int, vector<char>>& grid, vector<string>& res, string& current, string& digits, int i){
    int n = digits.size();
    
    if (i == n){
        res.push_back(current);
        return;
    }

    int k = digits[i] - '0';
    vector<char> list = grid[k];
    int m = list.size();

    for (int j = 0; j < m; j++){
        current.push_back(list[j]);
        generateCombinations(grid, res, current, digits, i+1);
        current.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> res;
    string current;
    map<int, vector<char>> grid;
    char c = 'a';

    for (int i = 2; i <= 9; i++){
        for (int j = 0; j < 3; j++){
            grid[i].push_back(c);
            ++c;
        }

        if (i == 7 || i == 9){
            grid[i].push_back(c);
            ++c;
        }
    }

    if (digits.size() != 0){
        generateCombinations(grid, res, current, digits, 0);
    }

    return res;
}

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    vector<string> res = letterCombinations(s);

    for (int i = 0; i < res.size(); i++){
        cout << res[i] << "\n";
    }
}