#include <bits/stdc++.h>
using namespace std;

int main(){
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n;
        string s;
        cin >> n >> s;

        pair<int, int> roverPosition = {0, 0};
        pair<int, int> helicopterPosition = {0, 0};
        bool helicopterHadInstructions = false;
        vector<char> instructions(n);

        if (s[0] == 'N'){
            roverPosition.second++;
        } else if (s[0] == 'S'){
            roverPosition.second--;
        } else if (s[0] == 'E'){
            roverPosition.first++;
        } else {
            roverPosition.first--;
        }
        instructions[0] = 'R';

        for (int i = 1; i < n; i++){
            int xR = roverPosition.first;
            int yR = roverPosition.second;
            int xH = helicopterPosition.first;
            int yH = helicopterPosition.second;

            if (s[i] == 'N'){
                if (yR < yH){
                    roverPosition.second++;
                    instructions[i] = 'R';
                } else {
                    helicopterPosition.second++;
                    instructions[i] = 'H';
                    helicopterHadInstructions = true;
                }
            } else if (s[i] == 'S'){
                if (yR > yH){
                    roverPosition.second--;
                    instructions[i] = 'R';
                } else {
                    helicopterPosition.second--;
                    instructions[i] = 'H';
                    helicopterHadInstructions = true;
                }
            } else if (s[i] == 'W'){
                if (xR <= xH){
                    helicopterPosition.first--;
                    instructions[i] = 'H';
                    helicopterHadInstructions = true;
                } else {
                    roverPosition.first--;
                    instructions[i] = 'R';
                }
            } else {
                if (xR < xH){
                    roverPosition.first++;
                    instructions[i] = 'R';
                } else {
                    helicopterPosition.first++;
                    instructions[i] = 'H';
                    helicopterHadInstructions = true;
                }
            }
        }

        bool inequealPositions = roverPosition.first != helicopterPosition.first || roverPosition.second != helicopterPosition.second;
        if (inequealPositions || !helicopterHadInstructions){
            cout << "NO" << "\n";
        } else {
            for (int j = 0; j < n; j++){
                cout << instructions[j];
            }

            cout << "\n";
        }
    }
}