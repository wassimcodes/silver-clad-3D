#include "Printer.h"
#include <iostream>

Printer::Printer()
{

}

void Printer::MessagePrinter(std::string p_message)
{
	std::cout << p_message << std::endl;	
}
