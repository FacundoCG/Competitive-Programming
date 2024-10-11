#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll zero = 0;
const ll MAXIMUM = pow(10, 18);

void printSet (set<ll> &set){
    cout << "{";

    for (ll v : set) {
        cout << v << " ";
    }

    cout << "}" << "\n";
}

set<ll> intersectionSets (const set<ll> &set1, const set<ll> &set2){
    set<ll> res;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(res, res.begin()));
    return res;
}

set<ll> unionSets (const set<ll> &set1, const set<ll> &set2){
    set<ll> res;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(res, res.begin()));
    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    
    set<ll> numbersLiked;
    set<ll> numbersHated;
    bool firstUnion = true;

    for (int i = 0; i < n; i++){
        set<ll> currentSet;
        ll t, s;
        cin >> t >> s;

        if (t == 1){
            for (int j = 0; j < s; j++){
                ll v;
                cin >> v;
                currentSet.insert(v);
            }

            if (firstUnion){
                numbersLiked = currentSet;
                firstUnion = false;
            } else {
                numbersLiked = intersectionSets(numbersLiked, currentSet);
            }
        } else {
            for (int j = 0; j < s; j++){
                ll v;
                cin >> v;
                numbersHated.insert(v);
            }
        }
    }

    ll res;

    if (firstUnion){
        res = (ll) MAXIMUM - numbersHated.size();
        cout << res << "\n";
        return 0;
    }

    set<ll> differenceSets;
    set_difference(numbersLiked.begin(), numbersLiked.end(), numbersHated.begin(), numbersHated.end(), inserter(differenceSets, differenceSets.begin()));
    
    res = differenceSets.size();

    cout << res << "\n";
}
