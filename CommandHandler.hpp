#pragma once

#include "Process.hpp"
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <memory>

namespace fs = std::filesystem;

class CommandHandler {
	public:

		static auto cd_command(std::string& command) -> void {
			
			command.erase(0, 3); // Removes "cd"
			
			if (command == "")
				return; //TODO: Return to the home directory

			fs::path path = command;
			
			try {
				
				fs::current_path(path);
			
			} catch (...) {
				
				return;
			}
		}

		static auto ls_command(fs::path& current_path) -> void {
			
			
			const std::string path = "./commands_src/ls/bin/ls";
			
			std::array<char*, 3> args = {const_cast<char*>(path.c_str()), const_cast<char*>(current_path.c_str()), NULL};			
			
			auto process = Process<3>(path, args);

			switch(process.createProcess()) {
				case RETURN_STATUS::FORK_ERROR:
					std::cout << "FORK ERROR -> ls" << '\n';
					return;
					break;
				case RETURN_STATUS::EXE_ERROR:
					std::cout << "CALLING ls FAILED" << '\n';
					return;
					break;
				case RETURN_STATUS::EXE_SUCCESS:
					return;
					break;
				case RETURN_STATUS::NONE:
					return;
					break;
				default:
					return;	
			}

		}

		static auto cat_command(std::string& command) -> void {
			command.erase(0, 4); // Removes "cat"
			
			const std::string path = "./commands_src/cat/bin/cat";

			std::array<char*, 3> args = {const_cast<char*>(path.c_str()), const_cast<char*>(command.c_str()), NULL};
			auto process = Process<3>(path, args);

			switch(process.createProcess()) {
				
				case RETURN_STATUS::FORK_ERROR:
					std::cout << "FORK ERROR -> cat" << '\n';
					return;
					break;
				case RETURN_STATUS::EXE_ERROR:
					std::cout << "CALLING cat FAILED" << '\n';
					return;
					break;
				case RETURN_STATUS::EXE_SUCCESS:
					return;
					break;
				case RETURN_STATUS::NONE:
					return;
					break;
				default:
					return;	
			}

		}


	private:
		CommandHandler() {}
};

