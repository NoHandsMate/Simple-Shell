#pragma once

#include "CommandHandler.hpp"

#include <string>

class Parser {
	
	public:
		
		static auto parse_command(std::string& input, fs::path const& current_path) -> bool {

			if (input.starts_with("cd")) {
				CommandHandler::cd_command(input);
				return true;
			}
			
			if (input.starts_with("ls")) {
				CommandHandler::ls_command(input, current_path);
				return true;
			}

			if (input.starts_with("pwd")) {
				std::cout << current_path.string();
				return true;
			}

			if (input.starts_with("cat")) {
				CommandHandler::cat_command(input);
				return true;
			}

			if (input.starts_with("mkdir")) {
				return true;
			}

			return false;
		}

	private:
		Parser() {}
};
