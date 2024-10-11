#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;
const double PI = acos(-1.0);

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

bool areEqual(vector<int> &A, vector<int> &B){
    if (A.size() != B.size()) return false;

    bool res = true;

    forn(i,A.size()){
        if (A[i] != B[i]) res = false;
    }

    return res;
}

void emptyStation(vector<int> &train, stack<int> &station){
    while (!station.empty()){
        train.pb(station.top());
        station.pop();
    }     
}

void marshalTrain(vector<int> &desiredTrain, vector<int> &currentTrain, stack<int> &station){
    int currentCoach = 1;
    int k = 0;

    while (k < desiredTrain.size() && currentCoach <= desiredTrain.size()){
        if (currentCoach == desiredTrain[k]){
            currentTrain.pb(currentCoach);
            k++;
            currentCoach++;
        } else if (!station.empty() && station.top() == desiredTrain[k]){
            currentTrain.pb(station.top());
            k++;
            station.pop();
        } else {
            station.push(currentCoach);
            currentCoach++;
        }
    }
}

void solve(vector<vector<int>> &trains){
    forn(i, trains.size()){
        string res = "Yes";
        vector<int> currentTrain;
        stack<int> station;

        marshalTrain(trains[i], currentTrain, station);
        emptyStation(currentTrain, station);   

        if (!areEqual(currentTrain, trains[i])){
            res = "No";
        }

        cout << res << "\n";
    }

    cout << "\n";
}

int main() {  
    int n;

    while (cin >> n){
        if (n == 0) break;

        int m;
        vector<vector<int>> trains;

        while (cin >> m){
            vector<int> train;

            if (m == 0) break;

            train.pb(m);

            forn(j,n-1){
                int k;
                cin >> k;
                train.pb(k);
            }

            trains.pb(train);
        }

        solve(trains);
    }
}