#include "Parser.hpp"

#include <filesystem>

#include <iostream>
#include <cstdlib>


auto main() -> int {
	
	std::cout << "-- Simple Shell --" <<'\n';
	
	std::string user_input = {};
	
	while(true) {
		
			

		std::cout << '\n';
			
		auto current_path = fs::current_path();
//		auto current_relative_path = current_path.relative_path();
		
		std::cout << current_path.string() << " " <<"> ";	
		
		user_input.clear();

		std::getline(std::cin, user_input);
		
		auto result = Parser::parse_command(user_input, current_path);
	
		if(!result) {	
			std::cout << "Unsupported command";
		}
	
	}
	return 0;
}
