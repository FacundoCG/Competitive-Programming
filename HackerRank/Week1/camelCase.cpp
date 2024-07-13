#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void combine(string word, string category){
    string wordCombinated;
    bool upperLetter = false;

    for (int i=0; i<word.length(); i++){
        if (upperLetter){
            wordCombinated += toupper(word[i]);
            upperLetter = false;
        } else if (word[i] == ' '){
            upperLetter = true;
        } else {
            wordCombinated += word[i];
        }
    }

    if (category == "C") wordCombinated[0] = toupper(wordCombinated[0]);
    else if (category == "M") wordCombinated += "()";

    cout << wordCombinated << "\n";
}

void split(string word, string category){
    string newWord;
    int n = word.length();

    if (category == "M") n -= 2;

    for (int i = 0; i < n; i++){
        if (!isupper(word[i]) or i == 0){
            newWord += tolower(word[i]);
        } else{
            newWord += ' ';
            newWord += tolower(word[i]);
        }
    }

    cout << newWord << endl;
}

void camelCase(string word, string operation, string category){
    
    if (operation == "C") combine(word, category);        
    else split(word, category);

}


int main() {
    
    string line;
    while (getline(cin, line)) {
        string operation;
        string category;
        string word;

        for (int i = 0; i < line.size(); i++) {
            if (i == 0) operation = line[i];
            if (i == 2) category = line[i];
            if (i>3) word += line[i];
        }

        camelCase(word, operation, category);
    }
       
    return 0;
}
