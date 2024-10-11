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


// ############################################################### //

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        int n, m;
        cin >> n >> m;

        vector<ll> candidates(n+m+1);
        vector<ll> programmingLevels(n+m+1);
        vector<ll> testingLevels(n+m+1);
        vector<bool> isProgrammer(n+m+1,false);

        ll sumProgrammers = 0;
        ll sumTesters = 0;

        forn(j,n+m+1) cin >> programmingLevels[j];
        forn(j,n+m+1) cin >> testingLevels[j];

        bool assignedFirstTesters = false;
        bool firstTime = true;
        int testerWhoCouldBeProgrammer = n+m;
        int programmerWhoCouldBeTester = n+m;
        int programmersLeft = n;
        int testersLeft = m;
        int j = 0;
        ll teamLevel = 0;

        while (programmersLeft > 0 || testersLeft > 0){
            if (programmersLeft > 0 && testersLeft > 0){
                if (programmingLevels[j] > testingLevels[j]){
                    programmersLeft--;
                    isProgrammer[j] = true;
                    teamLevel += programmingLevels[j];
                } else {
                    testersLeft--;
                    teamLevel += testingLevels[j];
                }
            } else if (programmersLeft > 0){
                if (firstTime && testingLevels[j] > programmingLevels[j]){
                    programmerWhoCouldBeTester = j;
                    firstTime = false;
                }

                assignedFirstTesters = true;
                isProgrammer[j] = true;
                teamLevel += programmingLevels[j];
                programmersLeft--;
            } else {
                if (firstTime && programmingLevels[j] > testingLevels[j]){
                    testerWhoCouldBeProgrammer = j;
                    firstTime = false;
                }

                teamLevel += testingLevels[j];
                testersLeft--;
            }

            j++;
        }

        if (assignedFirstTesters) {
            forn(j,n+m){
                ll res = teamLevel;

                if (isProgrammer[j]){
                    res -= programmingLevels[j];
                    res += programmingLevels[n+m];
                } else {
                    res -= testingLevels[j];
                    
                    if (programmerWhoCouldBeTester != n+m){
                        res -= programmingLevels[programmerWhoCouldBeTester];
                        res += testingLevels[programmerWhoCouldBeTester];
                        res += programmingLevels[n+m];
                    } else {
                        res += testingLevels[n+m];
                    }
                }

                cout << res << " ";
            }
        } else {
            forn(j,n+m){
                ll res = teamLevel;

                if (!isProgrammer[j]){
                    res -= testingLevels[j];
                    res += testingLevels[n+m];
                } else {
                    res -= programmingLevels[j];
                    
                    if (testerWhoCouldBeProgrammer != n+m){
                        res -= testingLevels[testerWhoCouldBeProgrammer];
                        res += programmingLevels[testerWhoCouldBeProgrammer];
                        res += testingLevels[n+m];
                    } else {
                        res += programmingLevels[n+m];
                    }
                }

                cout << res << " ";
            }
        }

        cout << teamLevel << "\n";
    }
}