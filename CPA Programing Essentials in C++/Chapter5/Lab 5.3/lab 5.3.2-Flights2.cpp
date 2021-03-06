#include <iostream>

class FlightBooking {	
public:
	FlightBooking(int id, int capacity, int reserved);
	void printStatus();
	
	bool reserveSeats(int number_ob_seats);
	bool canceReservations(int number_ob_seats);	
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{
	int percentage = this -> reserved * 100 / this -> capacity;
	std::cout << "Flight "<<this->id<<" : "<<this->reserved<<"/"<<capacity<<" ("<<percentage<<"%)"<<" seats taken\n";
}

FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
	this -> id = id;
	this -> capacity = capacity;
	
	int seats105perc = 105 * this->capacity / 100;
	
	if (reserved < 1)
		this -> reserved = 0; 	
	else if (reserved > seats105perc)
		this -> reserved = seats105perc;	
	else 
		this -> reserved = reserved;
}

bool FlightBooking::reserveSeats(int number_ob_seats)
{
	bool result = true;
	if (number_ob_seats < 1) {
		result = false;
		std::cout<<"Cannot perform this operation\n";
	}
	else {
		int seats105perc = 105 * this->capacity / 100;
		
		if ( number_ob_seats + this->reserved >= seats105perc) {
			
			result = false;
			std::cout<<"Cannot perform this operation\n";
		}
		else
			this->reserved += number_ob_seats;
	}	
	return result;
}

bool FlightBooking::canceReservations(int number_ob_seats)
{
	bool result = true;
	
	if (number_ob_seats > reserved || number_ob_seats < 0) {
		
		result = false;
		std::cout<<"Cannot perform this operation\n";
	}
	else 
		this->reserved -= number_ob_seats;
	
	return result;
}

int LikePow(int number, int pow_to) {
	
	if (pow_to == 0)
		return 1;
		
	int start_number = number;
	
	for (int i = 0; i < pow_to - 1; i++)
		number *= start_number;
		
	return number;
}

void ConvertStringToInt(int &number, std::string row) {
	
	for (int i = 0; i < row.length(); i++)
		number += LikePow(10, i) * (row[row.length() - 1 - i] - 48);
}

bool ExecuteCommand(std::string command, int number, FlightBooking &booking)
{
	if (command.compare("add") == 0) {
		if(booking.reserveSeats(number))
			return true;
	}
	else if (command.compare("cancel") == 0) {
		if(booking.canceReservations(number))
			return true;
	}
	return false;		
}

bool CheckCommand(std::string command, FlightBooking &booking)
{
	bool result = false;
	if (command.compare("quit") != 0 && command.length() > 0) {
		
		int number = 0;
		int index = command.find(" ");
		
		if (index != 0 && index != std::string::npos) {
			
			ConvertStringToInt(number, command.substr(index + 1, command.length() - 1));
			std::string concrete_command = command.substr(0, index);
			
			if (ExecuteCommand(concrete_command, number, booking))
				result = true;			
		}
	}
	return result;
}

int main() {
	
	int reserved = 0,
	capacity = 0;
	
	std::cout << "Provide flight capacity: \n";
	std::cin >> capacity;
	
	std::cout << "Provide number of reserved seats: \n";
	std::cin >> reserved;
	
	FlightBooking booking(1, capacity, reserved);
	booking.printStatus();
	
	std::string command = "";
	std::getline(std::cin, command);
	
	while (command != "quit")
	{
		if(CheckCommand(command, booking))
			booking.printStatus();
			
		std::getline(std::cin, command);
	}
	return 0;
}