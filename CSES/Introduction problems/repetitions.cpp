#include <bits/stdc++.h>

using namespace std;

void maxRepetition(string word){
    vector<int> maximos;
    maximos.push_back(1);
    
    int currentMax = 1;
    auto it = maximos.begin();

    for (int i = 0; i < word.length(); i++){
        if (word[i] == word[i+1]){
            currentMax++;
        } else{
            if (currentMax > *it){
            maximos.pop_back();
            maximos.push_back(currentMax);
            }
            currentMax = 1;
        }

        if (i == word.length() - 1){
            if (currentMax > *it){
            maximos.pop_back();
            maximos.push_back(currentMax);
            }
        }
        
    }
     
    cout << *it << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string word;
    cin >> word;

    maxRepetition(word);
}

