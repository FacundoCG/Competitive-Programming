#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct LexicographicalComparator {
    bool operator()(ll & a, ll & b) const {
        return a > b; // Use operator > for min-heap
    }
};

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    priority_queue<ll, vector<ll>, LexicographicalComparator> minHeapA;
    priority_queue<ll> maxHeapB;

    for (int i = 0; i < n; i++) {
        ll v;
        cin >> v;
        minHeapA.push(v);
    }

    for (int i = 0; i < m; i++) {
        ll v;
        cin >> v;
        maxHeapB.push(v);
    }

    ll minA = minHeapA.top();
    ll maxB = maxHeapB.top();
    ll res = 0;

    while (minA < maxB && !minHeapA.empty() && !maxHeapB.empty()) {
        ll diff = (ll) maxB - minA;
        res += diff;
        maxHeapB.pop();
        minHeapA.pop();
        if (!minHeapA.empty() && !maxHeapB.empty()){
             minA = minHeapA.top();
            maxB = maxHeapB.top();
        }
    }

    cout << res << "\n";
}
