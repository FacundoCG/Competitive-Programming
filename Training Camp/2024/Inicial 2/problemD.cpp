#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long t, a, b, x, y;
    cin >> t;

    for(int i=0; i<t; i++){
        cin >> a >> b >> x >> y;
        long long res1 = (long long) abs(1-x)+abs(1-y) ;
        long long res2 = (long long) abs(a-x)+abs(1-y) ;
        long long res3 = (long long) (abs(1-x)+abs(b-y));
        long long res4 = (long long) (abs(a-x)+abs(b-y));
        long long resultado = (long long) max(res1 , max(res2 , max(res3 , res4)));
        cout << resultado << "\n";
    }
}