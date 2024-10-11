#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> weight;
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

bool customCompare (const weight a, const weight b){
    ll weightOfEdgeA = a.first;
    ll weightOfEdgeB = b.first;

    ll repetitionsA = a.second;
    ll repetitionsB = b.second;

    if (weightOfEdgeA > weightOfEdgeB){
        return true;
    } else if (weightOfEdgeA < weightOfEdgeB){
        return false;
    }

    return repetitionsA < repetitionsB;
}

weight sumTuples(weight a, weight b){
    ll p1 = a.first + b.first;
    ll p2 = a.second + b.second;

    return {p1,p2};
}

struct LexicographicalComparator {
    bool operator()(const pair<weight,ll> a, const pair<weight,ll> b){
        weight a1 = a.first;
        weight b1 = b.first;

        ll weightOfEdgeA = a1.first;
        ll weightOfEdgeB = b1.first;

        ll repetitionsA = a1.second;
        ll repetitionsB = b1.second;

        if (weightOfEdgeA > weightOfEdgeB){
            return true;
        } else if (weightOfEdgeA < weightOfEdgeB){
            return false;
        }

        return repetitionsA < repetitionsB;
    }
};

vector<weight> djikstra (ll v, vector<vector<pair<weight, ll>>> &adjList, map<ll,ll> &repetitions, vector<ll> &parents){ // Time complexity: O(|E| * log(|V|))
    int n = adjList.size();
    vector<weight> distances(n, {INF, INF});
    vector<ll> visited(n, false);
    priority_queue<pair<weight, ll>, vector<pair<weight, ll>>, LexicographicalComparator> q;
    distances[v] = {0,0};
    parents[v] = v;
    q.push({{0,0}, v});
 
    while (!q.empty()){
        ll u = q.top().second;
        q.pop();
 
        if (visited[u]){
            continue;
        }
 
        visited[u] = true;
 
        for (ll i = 0; i < adjList[u].size(); i++){
            weight weightEdge = adjList[u][i].first;
            ll w = (ll) adjList[u][i].second;
            weight oldDistance = distances[w];
            weight distanceToU = distances[u];
            weight newDistance = sumTuples(weightEdge, distanceToU);
 
            if (customCompare(oldDistance, newDistance)){
                parents[w] = u;
                distances[w] = newDistance;
                q.push({distances[w], w});
            }
        }
    }
 
    return distances;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(i,t){
        string s;
        cin >> s;

        // Reading input + variables
        int m = s.size();
        ll firstTile = s[0] - 'a' + 1;
        ll lastTile = s[m-1] - 'a' + 1;
        vector<vector<pair<weight, ll>>> adjList(27);
        map<ll,ll> repetitionsOfLetters;
        vector<vector<ll>> positionsOfLetters(27);

        forn(j,m){
            char c = s[j];
            ll indexChar = c - 'a' + 1;
            positionsOfLetters[indexChar].pb(j+1);
            repetitionsOfLetters[indexChar]++;
        }

        for (auto p : repetitionsOfLetters) {
            ll C1 = p.first;
            ll repetitionsC1 = p.second;
            for (auto q : repetitionsOfLetters) {
                ll C2 = q.first;
                
                if (C1 != C2){
                    ll weightOfEdge = abs(C1 - C2);
                    weight weightAndRepetitions = {weightOfEdge, repetitionsC1};
                    adjList[C1].pb({weightAndRepetitions, C2});
                }
            }
        }

        // Calculating minDistance + path
        vector<ll> parents(27, UNDEFINED);
        vector<weight> distancesFrom1stTile = djikstra(firstTile, adjList, repetitionsOfLetters, parents);
        weight minDistance = sumTuples(distancesFrom1stTile[lastTile],{0,repetitionsOfLetters[lastTile]});

        // Build path of letters
        ll current = lastTile;
        vector<ll> pathLetters;

        while (current != firstTile){
            pathLetters.pb(current);
            current = parents[current];
        }

        pathLetters.pb(firstTile);
        reverse(all(pathLetters));
        //cout << pathLetters << endl;
        // Build path of jumps (positions)
        vector<ll> pathOfJumps;
        ll k = pathLetters.size();

        forn(j,k){
            ll currentLetter = pathLetters[j];
            ll p = positionsOfLetters[currentLetter].size();

            forn(h,p){
                ll index = positionsOfLetters[currentLetter][h];
                pathOfJumps.pb(index);
            } 
        }

        // Print answer
        ll minimumWeight = minDistance.first;
        ll maximumJumps = minDistance.second;

        cout << minimumWeight << " " << maximumJumps << "\n";

        for (auto index : pathOfJumps) {
            cout << index << " ";
        }

        cout << "\n";
    }
}