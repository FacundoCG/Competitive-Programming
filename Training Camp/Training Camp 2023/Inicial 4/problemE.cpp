// time-limit: 1000
// problem-url: https://codeforces.com/group/hzSLIARNBN/contest/465596/problem/E
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long l;
 
template<typename T>
void print(vector<T> &vec){
    for(auto &x:vec) cout<<x<<' ';
    cout<<'\n';
}
template<typename T>
void print(vector<pair<T,T>> &vec){
    for(auto &x:vec) cout<<x.first<<' '<<x.second<<'\n';
}
void barra(){ cout<<"----------------------"<<'\n'; }
 

void solve(){
    long long int m, n, ans = 0;
    cin >> n >> m;

    if (m%n != 0) {
      ans = -1;
    } else {
      m = m/n;
      while(m%2 == 0) {
        ans++;
        m = m/2;
      }
      while(m%3 == 0) {
        ans++;
        m = m/3;
      }
    }
    if (m == 1) {
      cout << ans << endl;
    } else {
      cout << -1 << endl;
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    //cin>>t;
    while(t--) solve(); 
}
