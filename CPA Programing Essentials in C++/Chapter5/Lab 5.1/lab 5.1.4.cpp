#include <iostream>
#include <string>

using namespace std;

class ShopItemOrder
{
public:
	ShopItemOrder(string name, double unit_price, int number)
	{
		this->name = name;
		this->unit_price = unit_price;
		this->number = number;
	}
	
	string get_name()
	{
		return this->name;	
	}
	
	void set_name(string name)
	{
		this->name = name;
	}
	
	double get_unit_price()
	{
		return this->unit_price;
	}
	void
	set_unit_price(double price)
	{
		this->unit_price = price;
	}
	
	int get_number()
	{
		return this->number;
	}
	
	void set_number(int number)
	{
		this->number = number;
	}
	
	double get_total_price()
	{
		return this->unit_price*this->number;
	}
	
	void PrintOrder()
	{
		cout<<"The order with name: "<< this->name<<",price: "<<this->unit_price<<" and number: " <<this->number<<endl;
	}
	
private:
	string name;
	double unit_price;
	int number;
};

int main()
{
	ShopItemOrder order("basketball", 12.50, 1);
	order.PrintOrder();
	
	order.set_number(2);
	cout << order.get_total_price() << endl;
	
	return 0;
}
