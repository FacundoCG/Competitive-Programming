#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second


int main()
{
    // Lectura inputs:
    ll n, m, a,b,c;
    string s;
    cin >> n >> m;
    cin >> s;
    for(int i=0; i<m; i++){
        vector<char> func(123, '%');
        vector<char> func2(123, '%');
        cin >> a >> b >> c;
        a -=1;
        b -=1;
        bool puede = true;
        while(c!=0){
            int Fa = func[s[a]];
            int segundoDeb = func2[s[b]];
            if(Fa == '%'){
                if(segundoDeb == '%'){
                    func[s[a]] = s[b];    
                    func2[s[b]] = s[a];
                }else{
                    puede = false;
                    break;
                }
            }else{
                if(s[b] != Fa){
                    puede = false;
                    break;
                }
            }
            a += 1;
            b += 1;
            c-=1;
        }
        if(puede){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }
    }

}