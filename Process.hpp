#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <array>
#include <string>

enum class RETURN_STATUS {
	FORK_ERROR,
	EXE_ERROR,
	EXE_SUCCESS,
	NONE
};



template<size_t arg_count>
class Process {
	
	public:
		
		Process() = delete;

		Process(std::string const& exe_path, std::array<char*, arg_count> const& args)
			: m_path(exe_path), m_arg(args) {}

		Process(std::string&& exe_path, std::array<char*, arg_count>&& args)
			: m_path(std::move(exe_path), m_args(std::move(args))) {}

		constexpr auto createProcess() -> RETURN_STATUS {
			
			m_pid = fork();

			if (m_pid == -1) 
				return RETURN_STATUS::FORK_ERROR;

			if(m_pid == 0) {
		
				// CHILD PROCESS
		
				if (execv(m_path.c_str(), m_arg.data()) == -1)
					return RETURN_STATUS::EXE_ERROR;
	
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
		std::array<char*, arg_count> m_arg;
};
