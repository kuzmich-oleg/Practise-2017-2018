#include <iostream>

using namespace std;

int main () {

	int firstValue, secondValue;
	
	cin >> firstValue;
	cin >> secondValue;
	
	if (firstValue/1 == secondValue/1)
		cout << "Results are equal (by 0.000001 epsilon)";
	else
		cout << "Results are not equal (by 0.000001 epsilon)";
  
	return 0;
  
}