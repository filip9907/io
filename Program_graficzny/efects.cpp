#include "efects.h"
efects::efects(bool tak) {
	if (tak==true)
	{
		std::cout << "Wybierz filtr:" << std::endl
			<< "1.Czarnobialy" << std::endl
			<< "2.Sepia" << std::endl <<
			"3.Rozmazanie" << std::endl;
		int filter_name=0;
		std::cin >> filter_name;
		switch (filter_name)
		{
		case 1:
			std::cout << "wybrales czarnobialy";
			break;

		case 2:
			std::cout << "wybrales sepie";
			break;
		case 3:
			std::cout << "wybrales rozmazanie";
			break;
		default:
			break;
		}
	}

};

int efects::moc_filtra(int power) {

	std::cout << "moc filtra:" << power << std::endl;

};