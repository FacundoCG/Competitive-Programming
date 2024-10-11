#include <bits/stdc++.h>
using namespace std;

int steps(string &s, vector<int>& cells, int typeOfCell, string convert){
    int res = 0;
    int n = s.size();

   for (int &c : cells){
        if (typeOfCell == 0){
            if(s[c] == convert[0] && c+1 < n){
                s[c+1] = convert[1];
                res++;
            }

            if(s[c] == convert[1] && c-1 >= 0){
                s[c-1] = convert[0];
                res++;
            }
        } else if (typeOfCell == 1){
            if(s[c] == convert[1] && c-1 >= 0){
                s[c-1] = convert[0];
            }
        } else if (typeOfCell == 2){
            
        }    
   }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    int n = s.size();
    int ab = 0;
    int ba = 0;
    int boredCells = 0;

    int minimumSteps = 0;

    vector<int> typeOfCell(n);

    for (int i = 1; i < n; i++) {
        if (s[i-1] == 'B' && s[i] == 'A'){
            ab++;
        } else if (s[i-1] == 'A' && s[i] == 'B'){
            ba++;
        }
    }

    if (ab == ba){
        cout << 0 << "\n";
        return 0;
    }

    vector<int> cells0;
    vector<int> cells1;
    vector<int> cells2;
    vector<int> cells3;
    vector<int> cells4;
    vector<int> cells5;
    vector<int> cells6;

    
    if (s[0] == s[1]){
        typeOfCell[0] = 0; // 0 is a bored cell 
        cells0.push_back(0);
    } else if (s[0] == 'A' && s[1] == 'B'){
        typeOfCell[0] = 1; // 1 is a cell which makes AB to the right and to the left nothing
        cells1.push_back(0);
    } else {
        typeOfCell[0] = 2; // 2 is a cell which makes BA to the right and to the left nothing
        cells2.push_back(0);
    }
    
    if (s[n-1] == s[n-2] && n != 2){
        typeOfCell[n-1] = 0; // 0 is a bored cell 
        cells0.push_back(n-1);
    } else if (s[n-1] == 'A' && s[n-2] == 'B' && n != 2){
        typeOfCell[n-1] = 3; // 3 is a cell which makes AB to the left and to the right nothing
        cells3.push_back(n-1);
    } else if (n != 2){
        typeOfCell[n-1] = 4; // 4 is a cell which makes BA to the left and to the right nothing
        cells4.push_back(n-1);
    }

    for (int i = 1; i < n-1; i++){
        if (s[i] == s[i-1] && s[i] == s[i+1]){
            typeOfCell[i] = 0;
            cells0.push_back(i);
        } else if (s[i] == s[i-1] && s[i] == 'A' && s[i+1] == 'B'){
            typeOfCell[i] = 1;
            cells1.push_back(i);
        } else if (s[i] == s[i-1] && s[i] == 'B' && s[i+1] == 'A'){
            typeOfCell[i] = 2;
            cells2.push_back(i);
        } else if (s[i] == s[i+1] && s[i] == 'A' && s[i-1] == 'B'){
            typeOfCell[i] = 3;
            cells3.push_back(i);
        } else if (s[i] == s[i+1] && s[i] == 'B' && s[i-1] == 'A'){
            typeOfCell[i] = 4;
            cells4.push_back(i);
        } else if (s[i] == 'A' && s[i-1] == 'B' && s[i+1] == 'B'){
            typeOfCell[i] = 5; // 5 is a cell which makes BA to the left and AB to the right
            cells5.push_back(i);
        } else {
            typeOfCell[i] = 6; // 6 is a cell which makes AB to the left and BA to the right
            cells6.push_back(i);
        }
    }

    int steps = 0;
    int cell = 0;

    if (ab > ba){
        while(ba != ab){
            if (cell == 0){
                cell=1; // Now continue with the cells type 1
            } else if (cell == 1){
                cell = 3; // // Now continue with the cells type 3
            } else if (cell == 3){
                cell = 5; 
            } else {
                cell = 6;
            }
            //int steps += 
            // Do something
        }
    }

    cout << s << "\n";
}   
