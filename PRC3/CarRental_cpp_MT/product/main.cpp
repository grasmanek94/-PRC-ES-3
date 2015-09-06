//============================================================================
// Name        : menu.cpp
// Author      : Freddy Hurkmans
// Version     :
// Copyright   : copyright Freddy Hurkmans
// Description : Assignment 1 example
//============================================================================

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#include "RentalAdministration.h"
#include "Limousine.h"
#include "Sedan.h"

Car* selectedCar;

static void addTestDataToAdministration(RentalAdministration* administration)
{
    string licencePlates[] = {"SD-001", "SD-002", "SD-003", "SD-004", "LM-001", "LM-002"};

    for (int i = 0; i < 4; i++)
    {
        Car* sedan = new Sedan("BMW", "535d", 2012 + i, licencePlates[i], false);
        administration->Add(sedan);
    }
    for (int i = 4; i < 6; i++)
    {
        Car* limousine = new Limousine("Rolls Roys", "Phantom Extended Wheelbase", 2015, licencePlates[i], true);
        administration->Add(limousine);
    }
}

static void printCars(const RentalAdministration* administration)
{
	for (unsigned int i = 0; i < administration->GetCars().size(); i++) {
		cout << administration->GetCars()[i]->ToString() << endl;
	}
}

static size_t selectCar(const RentalAdministration* administration)
{
	string input;
	cout << "Select car by Licence Plate: ";
	getline(cin, input);
	selectedCar = NULL;
	for (unsigned int i = 0; i < administration->GetCars().size(); i++) {
		if (administration->GetCars()[i]->GetLicencePlate() == input) {
			selectedCar = administration->GetCars()[i];
			// return i;
		}
	}
	if ( selectedCar ) {
		cout << selectedCar->ToString() << " selected." << endl;
	} else {
		cout << "Car with plate " << input << " not found." << endl;
		cout << "Car selection reset." << endl; 
	}
	return 0;
}

static void rentCar(RentalAdministration* administration, size_t carNumber)
{
	if ( selectedCar ) {
		if (administration->RentCar(selectedCar->GetLicencePlate())) {
			cout << "Rented " << selectedCar->ToString() << endl;
		} else {
			cout << selectedCar->GetLicencePlate() << " already rented.";
		}
	}
	else {
		cout << "No car selected." << endl;
	}
}

static void returnCar(RentalAdministration* administration, size_t carNumber)
{
	if ( selectedCar ) {
		if ( selectedCar->IsAvailable() ) {
			cout << "Car not rented" << endl;
			return;
		}
		int kilometers;
		double price;
		cout << "Kilometers driven: ";
		cin >> kilometers;
		
		price = administration->ReturnCar(selectedCar->GetLicencePlate(), kilometers);
		cout << "Returned " << selectedCar->ToString() << endl;
		cout << "Costs: " << price << endl;
	}
	else {
		cout << "No car selected." << endl;
	}
}

static void printIfCarNeedsCleaning(const RentalAdministration* administration, size_t carNumber)
{
	if ( selectedCar ) {
		if (selectedCar->IsAvailable()) {
			if ( selectedCar->NeedsCleaning() ) {
				cout << selectedCar->GetLicencePlate() << " needs cleaning" << endl;
			}
			else {
				cout << selectedCar->GetLicencePlate() << " doesn't need cleaning" << endl;
			}
		}
		else {
			cout << selectedCar->GetLicencePlate() << " not available." << endl;
		}
	}
	else {
		cout << "No car selected." << endl;
	}
}

static void cleanCar(RentalAdministration* administration, size_t carNumber)
{
	if ( selectedCar ) {
		if (selectedCar->IsAvailable()) {
			administration->CleanCar(selectedCar->GetLicencePlate());
			cout << selectedCar->GetLicencePlate() << " cleaned" << endl;
		}
		else {
			cout << selectedCar->GetLicencePlate() << " not available." << endl;
		}
	}
	else {
		cout << "No car selected." << endl;
	}
}


static void showMenu( void )
{
    cout << ("\n\nCar Rental menu\n");
    cout << ("===============\n");
    cout << ("(1) Show all cars\n");
    cout << ("(2) Select car\n");
    cout << ("(3) Rent selected car\n");
    cout << ("(4) Return selected car\n");
    cout << ("(5) Check if car needs cleaning\n");
    cout << ("(6) Clean car\n");
    cout << ("-----------------------\n");
    cout << ("(9) QUIT\n\n");
    cout << ("Choice : ");
}

int main( void )
{
    bool quit = false;
    size_t carNumber = 0;

    RentalAdministration administration;
    addTestDataToAdministration(&administration);

    while (!quit)
    {
        char choice = '\0';
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case '1' :
            printCars(&administration);
            break;
        case '2' :
            carNumber = selectCar(&administration);
            break;
        case '3' :
            rentCar(&administration, carNumber);
            break;
        case '4' :
            returnCar(&administration, carNumber);
            break;
        case '5' :
            printIfCarNeedsCleaning(&administration, carNumber);
            break;
        case '6' :
            cleanCar(&administration, carNumber);
            break;

        case '9' :
            quit = true;
            break;
        default:
            cout << "\n\nI did not understand your choice (" << choice << ")" << endl;
            break;
        }
    }

    return 0;
}
