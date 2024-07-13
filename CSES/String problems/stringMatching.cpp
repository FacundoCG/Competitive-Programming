#include <bits/stdc++.h>

using namespace std;

vector<int> ComputePrefixFunction(string pattern){
    int m = pattern.length();
    vector<int> lps(m);

    lps[0] = 0;
    int len = 0;
    int j = 1;

    while (j < m){
        if (pattern[len] == pattern[j]){
            len++;
            lps[j] = len;
            j++;
        } else{
            if (len != 0){
                len = lps[len-1];
            } else{
                lps[j] = 0;
                j++;
            }
        }
    }

    return lps;
}

void KMP (string text, string pattern){
    int n = text.length();
    int m = pattern.length();
    int len = 0; // len = caracters matched
    int times = 0;
    vector<int> lpq = ComputePrefixFunction(pattern);

    for (int i = 0; i < n; i++){
        while (len > 0 && pattern[len] != text[i]){
            len = lpq[len-1];
        }

        if (pattern[len] == text[i]){
            len++;
        }

        if (len == m){
            times++;
            len = lpq[len-1];
        }
    }

    cout << times << "\n";
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string inputString;
    cin >> inputString;

    string pattern;
    cin >> pattern;
    

    KMP(inputString, pattern);
   
    return 0;
}
