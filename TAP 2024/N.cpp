#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

int main()
{
    int n;
    cin >> n;

    vector<ll> arr(n);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    sort(all(arr));

    ll res = 0;

    for(int i = 0; i < n; i++){
        ll a = arr[i];
        for(int j = 0; j < n; j++){
            ll candidate = 0;
            ll b = arr[j];
            candidate += (ll) (a-b)*(a-b);
            candidate += (ll) a*b;
            ll k = a + b;
            ll option1 = (ll) arr[0]*(arr[0]-k);
            ll option2 = (ll) arr[n-1]*(arr[n-1]-k);
            candidate += max(option1, option2);
            res = max(res, candidate);
        }
    }

    cout << res << "\n";
}
