#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'marsExploration' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int marsExploration(string s) {
    int modifiedLetters = 0;

    for (int i = 0; i < s.length(); i++) {
        if ((i % 3 == 0 || i % 3 == 2) && s[i] != 'S'){
            modifiedLetters++;
        } else if (i % 3 == 1 && s[i] != 'O'){
            modifiedLetters++;
        }
    }

    return modifiedLetters;
}

int main()
{
    string s;
    getline(cin, s);

    int result = marsExploration(s);

    cout << result << endl;

    return 0;
}
