#include <iostream>
using namespace std;
int main(void) {
	
	float pi = 3.14159265359;
	float x,y,leftPart,rightPart;
	
	cout << "Enter value for x: ";
	cin >> x;
	
	leftPart = x*x/(pi*pi*(x*x+0.5));
	rightPart = 1+ x*x/(pi*pi*(x*x-0.5)*(x*x-0.5));
	y = leftPart*rightPart;
	
	cout << "y = " << y;
	return 0;
	
}