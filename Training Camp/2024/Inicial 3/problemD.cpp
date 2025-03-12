#include <bits/stdc++.h>
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
    ll n, k, contador=0;

    cin >> n >> k;

    string s = bitset<32>(n).to_string();
    vector<int> digits;

    int firstOne;
    bool flag = true;

    for (int i = 0; i < s.length(); i++){
        if (flag && s[i] == '1'){
            firstOne = i;
            flag = false;
        }

        int d = s[i] - '0';
        digits.push_back(d);
    }

    for(ll i=0; i<32; i++){
        if (s[i] == '1'){
            contador++;
        }
    }

    if(contador<= k && k<=n){
        cout << "YES" << "\n";

        while(k != contador){
            while (digits[firstOne] != 0 && k != contador){
                if (firstOne == 31){
                    break;
                }

                digits[firstOne]--;
                digits[firstOne+1] += 2;
                contador++;
            }

            firstOne++;
        }

        for (int i = 0; i < 32; i++){
            for (int j = 1; j <= digits[i]; j++){
                long long v = (long long) pow(2, 32 - i - 1);
                cout << (long long) v << " ";
            }
        }

        cout << endl;
    } else {
        cout << "NO" << "\n";
    }
 
    return 0;
}