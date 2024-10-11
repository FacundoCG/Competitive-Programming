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
    int n; cin >> n;
    set<int>* evens = new set<int>();
    int number;
    for (int i = 0; i < n; i++) {
      cin >> number;
      if (number % 2 == 0) {
        evens->insert(number);
      }
    }

    int ans = 0;
    while(!evens->empty()) {
      ans++;
      number = *(prev(evens->end()));
      evens->erase(prev(evens->end()));
      //cout << "Max: " << number << "\n";
      number /= 2;
      if (number %2 == 0) {
        evens->insert(number);
      } 
    }

    cout << ans << "\n";
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--) solve(); 
}
