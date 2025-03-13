#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
	char c;
	bool lastWasOpenQuote = false;
	
	while (cin.get(c)){
		if (c == '"'){
			if (lastWasOpenQuote){
				cout << "''";
			} else {
				cout << "``";
			}
			lastWasOpenQuote = !lastWasOpenQuote;
		} else {
			cout << c;
		}
	}
	
	return 0;
}
