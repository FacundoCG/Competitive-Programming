#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string pangrams(string s) {
    unordered_set<char> alphabet;
    string res;

    for (int i = 0; i < s.length(); i++) {
        if ( s[i] != ' ') alphabet.insert(tolower(s[i]));
    }

    if (alphabet.size() == 26) res = "pangram";
    else res = "not pangram";

    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = pangrams(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
