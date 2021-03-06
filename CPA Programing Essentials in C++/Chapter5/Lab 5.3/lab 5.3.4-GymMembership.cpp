#include <iostream>

using namespace std;

class GymMember {	
public:
	GymMember(int id, string name, int months);
	GymMember();
	void printStatus();
	void Extend(int month);
	void Cancel();
	int get_id();
	
private:
	int user_id;
	string user_name;
	int months;
};

void GymMember::printStatus()
{
	cout << "Member "<< this -> user_id << " : " << this -> user_name 
	<<", subscription valid for " << this -> months << " months\n";
}

GymMember::GymMember(int id, string name, int months)
{
	this -> user_id = id;
	this -> user_name = name;
	this -> months = months;
}

GymMember::GymMember()
{
	this -> user_id = 0;
	this -> user_name = "default";
	this -> months = 0;
}

int GymMember::get_id() { return this -> user_id; }

void GymMember::Extend(int months) {
	
	if (months > 0)
		this -> months += months;
}

void GymMember::Cancel() { this -> months = 0; }

int LikePow(int number, int pow_to) {
	
	if (pow_to == 0)
		return 1;
		
	int start_number = number;
	
	for (int i = 0; i < pow_to - 1; i++)
		number *= start_number;
		
	return number;
}

int ConvertStringToInt( string row) {
	
	int number = 0;
	
	for (int i = 0; i < row.length(); i++)
		number += LikePow(10, i) * (row[row.length() - 1 - i] - 48);
	
	return number;
}

string* LikeASplit (string input_row, int &size) {
	
	input_row += " ";
	int index = input_row.find(" ");
	string *rows = new string[1];
	
	while (index != 0 && index != string::npos)
	{
		string* temp_rows = new string[size + 1];
		
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

int GetCommandIndex(string command) {
	
	string commands[4] = {"create", "delete", "extend", "cancel"};
	int index = 0;
			
	for (int i = 0; i < 4; i ++)
		if (command.compare(commands[i]) == 0) {
			index = i + 1;
			break;
		}
	
	return index;
}

void ExecuteConcreteOne(int &com_index, int id, string name, int months, GymMember &member) {
	
	if (member.get_id() == 0 && com_index != 1) {
		cout << "Cannot perform this operation: member " << id << " is not found\n";
		com_index = 0;
	}
		
	switch(com_index) {
			case 0 : break;
			case 1: {
				member = GymMember(id, name, months);
				break;
			}
			case 2: {
				member = GymMember();
				break;
			}
			case 3: {
				member.Extend(months);
				break;
			}
			case 4: {
				member.Cancel();
				break;
			}
			default: {
				cout << "Uncorrect operation\n";
			}
		}
}

void ExecuteCommand(string command, int id, string name, int months, GymMember *members)
{
	int count_of_free = 0;
	int size = 10;
	int index = -1;
	
	for (int i = 0; i < size; i++)
		if (members[i].get_id() == 0)
			count_of_free++;
		else if (members[i].get_id() == id)
			index = i;
		
	if (count_of_free < 1 && command.compare("delete") != 0) 
		cout << "System is full)\n";
	else {
		if (index == -1)
			index = size - count_of_free;
		int com_index = GetCommandIndex(command);

		ExecuteConcreteOne(com_index, id, name, months, members[index]);
	}
}

void CheckCommand(string command, GymMember *members) {
	
	if (command.compare("quit") != 0 && command.length() > 0) {
		
		int size = 0;
		string *rows = LikeASplit(command, size);
		
		string concrete_command = rows[0];
		int id = ConvertStringToInt(rows[1]);
		string name = "";
		int months = 0;	
		
		 if (concrete_command.compare("create") == 0 && size == 4) 
			 name = rows[2] + rows[3];
		 
		 if (concrete_command.compare("extend") == 0) 
			 months = ConvertStringToInt(rows[2]);
		
		ExecuteCommand(concrete_command, id, name, months, members);
	}
}

void ShowMembers(GymMember *members, int length) {
	
	int count_of_members = 0;
	
	for (int i = 0; i < length; i++)
		if (members[i].get_id() != 0) {
			
			members[i].printStatus();
			count_of_members++;
		}
		
	if (count_of_members == 0)
		cout << "No members in the system\n";
		
	cout <<endl;
}

int main() {
	
	GymMember *members = new GymMember[10];
	ShowMembers(members, 10);
	
	string command = "";
	getline(std::cin, command);
	
	while (command != "quit")
	{
		CheckCommand(command, members);
		getline(cin, command);
		
		ShowMembers(members, 10);
	}
	return 0;
}