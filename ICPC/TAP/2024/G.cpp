#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;

#define esta(x,c) ((c).find(x) != (c).end())

int main()
{
    string s;
    cin >> s;

    map<char,int> repeticiones;

    int n = s.size();
    ll res = 0;

    for (int i = 0; i < n; i++){
        repeticiones[s[i]]++;
    }

    if (!esta('T',repeticiones) || !esta('P',repeticiones)){
        cout << res;
        return 0;
    }

    if(esta('A', repeticiones)){
        ll minChars = min(repeticiones['A'], min(repeticiones['T'], repeticiones['P']));
        res += minChars;
        repeticiones['A'] -= minChars;
        repeticiones['T'] -= minChars;
        repeticiones['P'] -= minChars;
    }

    if (esta('U', repeticiones)){
        ll minChars = min(repeticiones['U'], min(repeticiones['T'], repeticiones['P']));
        res += minChars;
        repeticiones['U'] -= minChars;
        repeticiones['T'] -= minChars;
        repeticiones['P'] -= minChars;
    }

    cout << res << "\n";

    return 0;
}
