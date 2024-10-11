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
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

// Show vector
template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// Show set
template <typename T>
ostream & operator <<(ostream &os, const set<T> &s) {
    os << "{";
    for(auto it = s.begin(); it != s.end(); it++){
        if(it != s.begin()) os << ",";
        os << *it;
    }
    return os << "}";
}


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

int calculateDifference(vector<int> &A, vector<int> &B){
    // A.size() == B.size()
    int res = 0;

    forn(i, A.size()){
        if (A[i] != B[i] && A[i] > B[i]){
            res += A[i] - B[i];
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        int n, q;
        cin >> n >> q;

        string a,b;
        cin >> a >> b;

        vector<vector<int>> prefixLettersA(n, vector<int>(27));
        vector<vector<int>> prefixLettersB(n, vector<int>(27));

        int firstLetterA = a[0] - 'a';
        int firstLetterB = b[0] - 'a';
        prefixLettersA[0][firstLetterA]++;
        prefixLettersB[0][firstLetterB]++;

        forsn(j,1,n){
            int letterA = a[j] - 'a';
            prefixLettersA[j][letterA]++;

            forn(k, prefixLettersA[j-1].size()){
                prefixLettersA[j][k] += prefixLettersA[j-1][k];
            }
        }

        forsn(j,1,n){
            int letterB = b[j] - 'a';
            prefixLettersB[j][letterB]++;

            forn(k, prefixLettersB[j-1].size()){
                prefixLettersB[j][k] += prefixLettersB[j-1][k];
            }
        }

        forn(j,q){
            int l, r;
            cin >> l >> r;

            vector<int> lettersInRangeA = prefixLettersA[r-1];
            vector<int> lettersInRangeB = prefixLettersB[r-1];

            if (l != 1){
                forn(h,27){
                    lettersInRangeA[h] -= prefixLettersA[l-2][h];
                    lettersInRangeB[h] -= prefixLettersB[l-2][h];
                }
            }

            int minOperations = calculateDifference(lettersInRangeA, lettersInRangeB);
            cout << minOperations << "\n";
        }
    }
}