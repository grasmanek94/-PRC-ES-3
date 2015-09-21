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

#include "RentalAdministration.h"
#include "Limousine.h"
#include "Sedan.h"

static void addTestDataToAdministration(RentalAdministration* administration)
{
    std::string licencePlates[] = {"SD-001", "SD-002", "SD-003", "SD-004", "LM-001", "LM-002"};

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
}

static size_t selectCar(const RentalAdministration* administration)
{
    return 0;
}

static void rentCar(RentalAdministration* administration, size_t carNumber)
{
}

static void returnCar(RentalAdministration* administration, size_t carNumber)
{
}

static void printIfCarNeedsCleaning(const RentalAdministration* administration, size_t carNumber)
{
}

static void cleanCar(RentalAdministration* administration, size_t carNumber)
{
}


static void showMenu( void )
{
    std::cout << ("\n\nCar Rental menu\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Show all cars\n");
    std::cout << ("(2) Select car\n");
    std::cout << ("(3) Rent selected car\n");
    std::cout << ("(4) Return selected car\n");
    std::cout << ("(5) Check if car needs cleaning\n");
    std::cout << ("(6) Clean car\n");
    std::cout << ("-----------------------\n");
    std::cout << ("(9) QUIT\n\n");
    std::cout << ("Choice : ");
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
		std::cin >> choice;
		std::cin.ignore();

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
			std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
            break;
        }
    }

    return 0;
}
