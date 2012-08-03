#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "vm.h"

int main(int argc, char *argv[])
{
	std::fstream file(argv[1]);
	std::stringstream buffer;
	buffer << file.rdbuf();
	
	VM vm(buffer.str());

	while(std::cin.good())
	{
		std::string line;
		std::cin >> line;
		std::cout << int(vm.run(line)) << std::endl;
	}

	return 0;
}
