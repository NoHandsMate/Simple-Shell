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
					std::cout << "FORK ERROR" << '\n';
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
					std::cout << "SOMETHING WRONG CALLING ls " << '\n';
					return;
					break;
				default:
					return;	
			}

		}

		static auto cat_command(std::string& command) -> void {
			command.erase(0, 4); // Removes "cat"
			
			auto file = std::ifstream(command);
			
			if(!file) {
				std::cout << "Couldn't open the file";
			}
			
			std::string content = {};

			while(getline(file, content)) {
				std::cout << content << '\n';
			}

			file.close();

		}


	private:
		CommandHandler() {}
};

