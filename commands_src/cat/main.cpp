#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

int main(int argc, const char* argv[]) {
	
	std::string arg = argv[0];
	
	if(arg.empty()) {
		
		std::string input{};

		while(true) {
			std::cin >> input;
			std::cout << input << '\n';
		}
	}

	auto file = std::ifstream(argv[0]);

	if(!file) {
		std::cout << "Could not open the specified file -> " << argv[0] << '\n';
		return -1;
	}
	
	std::string content = {};

	while(getline(file, content)) {
		std::cout << content << '\n';
	}

	file.close();
	
	return 1;
}
