#pragma once

#include "CommandHandler.hpp"

#include <string>

class Parser {
	
	public:
		
		static auto parse_command(std::string& input, fs::path& current_path) -> bool {

			if (input.starts_with("cd")) {
				CommandHandler::cd_command(input);
				return true;
			}
			
			if (input.starts_with("ls")) {
				CommandHandler::ls_command(current_path);
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
				CommandHandler::mkdir_command(input);
				return true;
			}

			return false;
		}

	private:
		Parser() {}
};
