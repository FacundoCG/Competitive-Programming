#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void digitsOfNWithoutZero(int n, vector<int> &digits){
	if (n <= 9){
		digits.push_back(n);
	} else {
		int digit = n % 10;
		digits.push_back(digit);
		digitsOfNWithoutZero(n/10, digits);
	}
}

int reverseNumber(int n){
	vector<int> reverseDigitsofN;
	
	while (n % 10 == 0) n /= 10;
	digitsOfNWithoutZero(n, reverseDigitsofN);
	 
	int res = 0;
	int m = (int) reverseDigitsofN.size();
	
	for (int i = 0; i < (int) reverseDigitsofN.size(); i++){
		res += pow(10, m-i-1)*reverseDigitsofN[i];
	}
	
	return res; 
}

int main(){
	int t;
	cin >> t;
	
	for (int i = 0; i < t; i++){
		int a, b;
		cin >> a >> b;
		
		int s = reverseNumber(a) + reverseNumber(b);
		cout << reverseNumber(s) << "\n";
	}
	
	return 0;
}
