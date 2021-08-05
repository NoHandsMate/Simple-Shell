#pragma once

#include <filesystem>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <csignal>

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

		static auto ls_command(std::string& command, fs::path const& current_path) -> void {
			
			command.erase(0, 3); // Removes "ls"
			
			short i = 0;

			for (auto const& file : fs::directory_iterator(current_path)) {
				
				if (i % 3 == 0) {
					std::cout << '\n';
					i = 0;
				}
				i++;
				std::cout << std::setw(32) << std::left << file.path().filename().string() << " ";

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

