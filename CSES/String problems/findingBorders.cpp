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


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string inputString;
    cin >> inputString;

    vector<int> lps = ComputePrefixFunction(inputString);
    

    int k = lps.size()-1;
    set<int> res;
    

    while (lps[k] > 0){
        k = lps[k];

        if (k>0){
            res.insert(k);
        }

        k--;
    }

    for(int num:res){
        cout << num << " ";
    }
    
    return 0;
}
