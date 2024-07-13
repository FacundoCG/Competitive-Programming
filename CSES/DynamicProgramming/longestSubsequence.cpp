#include <bits/stdc++.h>
using namespace std;
 
const long long INF = 1000500;
 
vector<bool> ready (INF, false);
vector<long long> value (INF, 0);
vector<long long> prices;
vector<long long> pages;
 
long long solve(long long x, long long paginas, vector<bool>& comprado){
    if (x <= 0) return paginas;
    if (ready[x]) return value[x];
 
    long long best = paginas;
    
    for (int i = 0; i < pages.size(); i++) {
        if (!comprado[i] && x-prices[i] >= 0){
            comprado[i] = true;
            best = max(best, solve(x-prices[i], paginas + pages[i], comprado));
            comprado[i] = false;
        }
    }
 
    value[x] = best;
    ready[x] = true;
    
    return best;
}
 
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    long long n;
    long long x;
    
    cin >> n;
    cin >> x;
    
    vector<bool> bought(n, false);

    prices.assign(n, 0);
    pages.assign(n, 0);
 
    for (int i = 0; i < n; i++){
        long long price;
        cin >> price;
        
        prices[i] = price;
    }
 
    for (int i = 0; i < n; i++){
        long long page;
        cin >> page;
        pages[i] = page;
    }
 
    cout << solve(x, 0, bought) << "\n";
}

