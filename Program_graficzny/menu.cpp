#include "menu.h"
#include <iostream>
#include "efects.h"

int wybor() {
	std::cout << "Wybierz tryb:" << std::endl
		<< "1.Panel Sterowania" << std::endl
		<< "2.Rysowanie" << std::endl <<
		"3.Filtry" << std::endl <<
		"4.Udostepnienie" << std::endl;

	int tryb = 0;
	std::string dupa;
	std::cin >> tryb;
	switch (tryb)
	{
	case 1:
		std::cout << "Wybrales panel sterowania" << std::endl;
		return tryb;
	case 2:
		std::cout << "Wybrales rysowanie" << std::endl;
		return tryb;
	case 3:
		std::cout << "wybrales efekt" << std::endl;
		std::cout << "Podaj nazwe efektu" << std::endl;

		std::cout << "przechodze do efektu" << std::endl;
		efects::efects(true);
		return tryb;
	case 4:
		std::cout << "Wybrales udostepnianie" << std::endl;
		std::cout << "przechodze do filtrow";
		return tryb;
	default:
		tryb = 0;
		std::cout << "wybierz tryb ponownie";
		return tryb;
	}
}
menu::menu() {};