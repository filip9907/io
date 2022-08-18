#include <iostream>
#include<vector>;
#include "efects.h"
#include <string>

int main() {
	std::cout << "Wybierz tryb:" << std::endl
		<< "1.Panel Sterowania" << std::endl
		<< "2.Rysowanie" << std::endl <<
		"3.Filtry" << std::endl <<
		"4.Udostepnienie" << std::endl;

		int tryb=0;
		std::string dupa;
	std::cin >> tryb;
	switch (tryb)
	{
	case 1:
		std::cout << "Wybrales panel sterowania" << std::endl;
	case 2:
		std::cout << "Wybrales rysowanie" << std::endl;
	case 3:
		std::cout << "wybrales efekt" << std::endl;
		std::cout << "Podaj nazwe efektu" << std::endl ;
		std::cin >> dupa;
		std::cout << "przechodze do efektu";
		efects::efects(true);
	case 4:
		std::cout << "Wybrales udostepnianie" << std::endl;
		std::cout << "przechodze do filtrow";
	default:
		tryb = 0;
		std::cout << "wybierz tryb ponownie";
		break;
	}
	

	return 0;
}