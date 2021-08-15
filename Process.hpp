#pragma once

#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <type_traits>
#include <concepts>
#include <iostream>

enum class RETURN_STATUS {
	FORK_ERROR,
	EXE_ERROR,
	EXE_SUCCESS,
	NONE
};

template<typename T>
concept ArgType = std::same_as<T, std::string>;

class Process {
	
	public:
		
		Process() = delete;

		Process(std::string const& exe_path)
			: m_path(exe_path) {}

		Process(std::string&& exe_path)
			: m_path(std::move(exe_path)) {}
		

		template<ArgType... T>
		constexpr auto createProcess(T const&... args) -> RETURN_STATUS {

			m_pid = fork();

			if (m_pid == -1) 
				return RETURN_STATUS::FORK_ERROR;

			if(m_pid == 0) {
			

				if (execl(m_path.c_str(), args.c_str() ..., (char*)NULL) == -1) {
					return RETURN_STATUS::EXE_ERROR;
				}
		
			} else {
				// PARENT PROCESS
				
				if (waitpid(m_pid, &m_status, 0) > 0)
					if (WIFEXITED(m_status) && !WEXITSTATUS(m_status)) {
						return RETURN_STATUS::EXE_SUCCESS;
					}	
			}

			return RETURN_STATUS::NONE;
		}
		

	private:

		pid_t m_pid{};
		int m_status{};
		std::string m_path;
};
