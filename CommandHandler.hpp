#pragma once

#include <filesystem>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
			
			auto child_pid = fork();
			
			int status = 0;

			if (child_pid == -1) {
				std::cout << "CANT FORK (ls)" << '\n';
				return;
			}

			else if (child_pid == 0) {
				char* args[] = {"./commands_src/ls/bin/ls", const_cast<char*>(current_path.c_str()), NULL};
				if( execv("./commands_src/ls/bin/ls", args) == -1 ) {
					std::cerr << "ERROR CALLING ls " << '\n';
					return;
				}
			} else {
				if (waitpid(child_pid, &status, 0) > 0) {
					if (WIFEXITED(status) && !WEXITSTATUS(status)) {
						std::cout << "SUCCESSFUL EXECUTED" << '\n';
					}
				}
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

