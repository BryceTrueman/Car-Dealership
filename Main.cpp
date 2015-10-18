/*
			Test Case 1
Chose option 1 - "* Your current inventory *"
				"You do not have any cars in your inventory :'(
chose option 2 - "Your current balance is: $ 10000"
			
			Test Case 2
	Chose option 3
"Please enter the name of the car you wish to buy: " Ferrari
"Please enter the color of the new car: " blue
"Please enter the price of the new car: " 2000
	Chose option 1
Name: Ferrari
Color: blue
Price: $2000
	Chose option 5
"What car would you like to paint?" Ferrari
"What color would you like to paint this car?" Green
	Chose option 1
Name: Ferrari
Color: Green
Price: $2000

			Test Case 3
	Chose option 6
"Please enter the file name that you want to load: " testIn.txt
	Chose option 1
Name: Delorian
Color: Seafoam
Price: $5

Name: Lamborghini
Color: Red
Price: $150000

Name: Prius
Color: Perrywinkle
Price: $3000
	Chose option 7
"Please enter where you would like to save this file: " Test.txt
	Chose option 8
"Have a nice day!"
*/


#include <iostream>
#include <string>
#include <vector>
#include "Car.h"
#include <fstream>

using namespace std;

int FindCar(vector<Car> cars, string findMe)//
{
	for (int i = 0; i < cars.size(); i++)
	{
		if (cars[i].getName() == findMe)
		{
			return i;
		}
	}
	return -1;
}

void currentinventory(vector <Car> cars)
{
	cout << "\t\t* Your Current Inventory *" << endl;
	cout << endl;
	for (int i = 0; i < cars.size(); i++)
	{
		cout << cars[i].toString();
		cout << endl;
	}
	if (cars.size() == 0)
	{
		cout << "You do not have any cars in your inventory :'(" << endl;
	}
}

double buyCar(vector<Car>& cars, double current_balance)
{
	string new_car_name;
	string new_color;
	double new_price = 0;
	cout << "Please enter the name of the car you wish to buy: ";
	cin.sync(); 
	getline(cin, new_car_name);
	int how_far = FindCar(cars, new_car_name);
	if (how_far != -1)
	{
		cout << "Sorry you already have that car." << endl;
		return new_price;
	}
	else
	{
		cout << "Please enter the color of the new car: ";
		getline(cin, new_color);
		cout << "Please enter the price of the new car: ";
		cin >> new_price;
		double temp_balance = current_balance - new_price;
		if (temp_balance >= 0)
		{
			Car newCar(new_car_name, new_color, new_price);
			cars.push_back(newCar);
			return new_price;
		}
		else
		{
			cout << endl;
			cout << "Sorry you do not have enough money to buy this car." << endl;
			return 0;
		}
	}
}

double sell_Car(vector <Car>& cars)
{
	string sell_car_name;
	double sell_car_price = 0;
	cout << endl;
	cout << "Please enter the name of the car you'd like to sell: ";
	cin.sync();
	getline(cin, sell_car_name);
	int how_far = FindCar(cars, sell_car_name);
	if (how_far != -1)
	{
		sell_car_price = cars[how_far].getPrice();
		cars.erase(cars.begin() + how_far);
		cout << endl;
		cout << "You sold your: " << sell_car_name << endl;
		return sell_car_price;
	}
	else
	{
		cout << endl;
		cout << "Sorry we do not have that car." << endl;
		return sell_car_price;
	}
}

double paintCar(vector <Car>& cars)
{
	double paint_car = 1000;
	string color_car_name;
	string new_car_color;
	cout << "What car would you like to paint?: ";
	cin.sync();
	getline(cin, color_car_name);
	int how_far = FindCar(cars, color_car_name);
	if (how_far != -1)
	{
		cout << "What color would you like to paint this car?: ";
		cin.sync();
		getline(cin, new_car_color);
		cars[how_far].paint(new_car_color);
		return paint_car;
	}
	else
	{
		cout << "Sorry we do not have that car." << endl;
	}
	paint_car = 0;
	return paint_car;
}

void loadFile(vector <Car>& cars)
{
	string newName;
	string newColor;
	double newPrice = 0;
	string in_file_name;
	cout << "Please enter the file name that you want to load: ";
	cin.sync();
	getline(cin, in_file_name);
	ifstream in;
	in.open(in_file_name);
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> newName;
			in >> newColor;
			in >> newPrice;
			Car c(newName, newColor, newPrice);
			cars.push_back(c);
		}
	}
	else
	{
		cout << "Bad file" << endl;
	}
	in.close();
}

void saveFile(vector <Car>& cars, double current_balance)
{
	string out_file_name;
	cout << "Please enter where you would like to save this file: ";
	cin.sync();
	getline(cin, out_file_name);
	ofstream out_file;
	out_file.open(out_file_name);
	cout << "You saved your file at: " << out_file_name << endl;
	cout << endl;
	out_file << current_balance << endl;
	for (int i = 0; i < cars.size(); i++)
	{
		out_file << cars[i].getName() << " ";
		out_file << cars[i].getColor() << " ";
		out_file << cars[i].getPrice();
		if (i != (cars.size() - 1))
		{
			out_file << endl;
		}
	}
	out_file.close();
}

int main()
{
	vector<Car> cars;
	int option = 0;
	const double starting_balance = 10000;
	double current_balance = starting_balance;
	cout << "\t\t\tHello, Welcome to my program!" << endl;
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	do
	{
		cout << "Please choose an option from the list." << endl;
		cout << "1. Show Current Inventory" << endl;
		cout << "2. Show Current Balance" << endl;
		cout << "3. Buy a car" << endl;
		cout << "4. Sell a car" << endl;
		cout << "5. Paint a car" << endl;
		cout << "6. Load File" << endl;
		cout << "7. Save File" << endl;
		cout << "8. Quit program" << endl;
		cin >> option;
		if (option == 1)//show current inventory
		{
			cout << endl;
			currentinventory(cars);
			cout << endl;
		}
		if (option == 2)//show current balance
		{
			cout << endl;
			cout << "Your current balance is: $ " << current_balance << endl;
			cout << endl;
		}
		if (option == 3)//buy a car
		{
			cout << endl;
			current_balance -= buyCar(cars, current_balance);
			cout << endl;
		}
		if (option == 4)//sell a car
		{
			current_balance += sell_Car(cars);
			cout << endl;
		}
		if (option == 5)//paint a car
		{
			paintCar(cars);
		}
		if (option == 6)//load file
		{
			loadFile(cars);
		}
		if (option == 7)//save file
		{
			saveFile(cars, current_balance);
		}
		if (option == 8)//quit program
		{
			cout << "Have a nice day!" << endl;
		}
	} while (option != 8);
	
	system("pause");
	return 0;
}

