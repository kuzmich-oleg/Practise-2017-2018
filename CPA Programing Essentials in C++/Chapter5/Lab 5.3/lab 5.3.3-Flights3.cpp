#include <iostream>

class FlightBooking {	
public:
	FlightBooking(int id, int capacity, int reserved);
	FlightBooking();
	void printStatus();
	
	bool reserveSeats(int number_ob_seats);
	bool canceReservations(int number_ob_seats);	
	int get_id();
	
private:
	int id;
	int capacity;
	int reserved;
};

void FlightBooking::printStatus()
{
	int percentage = 0;
	
	if (this -> capacity > 0)
		percentage = this -> reserved * 100 / this -> capacity;	
	
	std::cout << "Flight " << this -> id << " : " << this -> reserved
	 << "/" << capacity << " (" << percentage << "%)" << " seats taken\n";
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

FlightBooking::FlightBooking()
{
	this -> id = 0;
	this -> capacity = 0;
	this ->reserved = 0;
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

int FlightBooking::get_id() { return this -> id; }

int ConvertStringToInt( std::string row) {
	
	int number = 0;
	
	for (int i = 0; i < row.length(); i++)
		number += LikePow(10, i) * (row[row.length() - 1 - i] - 48);
	
	return number;
}

std::string* LikeASplit (std::string input_row, int &size) {
	
	input_row += " ";
	int index = input_row.find(" ");
	std::string *rows = new std::string[1];
	
	while (index != 0 && index != std::string::npos)
	{
		std::string* temp_rows = new std::string[size + 1];
		
		if (size > 0)
			for (int i = 0; i < size; i++)
				temp_rows[i] = rows[i];
		
			temp_rows[size] = input_row.substr(0, index);
			input_row.erase(0, index + 1);
			index = input_row.find(" ");
			
			delete [] rows;
			rows = temp_rows;
			size++;
	}
	return rows;
}

int GetCommandIndex(std::string command) {
	
	std:: string commands[4] = {"create", "delete", "add", "cancel"};
	int index = 0;
			
	for (int i = 0; i < 4; i ++)
		if (command.compare(commands[i]) == 0) {
			index = i + 1;
			break;
		}
	
	return index;
}

void ExecuteConcreteOne(int &com_index, int id, int seats, FlightBooking &flight) {
	
	if (flight.get_id() == 0 && com_index != 1) {
		std::cout << "Cannot perform this operation: flight " << id << " not found\n";
		com_index = 0;
	}
		
	switch(com_index) {
			case 0 : break;
			case 1: {
				flight = FlightBooking(id, seats, 0);
				break;
			}
			case 2: {
				flight = FlightBooking();
				break;
			}
			case 3: {
				flight.reserveSeats(seats);
				break;
			}
			case 4: {
				flight.canceReservations(seats);
				break;
			}
			default: {
				std::cout << "Uncorrect operation\n";
			}
		}
}

void ExecuteCommand(std::string command, int id, int seats, FlightBooking *flights)
{
	int count_of_free = 0;
	int size = 10;
	int index = -1;
	
	for (int i = 0; i < size; i++)
		if (flights[i].get_id() == 0)
			count_of_free++;
		else if (flights[i].get_id() == id)
			index = i;
		
	if (count_of_free < 1 && command.compare("delete") != 0) 
		std::cout << "There are not available flights\n";
	else {
		if (index == -1)
			index = size - count_of_free;
		int com_index = GetCommandIndex(command);

		ExecuteConcreteOne(com_index, id, seats, flights[index]);
	}
}

void CheckCommand(std::string command, FlightBooking *booking) {
	
	if (command.compare("quit") != 0 && command.length() > 0) {
		
		int size = 0;
		std::string *rows = LikeASplit(command, size);
		
		std::string concrete_command = rows[0];
		int id = ConvertStringToInt(rows[1]);
		int seats = 0;
		
		if (size == 3)
			seats = ConvertStringToInt(rows[2]);
		
		ExecuteCommand(concrete_command,id, seats, booking);
	}
}

void ShowFlights(FlightBooking *flights, int length) {
	
	int count_of_flights = 0;
	
	for (int i = 0; i < length; i++)
		if (flights[i].get_id() != 0) {
			
			flights[i].printStatus();
			count_of_flights++;
		}
		
	if (count_of_flights == 0)
		std::cout << "No flights in the system\n";
		
	std::cout << std::endl;
}

int main() {
	
	FlightBooking flights[10];
	ShowFlights(flights, 10);
	
	std::string command = "";
	std::getline(std::cin, command);
	
	while (command != "quit")
	{
		CheckCommand(command, flights);
		std::getline(std::cin, command);
		ShowFlights(flights, 10);
	}
	return 0;
}