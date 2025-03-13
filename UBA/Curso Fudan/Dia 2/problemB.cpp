#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    int set = 1;
    
    while (n != 0){
		vector<string> names(n);
		for(int i=0; i < n; i++) cin >> names[i];
		
		cout << "SET " << set << "\n";
		for (int i = 0; i < n; i+=2) cout << names[i] << "\n";
		for (int i = n-1-(n%2); i >= 0; i -= 2) cout << names[i] << "\n";
		
		set++;
		cin >> n;
	}

    return 0;
}


